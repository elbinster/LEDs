//+--------------------------------------------------------------------------
//
// NightDriver - (c) 2020 Dave Plummer.  All Rights Reserved.
//
// File:        marque.h
//
// Description:
//
//   Draws a theatre-style marquee
//
// History:     Sep-15-2020     davepl      Created
//
//---------------------------------------------------------------------------

#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>


void DrawMarquee(CRGBSet leds, int hue = 8, bool clear = true, int clearMod = 8)
{
    static uint8_t numLeds = leds.len;
    static byte j = 0;
    j+=4;
    byte k = j;

    // Roughly equivalent to fill_rainbow(g_LEDs, NUM_LEDS, j, 8);

    CRGB c;
    for (int i = 0; i < numLeds; i ++)
        leds[i] = c.setHue(k += hue);

    static int scroll = 0;
    scroll++;

    if (clear)
        for (int i = scroll % clearMod; i < numLeds - 1; i += clearMod)
            leds[i] = CRGB::Black;
}

void DrawMarqueeMirrored(CRGBSet leds, int hue = 8, bool clear = true, int clearMod = 8)
{
    static uint8_t numLeds = leds.len;
    static byte j = 0;
    j+=4;
    byte k = j;

    // Roughly equivalent to fill_rainbow(g_LEDs, NUM_LEDS, j, 8);

    CRGB c;
    for (int i = 0; i < (numLeds) / 2; i ++)
    {
        leds[i] = c.setHue(k);
        leds[numLeds - 1 - i] = c.setHue(k);
        k += hue;
    }


    static int scroll = 0;
    scroll++;

    if (clear)
        for (int i = scroll % clearMod; i < numLeds / 2; i += clearMod)
        {
            leds[i] = CRGB::Black;
            leds[numLeds - 1 - i] = CRGB::Black;
        }   
}



