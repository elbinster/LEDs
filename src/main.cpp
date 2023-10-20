//+--------------------------------------------------------------------------
//
// NightDriver - (c) 2018 Dave Plummer.  All Rights Reserved.
//
// File:        LED Episode 11
//
// Description:
//
//   Draws sample effects on a an addressable strip using FastLED
//
// History:     Sep-15-2020     davepl      Created
//              Oct-05-2020     davepl      Revised for Episode 07
//              Oct-11-2020     davepl      Revised for Episode 08
//              Oct-16-2020     davepl      Revised for Episode 09
//              Oct-23-2020     davepl      Revised for Episode 10
//---------------------------------------------------------------------------

#include <Arduino.h>            // Arduino Framework
#define FASTLED_INTERNAL        // Suppress build banner
#include <FastLED.h>
#include "ledgfx.h"
#include "comet.h"
#include "marquee.h"
#include "twinkle.h"
#include "fader.h"
#include "fire.h"
//#include "bounce.h"     // Bounce ain't gonna work without a cock

#define NUM_LEDS      200       // FastLED definitions
#define LED_PIN       12        // Output pin of LED Strip
#define FPS           60        // Ideal Frames per second
#define PERIOD        1/FPS     // Ideal delay (doesn't account for processing delay)

CRGB g_LEDs[NUM_LEDS] = {0};    // Frame buffer for FastLED
CRGBSet all_leds(g_LEDs, NUM_LEDS);

static int g_Brightness = 128;
static int g_PowerLimit = 4000;

#define STRING_START 0
#define FIRST_BREAK 45
#define SECOND_BREAK 155
#define STRING_END NUM_LEDS
CRGBSet first_leds(all_leds(STRING_START, FIRST_BREAK));
CRGBSet second_leds(all_leds(FIRST_BREAK+1, SECOND_BREAK));
CRGBSet third_leds(all_leds(SECOND_BREAK+1, STRING_END));

static FireEffect fire1(second_leds, 20, 100, 3, second_leds.len/4, false, false);

void setup() 
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(g_LEDs, NUM_LEDS).setCorrection(0xFFB0F0);               // Add our LED strip to the FastLED library
  FastLED.setBrightness(g_Brightness);
  set_max_power_indicator_LED(LED_BUILTIN);                               // Light the builtin LED if we power throttle
  FastLED.setMaxPowerInMilliWatts(g_PowerLimit);                          // Set the power limit, above which brightness will be throttled
  FastLED.clear();
  FastLED.show();
}

void DrawMarqueeComparison()
{
  FastLED.clear();
  static float scroll = 0.0f;
  scroll += 0.1f;
  if (scroll > 5.0)
    scroll -= 5.0;

  static CRGB color1 = AllColors[random(0, ARRAYSIZE(AllColors))];
  static CRGB color2 = AllColors[random(0, ARRAYSIZE(AllColors))];
  for (float i = scroll; i < NUM_LEDS/2 - 1; i+= 5)
  {
    DrawPixels(first_leds, first_leds.len-1-i, 3, color1);
    DrawPixels(first_leds, (int)i, 3, color2);
  }
}

void loop() 
{
  

  while (true)
  {
    EVERY_N_MILLISECONDS(PERIOD)
    {
      // Final Halloween Setup
      DrawTwoColorFade(second_leds, CRGB::Purple, CRGB::Green, 10);
      twinkleBlur(third_leds, CRGB::Green, 4, 8);
      //fire1.DrawFire();
    }
    EVERY_N_MILLISECONDS(PERIOD)
    {
      DrawComet(first_leds, 128, 3, CRGB::Orange, CRGB::OrangeRed);
    }
    FastLED.show(g_Brightness);
  }
}
