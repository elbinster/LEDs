//+--------------------------------------------------------------------------
//
// NightDriver - (c) 2020 Dave Plummer.  All Rights Reserved.
//
// File:        fire.h                    
//
// Description: A realistic flame simulation for LED strips
//
// History:     Oct-23-2020     davepl      Created
//
//---------------------------------------------------------------------------

#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

#include "ledgfx.h"

/// @brief FireEffect keeps track of heat values for each pixel
class FireEffect
{
  protected:
    CRGBSet Leds;               // Set of LEDs for this flame
    int     Size;               // Length of the flame
    int     Cooling;            // Rate at which the pixels cool off
    int     Sparks;             // How many sparks will be attempted each frame
    int     SparkHeight;        // If created, max height for a spark
    uint8_t Sparking;           // Probability of a spark each attempt
    bool    bReversed;          // If reversed we draw from 0 outwards
    bool    bMirrored;          // If mirrored we split and duplicate the drawing

    byte  * heat;

    // When diffusing the fire upwards, these control how much to blend in from the cells below (ie: downward neighbors)
    // You can tune these coefficients to control how quickly and smoothly the fire spreads

    static const byte BlendSelf = 2;
    static const byte BlendNeighbor1 = 3;
    static const byte BlendNeighbor2 = 2;
    static const byte BlendNeighbor3 = 1;
    static const byte BlendTotal = (BlendSelf + BlendNeighbor1 + BlendNeighbor2 + BlendNeighbor3);

  public:

    FireEffect(CRGBSet leds, int cooling = 20, uint8_t sparking = 100, int sparks = 3, int sparkHeight = 4, bool breversed = true, bool bmirrored = true)
        : Leds(leds),
          Cooling(cooling),
          Sparks(sparks),
          SparkHeight(sparkHeight),
          Sparking(sparking),
          bReversed(breversed),
          bMirrored(bmirrored)
    {
        Size = leds.len;
        if (bMirrored)
            Size = Size / 2;

        heat = new byte[Size] { 0 };
    }

    virtual ~FireEffect()
    {
        delete [] heat;
    }

    virtual void DrawFire(PixelOrder order = Sequential)
    {
        // First cool each cell by a litle bit
        for (int i = 0; i < (Size); i++)
        {
                Serial.print("Pixel: ");
                Serial.print(i);
                Serial.print(" start: ");
                Serial.print(heat[i]);
            int cool = max(0L, random(0, Cooling));
            heat[i] = max(0L, heat[i] - cool);
                Serial.print(" :minus: ");
                Serial.print(cool);
                Serial.print(" :equals: ");
                Serial.println(heat[i]);
        }
        // Next drift heat up and diffuse it a little bit
        for (int i = 0; i < Size; i++)
        {
            heat[i] = (heat[i] * BlendSelf +
                       heat[(i + 1) % Size] * BlendNeighbor1 +
                       heat[(i + 2) % Size] * BlendNeighbor2 +
                       heat[(i + 3) % Size] * BlendNeighbor3)
                      / BlendTotal;
        }

        // Randomly ignite new sparks down in the flame kernel

        for (int i = 0 ; i < Sparks; i++)
        {
            if (random(255) < Sparking)
            {
                int y = Size - 1 - random(SparkHeight);
                heat[y] = heat[y] + random(160, 255);       // Can roll over which actually looks good!
            }
        }

        // Finally, convert heat to a color
        Leds.fadeToBlackBy(64);
        for (int i = 0; i < Size; i++)
        {
            CRGB color = HeatColor(heat[i]);
            int j = bReversed ? Size-i : i;
            DrawPixels(Leds, j, 1, color);
            if (bMirrored)
            {
                uint8_t pixelToDraw = !bReversed ? (2 * Size - 1 - i) : Size + i;
                DrawPixels(Leds, pixelToDraw, 1, color);
            }
        }
        delay(40);
    }
};