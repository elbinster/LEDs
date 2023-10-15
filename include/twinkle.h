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

void DrawTwinkle(int end, int start = 0, int passes = 5, int fadeAmt = 32)
{
    end = max(start, end);
	static int passCount = 0;
	if (passCount++ >= (end-start)/passes)
	{
		passCount = 0;
        // Randomly fade the LEDs
        for (int j = start; j < end; j++)
            if (random(100) > 25)
                //FastLED.leds()[j] = FastLED.leds()[j].fadeToBlackBy(255-fadeAmt);     // Looks cool with max fade
                FastLED.leds()[j].fadeToBlackBy(fadeAmt);
        }
	FastLED.leds()[random(start, end)] = AllColors[random(0, ARRAYSIZE(AllColors))];
}

void twinkleHue(int end, int start = 0, CRGB hue = CRGB::Blue, int variance = 10, int passes = 5, int fadeAmt = 32)
{
    end = max(start, end);
    static int passCount = 0;

    hue.r = max(0, min(255, hue.r + random(-variance, variance)));
    hue.g = max(0, min(255, hue.g + random(-variance, variance)));
    hue.b = max(0, hue.b + random(-variance, variance));
    if (passCount++ >= (end-start)/passes)
    {
        passCount = 0;
        for (int i = start; i < end; i++)
        {
            if (random(100) > 25)
                FastLED.leds()[i].fadeToBlackBy(fadeAmt);
        }
        FastLED.leds()[random(start, end)] = hue;
    }
}