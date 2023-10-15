//+--------------------------------------------------------------------------
//
// NightDriver - (c) 2020 Dave Plummer.  All Rights Reserved.
//
// File:        marque.h
//
// Description:
//
//   Draws a theatre-style marquee
//
// History:     Sep-15-2020     davepl      Created
//
//---------------------------------------------------------------------------

#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>


void DrawMarquee(int end, int start = 0, int hue = 8, bool clear = true, int clearMod = 8)
{
    end = max(start, end);
    static byte j = 0;
    j+=4;
    byte k = j;

    // Roughly equivalent to fill_rainbow(g_LEDs, NUM_LEDS, j, 8);

    CRGB c;
    for (int i = start; i < end; i ++)
        FastLED.leds()[i] = c.setHue(k+=hue);

    static int scroll = start;
    scroll++;

    if (clear)
        for (int i = scroll % clearMod; i < end - 1; i += clearMod)
            FastLED.leds()[i] = CRGB::Black;
}

void DrawMarqueeMirrored(int end, int start = 0, int hue = 8, bool clear = true, int clearMod = 8)
{
    end = max(start, end);
    static byte j = 0;
    j+=4;
    byte k = j;

    // Roughly equivalent to fill_rainbow(g_LEDs, NUM_LEDS, j, 8);

    CRGB c;
    for (int i = start; i < (start + end + 1) / 2; i ++)
    {
        FastLED.leds()[i] = c.setHue(k);
        FastLED.leds()[end - 1 - i] = c.setHue(k);
        k+= hue;
    }


    static int scroll = start;
    scroll++;

    if (clear)
        for (int i = scroll % clearMod; i < end / 2; i += clearMod)
        {
            FastLED.leds()[i] = CRGB::Black;
            FastLED.leds()[end - 1 - i] = CRGB::Black;
        }   
}



