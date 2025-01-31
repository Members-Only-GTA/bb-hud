#pragma once
#include "CHud.h"

enum eHudSettings {
    HUD_RADAR,
    HUD_RADAR_RECT,
    HUD_RADAR_MASK,
    HUD_RADAR_DAMAGE,
    HUD_RADAR_FOREGROUND,
    HUD_RADAR_BACKGROUND,
    HUD_RADAR_BACKGROUND_P2,
    HUD_RADAR_BLIPS_SIZE,
    HUD_RADAR_BLIPS_LEVEL_SIZE,
    HUD_RADAR_BLIPS_COP_SIZE,
    HUD_RADAR_BLIPS_COP_HELI_SIZE,
    HUD_RADAR_BLIPS_BORDER_SIZE,
    HUD_HEALTH_BAR,
    HUD_ARMOUR_BAR,
    HUD_ARMOUR_BAR_B,
    HUD_BREATH_BAR,
    HUD_NITRO_BAR,
    HUD_NITRO_TEXT,
    HUD_HEALTH_BAR_P2,
    HUD_ARMOUR_BAR_P2,
    HUD_ARMOUR_BAR_B_P2,
    HUD_BREATH_BAR_P2,
    HUD_RADAR_GPS_LINE,
    HUD_RADAR_GPS_RECT,
    HUD_RADAR_GPS_DIST_TEXT,
    HUD_RADAR_GPS_DIST_ARROW,
    HUD_SUBTITLES,
    HUD_WANTED_STARS,
    HUD_CASH,
    HUD_AMMO,
    HUD_WEAPON_WHEEL,
    HUD_WEAPON_WHEEL_MOUSE_LINE,
    HUD_WEAPON_STATS_BOX,
    HUD_WEAPON_STATS_BAR,
    HUD_VEHICLE_NAME,
    HUD_ZONE_NAME,
    HUD_LEVEL_NAME,
    HUD_HELP_BOX_TEXT,
    HUD_HELP_BOX_BORDER,
    HUD_HELP_BOX_SMALL_TEXT,
    HUD_HELP_BOX_SMALL_BORDER,
    HUD_CROSSHAIR_DOT,
    HUD_CROSSHAIR_CROSS,
    HUD_VITAL_STATS,
    HUD_PLAYER_WHEEL,
    HUD_WASTED_TEXT,
    HUD_BUSTED_TEXT,
    HUD_BIG_MESSAGE,
    HUD_MISSION_TITLE,
    HUD_MISSION_TIMERS,

    NUM_HUD_SETTINGS,
};

class CHudSetting {
public:
    char name[64];
    float x, y, w, h;
    CRGBA col;

    CHudSetting() {
        strcpy(name, "NONE");
        x = y = w = h = 0.0f;
        col = { 0, 0, 0, 0 };
    }
};

class CHudNew : CHud {
public:
    static CHudSetting m_HudList[256];

    static bool bInitialised;
    static bool bShowMoney;
    static bool bShowMoneyDifference;
    static int nMoneyFadeAlpha;
    static int nMoneyDifferenceFadeAlpha;
    static int nTimeToShowMoney;
    static int nTimeToShowMoneyDifference;

    static bool bShowAmmo;
    static int nAmmoFadeAlpha;
    static int nTimeToShowAmmoDifference;

    static int m_nPreviousMoney;
    static int m_nDiffMoney;

    static int nTargettedEntityDeathTime;

    static bool m_bShowMissionText;
    static char m_LastMissionName[128];

    static bool m_bShowWastedBusted;
    static bool m_bShowSuccessFailed;
    static int m_nBigMessageTime;
    static int m_nBigMessageTime2;
    static float m_fBigMessageOffset;
    static CRGBA m_BigMessageColor;
    static char m_SuccessFailedText[2][128];
    static int m_nMiddleTopMessageTime;
    static char m_MiddleTopMessage[16][128];
    static char m_MiddleTopSubMessage[128];
    static int m_nCurrentMiddleTopMessage;
    static bool m_bShowMiddleTopMessage;
    static int m_nMiddleTopMessageIdToSet;

    static char m_CurrentLevelName[128];
    static int m_nLevelNameState;

    static int previousModelIndex[4];

    static char* MissionTimersString[5][2];
    static int nTimersCount;

public:
    static void Init();
    static void ReInit();
    static void Shutdown();
    static void ReadSettingsFromFile();
    static CHudSetting GetSetting(int setting);
    static CHudSetting GetSetting(char* name);
    static void Draw();
	static void DrawHealth();
	static void DrawArmour();
    static void DrawMoneyCounter();
};