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
// History:     Sep-15-2020     davepl      Created
//
//---------------------------------------------------------------------------

#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

#include "ledgfx.h"

static const CRGB TwinkleColors [] = 
{
	CRGB::AliceBlue,             ///< @htmlcolorblock{F0F8FF}
    CRGB::Amethyst,              ///< @htmlcolorblock{9966CC}
    CRGB::AntiqueWhite,          ///< @htmlcolorblock{FAEBD7}
    CRGB::Aqua,                  ///< @htmlcolorblock{00FFFF}
    CRGB::Aquamarine,            ///< @htmlcolorblock{7FFFD4}
    CRGB::Azure,                 ///< @htmlcolorblock{F0FFFF}
    CRGB::Beige,                 ///< @htmlcolorblock{F5F5DC}
    CRGB::Bisque,                ///< @htmlcolorblock{FFE4C4}
    CRGB::Black,                 ///< @htmlcolorblock{000000}
    CRGB::BlanchedAlmond,        ///< @htmlcolorblock{FFEBCD}
    CRGB::Blue,                  ///< @htmlcolorblock{0000FF}
    CRGB::BlueViolet,            ///< @htmlcolorblock{8A2BE2}
    CRGB::Brown,                 ///< @htmlcolorblock{A52A2A}
    CRGB::BurlyWood,             ///< @htmlcolorblock{DEB887}
    CRGB::CadetBlue,             ///< @htmlcolorblock{5F9EA0}
    CRGB::Chartreuse,            ///< @htmlcolorblock{7FFF00}
    CRGB::Chocolate,             ///< @htmlcolorblock{D2691E}
    CRGB::Coral,                 ///< @htmlcolorblock{FF7F50}
    CRGB::CornflowerBlue,        ///< @htmlcolorblock{6495ED}
    CRGB::Cornsilk,              ///< @htmlcolorblock{FFF8DC}
    CRGB::Crimson,               ///< @htmlcolorblock{DC143C}
    CRGB::Cyan,                  ///< @htmlcolorblock{00FFFF}
    CRGB::DarkBlue,              ///< @htmlcolorblock{00008B}
    CRGB::DarkCyan,              ///< @htmlcolorblock{008B8B}
    CRGB::DarkGoldenrod,         ///< @htmlcolorblock{B8860B}
    CRGB::DarkGray,              ///< @htmlcolorblock{A9A9A9}
    CRGB::DarkGrey,              ///< @htmlcolorblock{A9A9A9}
    CRGB::DarkGreen,             ///< @htmlcolorblock{006400}
    CRGB::DarkKhaki,             ///< @htmlcolorblock{BDB76B}
    CRGB::DarkMagenta,           ///< @htmlcolorblock{8B008B}
    CRGB::DarkOliveGreen,        ///< @htmlcolorblock{556B2F}
    CRGB::DarkOrange,            ///< @htmlcolorblock{FF8C00}
    CRGB::DarkOrchid,            ///< @htmlcolorblock{9932CC}
    CRGB::DarkRed,               ///< @htmlcolorblock{8B0000}
    CRGB::DarkSalmon,            ///< @htmlcolorblock{E9967A}
    CRGB::DarkSeaGreen,          ///< @htmlcolorblock{8FBC8F}
    CRGB::DarkSlateBlue,         ///< @htmlcolorblock{483D8B}
    CRGB::DarkSlateGray,         ///< @htmlcolorblock{2F4F4F}
    CRGB::DarkSlateGrey,         ///< @htmlcolorblock{2F4F4F}
    CRGB::DarkTurquoise,         ///< @htmlcolorblock{00CED1}
    CRGB::DarkViolet,            ///< @htmlcolorblock{9400D3}
    CRGB::DeepPink,              ///< @htmlcolorblock{FF1493}
    CRGB::DeepSkyBlue,           ///< @htmlcolorblock{00BFFF}
    CRGB::DimGray,               ///< @htmlcolorblock{696969}
    CRGB::DimGrey,               ///< @htmlcolorblock{696969}
    CRGB::DodgerBlue,            ///< @htmlcolorblock{1E90FF}
    CRGB::FireBrick,             ///< @htmlcolorblock{B22222}
    CRGB::FloralWhite,           ///< @htmlcolorblock{FFFAF0}
    CRGB::ForestGreen,           ///< @htmlcolorblock{228B22}
    CRGB::Fuchsia,               ///< @htmlcolorblock{FF00FF}
    CRGB::Gainsboro,             ///< @htmlcolorblock{DCDCDC}
    CRGB::GhostWhite,            ///< @htmlcolorblock{F8F8FF}
    CRGB::Gold,                  ///< @htmlcolorblock{FFD700}
    CRGB::Goldenrod,             ///< @htmlcolorblock{DAA520}
    CRGB::Gray,                  ///< @htmlcolorblock{808080}
    CRGB::Grey,                  ///< @htmlcolorblock{808080}
    CRGB::Green,                 ///< @htmlcolorblock{008000}
    CRGB::GreenYellow,           ///< @htmlcolorblock{ADFF2F}
    CRGB::Honeydew,              ///< @htmlcolorblock{F0FFF0}
    CRGB::HotPink,               ///< @htmlcolorblock{FF69B4}
    CRGB::IndianRed,             ///< @htmlcolorblock{CD5C5C}
    CRGB::Indigo,                ///< @htmlcolorblock{4B0082}
    CRGB::Ivory,                 ///< @htmlcolorblock{FFFFF0}
    CRGB::Khaki,                 ///< @htmlcolorblock{F0E68C}
    CRGB::Lavender,              ///< @htmlcolorblock{E6E6FA}
    CRGB::LavenderBlush,         ///< @htmlcolorblock{FFF0F5}
    CRGB::LawnGreen,             ///< @htmlcolorblock{7CFC00}
    CRGB::LemonChiffon,          ///< @htmlcolorblock{FFFACD}
    CRGB::LightBlue,             ///< @htmlcolorblock{ADD8E6}
    CRGB::LightCoral,            ///< @htmlcolorblock{F08080}
    CRGB::LightCyan,             ///< @htmlcolorblock{E0FFFF}
    CRGB::LightGoldenrodYellow,  ///< @htmlcolorblock{FAFAD2}
    CRGB::LightGreen,            ///< @htmlcolorblock{90EE90}
    CRGB::LightGrey,             ///< @htmlcolorblock{D3D3D3}
    CRGB::LightPink,             ///< @htmlcolorblock{FFB6C1}
    CRGB::LightSalmon,           ///< @htmlcolorblock{FFA07A}
    CRGB::LightSeaGreen,         ///< @htmlcolorblock{20B2AA}
    CRGB::LightSkyBlue,          ///< @htmlcolorblock{87CEFA}
    CRGB::LightSlateGray,        ///< @htmlcolorblock{778899}
    CRGB::LightSlateGrey,        ///< @htmlcolorblock{778899}
    CRGB::LightSteelBlue,        ///< @htmlcolorblock{B0C4DE}
    CRGB::LightYellow,           ///< @htmlcolorblock{FFFFE0}
    CRGB::Lime,                  ///< @htmlcolorblock{00FF00}
    CRGB::LimeGreen,             ///< @htmlcolorblock{32CD32}
    CRGB::Linen,                 ///< @htmlcolorblock{FAF0E6}
    CRGB::Magenta,               ///< @htmlcolorblock{FF00FF}
    CRGB::Maroon,                ///< @htmlcolorblock{800000}
    CRGB::MediumAquamarine,      ///< @htmlcolorblock{66CDAA}
    CRGB::MediumBlue,            ///< @htmlcolorblock{0000CD}
    CRGB::MediumOrchid,          ///< @htmlcolorblock{BA55D3}
    CRGB::MediumPurple,          ///< @htmlcolorblock{9370DB}
    CRGB::MediumSeaGreen,        ///< @htmlcolorblock{3CB371}
    CRGB::MediumSlateBlue,       ///< @htmlcolorblock{7B68EE}
    CRGB::MediumSpringGreen,     ///< @htmlcolorblock{00FA9A}
    CRGB::MediumTurquoise,       ///< @htmlcolorblock{48D1CC}
    CRGB::MediumVioletRed,       ///< @htmlcolorblock{C71585}
    CRGB::MidnightBlue,          ///< @htmlcolorblock{191970}
    CRGB::MintCream,             ///< @htmlcolorblock{F5FFFA}
    CRGB::MistyRose,             ///< @htmlcolorblock{FFE4E1}
    CRGB::Moccasin,              ///< @htmlcolorblock{FFE4B5}
    CRGB::NavajoWhite,           ///< @htmlcolorblock{FFDEAD}
    CRGB::Navy,                  ///< @htmlcolorblock{000080}
    CRGB::OldLace,               ///< @htmlcolorblock{FDF5E6}
    CRGB::Olive,                 ///< @htmlcolorblock{808000}
    CRGB::OliveDrab,             ///< @htmlcolorblock{6B8E23}
    CRGB::Orange,                ///< @htmlcolorblock{FFA500}
    CRGB::OrangeRed,             ///< @htmlcolorblock{FF4500}
    CRGB::Orchid,                ///< @htmlcolorblock{DA70D6}
    CRGB::PaleGoldenrod,         ///< @htmlcolorblock{EEE8AA}
    CRGB::PaleGreen,             ///< @htmlcolorblock{98FB98}
    CRGB::PaleTurquoise,         ///< @htmlcolorblock{AFEEEE}
    CRGB::PaleVioletRed,         ///< @htmlcolorblock{DB7093}
    CRGB::PapayaWhip,            ///< @htmlcolorblock{FFEFD5}
    CRGB::PeachPuff,             ///< @htmlcolorblock{FFDAB9}
    CRGB::Peru,                  ///< @htmlcolorblock{CD853F}
    CRGB::Pink,                  ///< @htmlcolorblock{FFC0CB}
    CRGB::Plaid,                 ///< @htmlcolorblock{CC5533}
    CRGB::Plum,                  ///< @htmlcolorblock{DDA0DD}
    CRGB::PowderBlue,            ///< @htmlcolorblock{B0E0E6}
    CRGB::Purple,                ///< @htmlcolorblock{800080}
    CRGB::Red,                   ///< @htmlcolorblock{FF0000}
    CRGB::RosyBrown,             ///< @htmlcolorblock{BC8F8F}
    CRGB::RoyalBlue,             ///< @htmlcolorblock{4169E1}
    CRGB::SaddleBrown,           ///< @htmlcolorblock{8B4513}
    CRGB::Salmon,                ///< @htmlcolorblock{FA8072}
    CRGB::SandyBrown,            ///< @htmlcolorblock{F4A460}
    CRGB::SeaGreen,              ///< @htmlcolorblock{2E8B57}
    CRGB::Seashell,              ///< @htmlcolorblock{FFF5EE}
    CRGB::Sienna,                ///< @htmlcolorblock{A0522D}
    CRGB::Silver,                ///< @htmlcolorblock{C0C0C0}
    CRGB::SkyBlue,               ///< @htmlcolorblock{87CEEB}
    CRGB::SlateBlue,             ///< @htmlcolorblock{6A5ACD}
    CRGB::SlateGray,             ///< @htmlcolorblock{708090}
    CRGB::SlateGrey,             ///< @htmlcolorblock{708090}
    CRGB::Snow,                  ///< @htmlcolorblock{FFFAFA}
    CRGB::SpringGreen,           ///< @htmlcolorblock{00FF7F}
    CRGB::SteelBlue,             ///< @htmlcolorblock{4682B4}
    CRGB::Tan,                   ///< @htmlcolorblock{D2B48C}
    CRGB::Teal,                  ///< @htmlcolorblock{008080}
    CRGB::Thistle,               ///< @htmlcolorblock{D8BFD8}
    CRGB::Tomato,                ///< @htmlcolorblock{FF6347}
    CRGB::Turquoise,             ///< @htmlcolorblock{40E0D0}
    CRGB::Violet,                ///< @htmlcolorblock{EE82EE}
    CRGB::Wheat,                 ///< @htmlcolorblock{F5DEB3}
    CRGB::White,                 ///< @htmlcolorblock{FFFFFF}
    CRGB::WhiteSmoke,            ///< @htmlcolorblock{F5F5F5}
    CRGB::Yellow,                ///< @htmlcolorblock{FFFF00}
    CRGB::YellowGreen           ///< @htmlcolorblock{9ACD32}
};

void DrawTwinkle()
{
	static int passCount = 0;
	if (passCount++ == FastLED.size()/4)
	{
		passCount = 0;
		FastLED.clear(false);
	}
	FastLED.leds()[random(FastLED.size())] = TwinkleColors[random(0, ARRAYSIZE(TwinkleColors))];
	//delay(50);       
}
