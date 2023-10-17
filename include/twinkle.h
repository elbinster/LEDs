//+--------------------------------------------------------------------------
//
// NightDriver - (c) 2020 Dave Plummer.  All Rights Reserved.
//
// File:        
//
// Description:
//
//   
//
// History:     Sep-15-2020     davepl      Created
//
//---------------------------------------------------------------------------

#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

#include "ledgfx.h"

void DrawTwinkle(CRGBSet leds, int passes = 5, int fadeAmt = 32)
{
	static int passCount = 0;
    static uint8_t numLeds = leds.len;
	if (passCount++ >= (numLeds)/passes)
	{
		passCount = 0;
        // Randomly fade the LEDs
        for (int j = 0; j < numLeds; j++)
            if (random(100) > 25)
                //leds[j] = leds[j].fadeToBlackBy(255-fadeAmt);     // Looks cool with max fade
                leds[j].fadeToBlackBy(fadeAmt);
        }
	leds[random(numLeds)] = AllColors[random(0, ARRAYSIZE(AllColors))];
}

void twinkleHue(CRGBSet leds, CRGB hue = CRGB::Blue, int variance = 10, int passes = 5, int fadeAmt = 32)
{
    static int passCount = 0;
    static uint8_t numLeds = leds.len;
    hue.r = max(0, min(255, hue.r + random(-variance, variance)));
    hue.g = max(0, min(255, hue.g + random(-variance, variance)));
    hue.b = max(0, hue.b + random(-variance, variance));
    if (passCount++ >= (numLeds)/passes)
    {
        passCount = 0;
        for (int i = 0; i < numLeds; i++)
        {
            if (random(100) > 25)
                leds[i].fadeToBlackBy(fadeAmt);
        }
        leds[random(numLeds)] = hue;
    }
}

void twinkleBlur(CRGBSet leds, CRGB hue = CRGB::DarkOrange, uint8_t passes = 5, int fadeAmt = 32)
{
    static int passCount = 0;
    uint8_t numLeds = leds.len;

    if (passCount++ >= (numLeds)/passes)
    {
        passCount = 0;
        for (int i = 0; i < numLeds; i++)
        {
            // random blur (do this more)
            if (random(100) > 75) {
                blur1d(leds, numLeds, fadeAmt);
                blur1d(leds, numLeds, fadeAmt);
                blur1d(leds, numLeds, fadeAmt);
            }
            // random fade to black
            if (random(100) > 50) {
                leds[i].fadeToBlackBy(fadeAmt/2);
            }
        }
        leds[random(numLeds)] = hue;
    }
}