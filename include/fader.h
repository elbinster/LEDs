//+--------------------------------------------------------------------------
//
// NightDriver - (c) 2023 Jesse Elbin.  All Rights Reserved.
//
// File:        fdader.h
//
// Description:
//
//   Draws a color fade
//
// History:     Oct-15-2023     jelbin      Created
//
//---------------------------------------------------------------------------

#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>


void DrawSingleColorFade(int end, int start = 0, CRGB color = CRGB::Blue, uint16_t steps = 100)
{
    end = max(start, end);

    static uint16_t step = steps;
    static bool up = false;

    if (step >= steps)
    {
        up = !up;
        Serial.println("RESET");
        step = 0;
    }
    
    float fSteps = steps;
    float fadeAmt = 255/(fSteps-1);
    float ratio = fadeAmt*step;
    
    if (!up)
    {
        ratio = 255 - ratio;
    } else
        ratio = brighten8_raw(ratio);
    Serial.print(step);
    Serial.print(" ");
    Serial.println(ratio);
    for (int i = start; i < end; i ++)
    {
        if (up)
            FastLED.leds()[i] = color;
        FastLED.leds()[i].nscale8(ratio);
    }
    step++;
}



