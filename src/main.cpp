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

#define NUM_LEDS      200       // FastLED definitions
#define LED_PIN       12        // Out+put pin of LED Strip
#define FPS           60        // Ideal Frames per second
#define PERIOD        1/FPS     // Ideal delay (doesn't account for processing delay)

CRGB g_LEDs[NUM_LEDS] = {0};    // Frame buffer for FastLED
CRGBSet all_leds(g_LEDs, NUM_LEDS);

static int g_Brightness = 125;
static int g_PowerLimit = 4000;

#define STRING_START 0
#define FIRST_BREAK 5
#define SECOND_BREAK 45
#define STRING_END NUM_LEDS
CRGBSet first_leds(all_leds(0, 38));
CRGBSet second_leds(all_leds(46, 200));
CRGBSet third_leds(all_leds(151, 200));

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

void loop() 
{
/*  
FireEffect(
  CRGBSet leds, 
  int cooling = 20, 
  uint8_t sparking = 100, 
  int sparks = 3, 
  int sparkHeight = 4, 
  bool breversed = true, 
  bool bmirrored = true)
*/
  static FireEffect fire1(all_leds, 10, 100, 2, all_leds.len/2, false, true);
  while (true)
  {
    EVERY_N_MILLISECONDS(PERIOD)
    {
      // Final Halloween Setup
      DrawTwoColorFade(second_leds, CRGB::Purple, CRGB::OrangeRed, 10);

      ////twinkleBlur(third_leds, CRGB::Green, 4, 8);
      ////fire1.DrawFire();
    }
    EVERY_N_MILLISECONDS(PERIOD)
    {
      DrawComet(first_leds, 128, 3, CRGB::Orange, CRGB::OrangeRed);
      //DrawComet(all_leds, 128, 3, CRGB::Orange, CRGB::OrangeRed);
    }
    FastLED.show(g_Brightness);
  }
}
