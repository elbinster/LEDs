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

void DrawSingleColorFade(CRGBSet leds, CRGB color = CRGB::Red, uint8_t bpm = 60) {
    
    static uint8_t numLeds = leds.len;
    uint8_t fader = beatsin8(bpm, 0, 255, 0, 0);
    for (int i = 0; i < numLeds; i ++)
    {
        leds[i] = color;
        leds[i].nscale8(fader);
    }
}

void DrawTwoColorFade(CRGBSet leds, CRGB color1 = CRGB::Blue, CRGB color2 = CRGB::Red, uint8_t bpm = 60) {

    static bool colorOne = false;
    static uint8_t numLeds = leds.len;
    static uint8_t minVal = 0;
    static uint8_t maxVal = 255;
    static uint8_t lastVal = 0;
    static bool up = false;
    uint8_t fader = beatsin8(bpm, minVal, maxVal, 0, 0);
    Serial.println(fader);
    if ((lastVal-fader < 0) && !up) {        // Doesn't reliably hit the min, but will flip twice if too high.
        colorOne = !colorOne;
        up = true;
    }
    if ((lastVal-fader > 0) && up)
        up = false;
    for (int i = 0; i < numLeds; i ++)
    {
        if (colorOne) {
            leds[i] = color1;
        } else {
            leds[i] = color2;
        }
        leds[i].nscale8(fader);
    }
    lastVal = fader;
}
