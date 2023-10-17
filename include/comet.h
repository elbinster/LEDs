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

void DrawComet(CRGBSet leds, byte fadeAmt = 128, int cometSize = 5, CRGB hue1 = CRGB::Red, CRGB hue2 = CRGB::Green)
{
 
    static bool fwd = true;
    static int iPos = 0;
    static uint8_t numLeds = leds.len;

    if (iPos <= 0)
        fwd = true;
    if (iPos + cometSize >= numLeds)
        fwd = false;
    
    if (fwd)
        iPos++;
    else
        iPos--;
    
    for (int i = 0; i < cometSize; i++)
        if (fwd)
            leds[iPos+i] = hue1;
        else
            leds[iPos+i] = hue2;

    // Randomly fade the LEDs
    for (int j = 0; j < numLeds; j++)
        if (random(10) > 5)
            //leds[j] = leds[j].fadeToBlackBy(255-fadeAmt);     // Looks cool with max fade
            leds[j].fadeToBlackBy(fadeAmt);
    delay(30);
}