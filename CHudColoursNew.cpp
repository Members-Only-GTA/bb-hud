#include "plugin.h"
#include "CHudColours.h"
#include "CHudColoursNew.h"
#include "Settings.h"

#include "CHudColoursDefault.h"

using namespace plugin;

CHudColoursNew HudColourNew;

CHudColoursNew::CHudColoursNew() {
	patch::RedirectJump(0x58FDA0, CHudColoursNew::ReadDefaultColors);
}

void CHudColoursNew::Initialise() {
    // Assign original game colors from CCHudColoursDefault
    HUD_COLOUR_RED = CHudColoursDefault::HUD_COLOUR_RED;
    HUD_COLOUR_GREEN = CHudColoursDefault::HUD_COLOUR_GREEN;
    HUD_COLOUR_BLUEDARK = CHudColoursDefault::HUD_COLOUR_BLUEDARK;
    HUD_COLOUR_BLUELIGHT = CHudColoursDefault::HUD_COLOUR_BLUELIGHT;
    HUD_COLOUR_WHITE = CHudColoursDefault::HUD_COLOUR_WHITE;
    HUD_COLOUR_BLACK = CHudColoursDefault::HUD_COLOUR_BLACK;
    HUD_COLOUR_ORANGE = CHudColoursDefault::HUD_COLOUR_ORANGE;
    HUD_COLOUR_PURPLE = CHudColoursDefault::HUD_COLOUR_PURPLE;
    HUD_COLOUR_GREY = CHudColoursDefault::HUD_COLOUR_GREY;
    HUD_COLOUR_REDDARK = CHudColoursDefault::HUD_COLOUR_REDDARK;
    HUD_COLOUR_GREENDARK = CHudColoursDefault::HUD_COLOUR_GREENDARK;
    HUD_COLOUR_ORANGELIGHT = CHudColoursDefault::HUD_COLOUR_ORANGELIGHT;
    HUD_COLOUR_GREYDARK = CHudColoursDefault::HUD_COLOUR_GREYDARK;
    HUD_COLOUR_BLUE = CHudColoursDefault::HUD_COLOUR_BLUE;
    HUD_COLOUR_YELLOW = CHudColoursDefault::HUD_COLOUR_YELLOW;

    // Assign BB HUD colors from CCHudColoursDefault (if available)
    HUD_COLOUR_CLOCK = CHudColoursDefault::HUD_COLOUR_CLOCK;
    HUD_COLOUR_CASH = CHudColoursDefault::HUD_COLOUR_CASH;
    HUD_COLOUR_HEALTH = CHudColoursDefault::HUD_COLOUR_HEALTH;
    HUD_COLOUR_ARMOUR = CHudColoursDefault::HUD_COLOUR_ARMOUR;
    HUD_COLOUR_BREATH = CHudColoursDefault::HUD_COLOUR_BREATH;
    HUD_COLOUR_WEAPON_ICON = CHudColoursDefault::HUD_COLOUR_WEAPON_ICON;
    HUD_COLOUR_AMMO = CHudColoursDefault::HUD_COLOUR_AMMO;
    HUD_COLOUR_WANTED_N = CHudColoursDefault::HUD_COLOUR_WANTED_N;
    HUD_COLOUR_WANTED_A = CHudColoursDefault::HUD_COLOUR_WANTED_A;
    HUD_COLOUR_ZONE_NAME = CHudColoursDefault::HUD_COLOUR_ZONE_NAME;
    HUD_COLOUR_VEHICLE_NAME = CHudColoursDefault::HUD_COLOUR_VEHICLE_NAME;
    HUD_COLOUR_RADIO_NAME_N = CHudColoursDefault::HUD_COLOUR_RADIO_NAME_N;
    HUD_COLOUR_RADIO_NAME_A = CHudColoursDefault::HUD_COLOUR_RADIO_NAME_A;
    HUD_COLOUR_HELP_TEXT = CHudColoursDefault::HUD_COLOUR_HELP_TEXT;
    HUD_COLOUR_HELP_BOX = CHudColoursDefault::HUD_COLOUR_HELP_BOX;
    HUD_COLOUR_SUBTITLES = CHudColoursDefault::HUD_COLOUR_SUBTITLES;
    HUD_COLOUR_WASTED = CHudColoursDefault::HUD_COLOUR_WASTED;
    HUD_COLOUR_BUSTED = CHudColoursDefault::HUD_COLOUR_BUSTED;
    HUD_COLOUR_MISSION_RESULT = CHudColoursDefault::HUD_COLOUR_MISSION_RESULT;
    HUD_COLOUR_MISSION_TITLE = CHudColoursDefault::HUD_COLOUR_MISSION_TITLE;
	HUD_COLOUR_DAMAGE = CHudColoursDefault::HUD_COLOUR_DAMAGE;
}

void CHudColoursNew::Shutdown() {
	;;
}

void __fastcall CHudColoursNew::ReadDefaultColors(CRGBA* color, int) {
	HudColourNew.Initialise();

	CRGBA DefaultColorList[] = {
		HudColourNew.HUD_COLOUR_RED,
		HudColourNew.HUD_COLOUR_GREEN,
		HudColourNew.HUD_COLOUR_BLUEDARK,
		HudColourNew.HUD_COLOUR_BLUELIGHT,
		HudColourNew.HUD_COLOUR_WHITE,
		HudColourNew.HUD_COLOUR_BLACK,
		HudColourNew.HUD_COLOUR_ORANGE,
		HudColourNew.HUD_COLOUR_PURPLE,
		HudColourNew.HUD_COLOUR_GREY,
		HudColourNew.HUD_COLOUR_REDDARK,
		HudColourNew.HUD_COLOUR_GREENDARK,
		HudColourNew.HUD_COLOUR_ORANGELIGHT,
		HudColourNew.HUD_COLOUR_GREYDARK,
		HudColourNew.HUD_COLOUR_BLUE,
		HudColourNew.HUD_COLOUR_YELLOW,
	};

	for (int i = 0; i < 15; i++)
		color[i] = DefaultColorList[i];
}