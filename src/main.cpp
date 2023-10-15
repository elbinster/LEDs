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
#define LED_PIN       13

CRGB g_LEDs[NUM_LEDS] = {0};    // Frame buffer for FastLED
static int g_Brightness = 16;
static int g_PowerLimit = 900;

#include "ledgfx.h"
#include "comet.h"
#include "marquee.h"
#include "twinkle.h"
#include "fire.h"

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(g_LEDs, NUM_LEDS);               // Add our LED strip to the FastLED library
  FastLED.setBrightness(g_Brightness);
  set_max_power_indicator_LED(LED_BUILTIN);                               // Light the builtin LED if we power throttle
  FastLED.setMaxPowerInMilliWatts(g_PowerLimit);                          // Set the power limit, above which brightness will be throttled
}

void DrawMarqueeComparison()
{
  static float scroll = 0.0f;
  scroll += 0.1f;
  if (scroll > 5.0)
    scroll -= 5.0;

  for (float i = scroll; i < NUM_LEDS/2 -1; i+= 5)
  {
    DrawPixels(i, 3, CRGB::Green);
    DrawPixels(NUM_LEDS-1-(int)i, 3, CRGB::Red);
  }
}

void loop() 
{
  bool bLED = 0;

  while (true)
  {
    FastLED.clear();
    //DrawMarqueeComparison();
    DrawComet();

    /*
    // RGB Spinners
    float b = beat16(60) / 65535.0f * FAN_SIZE;
    DrawFanPixels(b, 1, CRGB::Red,   Sequential,  0);
    DrawFanPixels(b, 1, CRGB::Green, Sequential,  1);
    DrawFanPixels(b, 1, CRGB::Blue,  Sequential,  2);
    */

    /*
    // Left to Right Cyan Wipe
    float b = beatsin16(60) / 65535.0f * FAN_SIZE;
    for (int iFan = 0; iFan < NUM_FANS; iFan++)
      DrawFanPixels(0, b, CRGB::Cyan, LeftRight, iFan);
    */

    /* Right to Left Cyan Wipe
    float b = beatsin16(60) / 65535.0f * FAN_SIZE;
    for (int iFan = 0; iFan < NUM_FANS; iFan++)
      DrawFanPixels(0, b, CRGB::Cyan, RightLeft, iFan);
    */

    /*
    // Bottom Up Green Wipe
    float b = beatsin16(60) / 65535.0f * NUM_LEDS;
      DrawFanPixels(0, b, CRGB::Green, BottomUp);
    */

    /*
    // Top Down Green Wipe
    float b = beatsin16(60) / 65535.0f * NUM_LEDS;
        DrawFanPixels(0, b, CRGB::Green, TopDown);    
    */

    /*
    // Simple Color Cycle
    static byte hue = 0;
    for (int i = 0; i < NUM_LEDS; i++)
      DrawFanPixels(i, 1, CHSV(hue, 255, 255));
    hue += 4;
    */

    /*
    // Sequential Color Rainbows
    static byte basehue = 0;
    byte hue = basehue;
    basehue += 4;
    for (int i = 0; i < NUM_LEDS; i++)
      DrawFanPixels(i, 1, CHSV(hue+=16, 255, 255));
    basehue += 4;
    */

    /*
    // Vertical Rainbow Wipe
    static byte basehue = 0;
    byte hue = basehue;
    basehue += 8;
    for (int i = 0; i < NUM_LEDS; i++)
      DrawFanPixels(i, 1, CHSV(hue+=16, 255, 255), LeftRight);
    */

    /*
    static byte basehue = 0;
    byte hue = basehue;
    basehue += 8;
    for (int i = 0; i < NUM_LEDS; i++)
      DrawFanPixels(i, 1, CHSV(hue+=16, 255, 255), BottomUp);
    */

    /*
    // Rainbow Strip Palette Effect
    static CRGBPalette256 pal(RainbowStripeColors_p);
    static byte baseColor = 0;
    byte hue = baseColor;
    for (int i = 0; i < NUM_LEDS; i++)
      DrawFanPixels(i, 1, ColorFromPalette(pal, hue += 4), BottomUp);
    baseColor += 1;
    */

    /*
    // vu-style Meter bar
    int b = beatsin16(30) * NUM_LEDS / 65535L;
    static const CRGBPalette256 vuPaletteGreen = vu_gpGreen;
    for (int i = 0; i < b; i++)
      DrawFanPixels(i, 1, ColorFromPalette(vuPaletteGreen, (int)(255 * i / NUM_LEDS)), BottomUp);
    */

    /*
    // Sequential Fire Fans
    static FireEffect fire(NUM_LEDS, 20, 100, 3, NUM_LEDS, true, false);
    fire.DrawFire();
    */

    /*
    // Bottom Up Fire Effect with extra sparking on first fan only
    static FireEffect fire(NUM_LEDS, 20, 140, 3, FAN_SIZE, true, false);
    fire.DrawFire(BottomUp);
    */

    // LeftRight (Wide Style) Fire Effect with extra sparking on first fan only

    /*
    static FireEffect fire(NUM_LEDS, 20, 140, 3, FAN_SIZE, true, false);
    fire.DrawFire(LeftRight);
    for (int i = 0; i < FAN_SIZE; i++)
    {
      g_LEDs[i] = g_LEDs[i + 2 * FAN_SIZE];
      g_LEDs[i + FAN_SIZE] = g_LEDs[i + 2 * FAN_SIZE];
    }
    */

  /*
   int b = beatsin16(30) * NUM_LEDS / 65535L;
   static const CRGBPalette256 seahawksPalette = gpSeahawks;
   for (int i = 0; i < NUM_LEDS; i++)
      DrawFanPixels(i, 1, ColorFromPalette(seahawksPalette, beat8(64) + (int)(255 * i / NUM_LEDS)), BottomUp);
  
    */

    FastLED.show(g_Brightness);                          //  Show and delay
    delay(33);
  }
}
