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

const uint8_t PROGMEM gamma8[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

void DrawSingleColorFade(CRGBSet leds, CRGB color = CRGB::Red, uint8_t bpm = 60) {
    
    static uint8_t numLeds = leds.len;
    uint8_t fader = beatsin8(bpm, 0, 255, 0, 0);
    fader = pgm_read_byte(&gamma8[fader]);
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
    fader = pgm_read_byte(&gamma8[fader]);
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
