#pragma once

//
// CCHudColoursDefault.h
//
// This file contains RGB colour values for each HUD component.
// Please ensure you change the correct values; wrong values may cause the modification to work improperly.
//

#include "CRGBA.h" 

namespace CHudColoursDefault {

    // Basic HUD colours
    static const CRGBA HUD_COLOUR_RED(255, 38, 41, 255);
    static const CRGBA HUD_COLOUR_GREEN(82, 157, 67, 255);
    static const CRGBA HUD_COLOUR_BLUEDARK(50, 60, 127, 255);
    static const CRGBA HUD_COLOUR_BLUELIGHT(172, 203, 241, 255);
    static const CRGBA HUD_COLOUR_WHITE(255, 255, 255, 255);
    static const CRGBA HUD_COLOUR_BLACK(0, 0, 0, 255);
    static const CRGBA HUD_COLOUR_ORANGE(215, 146, 24, 255);
    static const CRGBA HUD_COLOUR_PURPLE(168, 110, 252, 255);
    static const CRGBA HUD_COLOUR_GREY(150, 150, 150, 255);
    static const CRGBA HUD_COLOUR_REDDARK(104, 15, 17, 255);
    static const CRGBA HUD_COLOUR_GREENDARK(38, 71, 31, 255);
    static const CRGBA HUD_COLOUR_ORANGELIGHT(226, 192, 99, 255);
    static const CRGBA HUD_COLOUR_GREYDARK(74, 90, 107, 255);
    static const CRGBA HUD_COLOUR_BLUE(20, 25, 200, 255);
    static const CRGBA HUD_COLOUR_YELLOW(255, 255, 0, 255);

    // Additional HUD colours
    static const CRGBA HUD_COLOUR_CLOCK(255, 255, 255, 200);
    static const CRGBA HUD_COLOUR_CASH(82, 157, 67, 200);
    static const CRGBA HUD_COLOUR_HEALTH(227, 91, 148, 200);
    static const CRGBA HUD_COLOUR_ARMOUR(9, 255, 250, 200);
    static const CRGBA HUD_COLOUR_BREATH(0, 30, 117, 255);
    static const CRGBA HUD_COLOUR_WEAPON_ICON(255, 255, 255, 200);
    static const CRGBA HUD_COLOUR_AMMO(255, 255, 255, 255);
    static const CRGBA HUD_COLOUR_WANTED_N(0, 0, 0, 0);
    static const CRGBA HUD_COLOUR_WANTED_A(207, 149, 54, 200);
    static const CRGBA HUD_COLOUR_ZONE_NAME(235, 235, 235, 255);
    static const CRGBA HUD_COLOUR_VEHICLE_NAME(235, 235, 235, 255);
    static const CRGBA HUD_COLOUR_RADIO_NAME_N(105, 154, 191, 255);
    static const CRGBA HUD_COLOUR_RADIO_NAME_A(78, 142, 190, 255);
    static const CRGBA HUD_COLOUR_HELP_TEXT(235, 235, 235, 255);
    static const CRGBA HUD_COLOUR_HELP_BOX(0, 0, 0, 125);
    static const CRGBA HUD_COLOUR_SUBTITLES(235, 235, 235, 255);
    static const CRGBA HUD_COLOUR_WASTED(27, 169, 225, 255);
    static const CRGBA HUD_COLOUR_BUSTED(207, 20, 27, 255);
    static const CRGBA HUD_COLOUR_MISSION_RESULT(227, 91, 148, 200);
    static const CRGBA HUD_COLOUR_MISSION_TITLE(215, 146, 24, 255);
	static const CRGBA HUD_COLOUR_DAMAGE(255, 0, 0, 255);

} // namespace CHudColoursDefault