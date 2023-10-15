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

void DrawComet()
{
    const byte fadeAmt = 2;
    const int cometSize = 5;

    static byte hue1 = HUE_PURPLE;
    static byte hue2 = HUE_GREEN;
    static bool fwd = true;
    static int iPos = 0;

    if (iPos <= 0)
        fwd = true;
    if (iPos + cometSize >= FastLED.size())
        fwd = false;
    
    if (fwd)
        iPos++;
    if (!fwd)
        iPos--;
    
    for (int i = 0; i < cometSize; i++)
    {
        if (fwd)
            FastLED.leds()[iPos+i].setHue(hue1);
        if (!fwd)
            FastLED.leds()[iPos+i].setHue(hue2);
    }

    // Randomly fade the LEDs
    for (int j = 0; j < FastLED.size(); j++)
        if (random(10) > 3)
            FastLED.leds()[j] = FastLED.leds()[j].fadeToBlackBy(fadeAmt);

    delay(10);
}