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

void DrawComet(int num)
{
    const byte fadeAmt = 128;
    const int cometSize = 5;

    static CRGB hue1 = AllColors[random(0, ARRAYSIZE(AllColors))];
    //static CRGB hue1 =  CRGB::Crimson;
    static CRGB hue2 = CRGB::DarkSeaGreen;

    static bool fwd = true;
    static int iPos = 0;

    if (iPos <= 0)
        fwd = true;
    if (iPos + cometSize >= num)
        fwd = false;
    
    if (fwd)
        iPos++;
    if (!fwd)
        iPos--;
    
    for (int i = 0; i < cometSize; i++)
    {
        if (fwd)
            FastLED.leds()[iPos+i] = hue1;
        else
            FastLED.leds()[iPos+i] = hue2;
    }

    // Randomly fade the LEDs
    for (int j = 0; j < num; j++)
        if (random(10) > 5)
            //FastLED.leds()[j] = FastLED.leds()[j].fadeToBlackBy(255-fadeAmt);     // Looks cool with max fade
            FastLED.leds()[j].fadeToBlackBy(fadeAmt);

    //delay(10);
}