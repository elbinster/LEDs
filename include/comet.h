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
// History:     Sep-28-2020     davepl      Created
//
//---------------------------------------------------------------------------

#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

void DrawComet(int end, int start = 0, byte fadeAmt = 128, int cometSize = 5)
{
    //end = min(start, end);
    static CRGB hue1 = AllColors[random(0, ARRAYSIZE(AllColors))];
    //static CRGB hue1 =  CRGB::Crimson;
    static CRGB hue2 = CRGB::DarkSeaGreen;

    static bool fwd = true;
    static int iPos = start;

    if (iPos <= start)
        fwd = true;
    if (iPos + cometSize >= end)
        fwd = false;
    
    if (fwd)
        iPos++;
    else
        iPos--;
    
    for (int i = 0; i < cometSize; i++)
        if (fwd)
            FastLED.leds()[iPos+i] = hue1;
        else
            FastLED.leds()[iPos+i] = hue2;

    // Randomly fade the LEDs
    for (int j = start; j < end; j++)
        if (random(10) > 5)
            //FastLED.leds()[j] = FastLED.leds()[j].fadeToBlackBy(255-fadeAmt);     // Looks cool with max fade
            FastLED.leds()[j].fadeToBlackBy(fadeAmt);
}