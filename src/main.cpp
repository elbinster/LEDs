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

#define NUM_LEDS      200       // FastLED definitions
#define LED_PIN       12

CRGB g_LEDs[NUM_LEDS] = {0};    // Frame buffer for FastLED
static int g_Brightness = 200;
static int g_PowerLimit = 1500;

#include "ledgfx.h"
#include "comet.h"
#include "marquee.h"
#include "twinkle.h"
#include "fire.h"

void setup() 
{
  //Serial.begin(57600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(g_LEDs, NUM_LEDS);               // Add our LED strip to the FastLED library
  FastLED.setBrightness(g_Brightness);
  set_max_power_indicator_LED(LED_BUILTIN);                               // Light the builtin LED if we power throttle
  FastLED.setMaxPowerInMilliWatts(g_PowerLimit);                          // Set the power limit, above which brightness will be throttled
  FastLED.clear();
}

void DrawMarqueeComparison()
{
  static float scroll = 0.0f;
  scroll += 0.1f;
  if (scroll > 5.0)
    scroll -= 5.0;

  for (float i = scroll; i < NUM_LEDS/2 -1; i+= 5)
  {
    DrawPixels(i, 3, CRGB::DarkGoldenrod);
    DrawPixels(NUM_LEDS-2-(int)i, 3, CRGB::Amethyst);
  }
}

void loop() 
{

  while (true)
  {
    FastLED.clear();
    //DrawMarqueeComparison();
    //DrawComet();
    DrawTwinkle();


    FastLED.show();
    delay(25);
  }
}
