#include "BBHud.h"
#include "HudColoursNew.h"
#include "HudNew.h"

#include "CFont.h"
#include "CWorld.h"

#include "Utility.h"

using namespace plugin;

CHudNew HudNew;

CHudSetting CHudNew::m_HudList[256];

bool CHudNew::bInitialised = false;
bool CHudNew::bShowMoney;
bool CHudNew::bShowMoneyDifference;
int CHudNew::nMoneyFadeAlpha;
int CHudNew::nMoneyDifferenceFadeAlpha;
int CHudNew::nTimeToShowMoney;
int CHudNew::nTimeToShowMoneyDifference;

bool CHudNew::bShowAmmo;
int CHudNew::nAmmoFadeAlpha;
int CHudNew::nTimeToShowAmmoDifference;

int CHudNew::m_nPreviousMoney;
int CHudNew::m_nDiffMoney;
int CHudNew::nTargettedEntityDeathTime;

bool CHudNew::m_bShowMissionText;
char CHudNew::m_LastMissionName[128];
bool CHudNew::m_bShowWastedBusted;
bool CHudNew::m_bShowSuccessFailed;
int CHudNew::m_nBigMessageTime;
int CHudNew::m_nBigMessageTime2;
float CHudNew::m_fBigMessageOffset;
CRGBA CHudNew::m_BigMessageColor;
char CHudNew::m_SuccessFailedText[2][128];
int CHudNew::m_nMiddleTopMessageTime;
char CHudNew::m_MiddleTopMessage[16][128];
char CHudNew::m_MiddleTopSubMessage[128];

int CHudNew::m_nCurrentMiddleTopMessage;
bool CHudNew::m_bShowMiddleTopMessage;
int CHudNew::m_nMiddleTopMessageIdToSet;

char CHudNew::m_CurrentLevelName[128];
int CHudNew::m_nLevelNameState;

int CHudNew::previousModelIndex[4];
char* CHudNew::MissionTimersString[5][2];
int CHudNew::nTimersCount;

void* simple_mask_fxc;

static LateStaticInit InstallHooks([]() {
    patch::RedirectJump(0x58FAE0, CHudNew::Draw);
    //patch::RedirectJump(0x58D490, CHudNew::DrawAfterFade);

});

void CHudNew::Init() {
	if (bInitialised)
		return;
	
	ReInit();
	bInitialised = true;
}

void CHudNew::ReInit() {
    bShowMoney = false;
    bShowMoneyDifference = false;
    nMoneyFadeAlpha = 0;
    nMoneyDifferenceFadeAlpha = 0;
    nTimeToShowMoneyDifference = 0;

    bShowAmmo = false;
    nAmmoFadeAlpha = 0;
    nTimeToShowAmmoDifference = 0;

    if (CWorld::Players[CWorld::PlayerInFocus].m_pPed)
        m_nPreviousMoney = CWorld::Players[CWorld::PlayerInFocus].m_nMoney;
    else
        m_nPreviousMoney = 0;

    m_nDiffMoney = 0;
    nTargettedEntityDeathTime = 0;

    m_bShowWastedBusted = false;
    m_bShowSuccessFailed = false;
    m_nBigMessageTime = -1;
    m_nBigMessageTime2 = -1;
    m_fBigMessageOffset = 0.0f;
    m_SuccessFailedText[0][0] = NULL;
    m_SuccessFailedText[1][0] = NULL;
    m_BigMessageColor = { 255, 255, 255, 255 };

    m_nMiddleTopMessageTime = 0;

    for (int i = 0; i < 16; i++) {
        m_MiddleTopMessage[i][0] = '\0';
    }
    m_MiddleTopSubMessage[0] = '\0';

    m_nCurrentMiddleTopMessage = 0;
    m_bShowMiddleTopMessage = false;
    m_nMiddleTopMessageIdToSet = 0;

    m_bShowMissionText = false;

    for (int i = 0; i < 4; i++) {
        previousModelIndex[i] = MODEL_NULL;
    }

    bDrawingVitalStats = false;

    nTimersCount = 0;
}

void CHudNew::Shutdown() {
    if (!bInitialised)
        return;

    bInitialised = false;
}

void CHudNew::Draw() {
    if (CWorld::Players[0].m_pPed) {
        DrawMoneyCounter();
        DrawHealth();
		DrawArmour();
    }
}

void CHudNew::DrawMoneyCounter() {
    CFont::SetColor(HudColourNew.GetRGBA(HUD_COLOUR_CASH));
}

void CHudNew::DrawHealth() {
	CFont::SetColor(HudColourNew.GetRGBA(HUD_COLOUR_HEALTH));
}

void CHudNew::DrawArmour() {
	CFont::SetColor(HudColourNew.GetRGBA(HUD_COLOUR_ARMOUR));
}

void CHudNew::ReadSettingsFromFile() {
    std::ifstream file(PLUGIN_PATH((char*)"BBHud\\data\\hudcolor.dat"));

    if (file.is_open()) {
        int id = 0;
        for (std::string line; getline(file, line);) {
            char name[64];
            char link[64];
            float x, y, w, h;
            int a;

            if (!line[0] || line[0] == '\t' || line[0] == ' ' || line[0] == '#' || line[0] == '[')
                continue;

            m_HudList[id] = CHudSetting();

            if (line[0] == ';') {
                id++;
                continue;
            }

            sscanf(line.c_str(), "%s %f %f %f %f %s %d", &name, &x, &y, &w, &h, &link, &a);

            CRGBA col = HudColourNew.GetRGB(link, static_cast<unsigned char>(a));

            strcpy(m_HudList[id].name, name);
            m_HudList[id].x = x;
            m_HudList[id].y = y;
            m_HudList[id].w = w;
            m_HudList[id].h = h;
            m_HudList[id].col = col;
            printf("%s at id: %d \n", name, id);
            id++;
        }
        file.close();
    }
}

CHudSetting CHudNew::GetSetting(int setting) {
    return m_HudList[setting];
}

CHudSetting CHudNew::GetSetting(char* name) {
    CHudSetting result = CHudSetting();

    for (int i = 0; i < 256; i++) {
        if (name[4] == m_HudList[i].name[4] && faststrcmp(name, m_HudList[i].name, 5) == 0)
            result = GetSetting(i);
    }

    return result;
}