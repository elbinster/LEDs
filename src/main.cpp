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
static int g_Brightness = 32;
static int g_PowerLimit = 3000;

#include "ledgfx.h"
#include "comet.h"
#include "marquee.h"
#include "twinkle.h"
#include "fire.h"
#include "fire2.h"
//#include "bounce.h"     // Bounce ain't gonna work without a cock

static FireEffect_orig fire(NUM_LEDS-1);
static FireEffect fire1(NUM_LEDS/3-1, 0, 75, 100, 30, 10, true, false);
static FireEffect fire2(NUM_LEDS/4, NUM_LEDS/2, 250, 200, 30, 10, false, false);

void setup() 
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(g_LEDs, NUM_LEDS);               // Add our LED strip to the FastLED library
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
    DrawPixels(NUM_LEDS-1-i, 3, color1);
    DrawPixels((int)i, 3, color2);
  }
}

void loop() 
{

  while (true)
  {
    //DrawMarqueeComparison();
    //DrawTwinkle(NUM_LEDS/4-1, 0, 40, 16);
    //DrawMarquee(NUM_LEDS/2, NUM_LEDS/4, 32, false, 8);
    DrawMarqueeMirrored(NUM_LEDS/2, NUM_LEDS/4, 32, false, 8);
    //DrawComet(NUM_LEDS-1, NUM_LEDS/2,);
    
    // Fire needs extras
    //static FireEffect fire(50, 0, 20, 100, 9, 4, false, false);
    //fire.DrawFire();      // Original DrawFire
    //fire1.DrawFire();   // New DrawFire, first half of string
    //fire2.DrawFire();   // New DrawFire, second half of string

    FastLED.show(g_Brightness);
    delay(25);
  }
}
