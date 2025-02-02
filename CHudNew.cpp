#include "plugin.h"
#include "BBHud.h"
#include "CHudColoursNew.h"
#include "CHudNew.h"
#include "CProgressBar.h"
#include "ScreenAddons.h"
#include "Settings.h"

#include "CHudColours.h"
#include "CCamera.h"
#include "CClock.h"
#include "CHud.h"
#include "CFont.h"
#include "CMenuManager.h"
#include "CTheScripts.h"
#include "CSprite.h"
#include "CTimer.h"
#include "CCutsceneMgr.h"
#include "CModelInfo.h"
#include "CStats.h"
#include "CMessages.h"
#include "CGarages.h"
#include "CReplay.h"
#include "eModelID.h"
#include "CDarkel.h"
#include "CEntryExitManager.h"
#include "CAERadioTrackManager.h"
#include "CText.h"
#include "CRadar.h"
#include "CMenuSystem.h"
#include "CTxdStore.h"
#include "CWorld.h"

using namespace plugin;

CHudNew chudnew;
CSprite2d CHudNew::SpritesNew[HUD_TOTALSPRITES];
CSprite2d CHudNew::SharedSprites[SHARED_TOTALSPRITES];
CSprite2d CHudNew::CrosshairSprites[CROSSHAIRS_TOTALSPRITES];
bool CHudNew::ms_bSpritesLoaded;

CHudNew::CHudNew() {
	if (!s.m_bEnable)
		return;

	patch::PutRetn(0x58FAE0); // CHud::Draw
	patch::PutRetn(0x58D490); // CHud::DrawAfterFade
	patch::Set(0x53E4FA, 5); // CAudioEngine::DisplayRadioStationName
}

void CHudNew::Initialise() {
    ;;
}

void CHudNew::Shutdown() {
	;;
}

void CHudNew::Draw() {
	if (CReplay::Mode != 1
		&& !CWeapon::ms_bTakePhoto
		&& !FrontEndMenuManager.m_bMenuActive) {
		RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)FALSE);
		RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
		RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
		RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
		RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, (void*)rwTEXTUREADDRESSMIRROR);
		RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void*)FALSE);
		RwRenderStateSet(rwRENDERSTATESHADEMODE, (void*)rwSHADEMODEFLAT);
		RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)rwFILTERLINEAR);

		if (!TheCamera.m_bWideScreenOn) {

			if (FrontEndMenuManager.m_bPrefsShowHud && CTheScripts::bDisplayHud) {
				/*
					DrawPlayerInfo
				*/
				// 1st
                if (CWorld::Players[0].m_pPed) {
                    if (CHud::bDrawClock)
                        DrawClock(s.m_fClock.left, s.m_fClock.top, s.m_fClock.right, s.m_fClock.bottom);

                    DrawMoneyCounter(s.m_fMoney.left, s.m_fMoney.top, s.m_fMoney.right, s.m_fMoney.bottom);
                    DrawHealth(0, s.m_fHealth.left, s.m_fHealth.top, s.m_fHealth.right, s.m_fHealth.bottom);
                    DrawArmour(0, s.m_fArmour.left, s.m_fArmour.top, s.m_fArmour.right, s.m_fArmour.bottom);
                    if (CWorld::Players[0].m_pPed->m_fArmour > 1.0)
                        DrawBreath(0, s.m_fBreath.left, s.m_fBreath.top, s.m_fBreath.right, s.m_fBreath.bottom);
                    else
                        DrawBreath(0, s.m_fArmour.left, s.m_fArmour.top, s.m_fArmour.right, s.m_fArmour.bottom);
                }
			}

			CHud::DrawMissionTimers();

			DrawWanted(s.m_fWanted.left, s.m_fWanted.top, s.m_fWanted.right, s.m_fWanted.bottom);
			DrawRadioStation(s.m_fRadioName.left, s.m_fRadioName.top, s.m_fRadioName.right, s.m_fRadioName.bottom);
		}
		if (!CHud::bScriptDontDisplayRadar && !TheCamera.m_bWideScreenOn) {
			//CRadarNew::DrawRadarAfterHud();

			if (!CPad::GetPad(0)->GetDisplayVitalStats(FindPlayerPed()) || FindPlayerVehicle(-1, 0)) {
				CHud::bDrawingVitalStats = 0;
			}
			else {
				CHud::bDrawingVitalStats = 1;
				CHud::DrawVitalStats();
			}
			if (1 || /*!CGameLogic::SkipCanBeActivated() || */ CHud::bDrawingVitalStats) {
				// HelpTripSkipShown = 0
			}
			else {
				CHud::DrawTripSkip();
				if (0 /*!HelpTripSkipShown*/) {
					//CHud::SetHelpMessage(TheText.Get("SKIP_1"), 1, 0, 0);
					// HelpTripSkipShown = 1;
				}
			}
		}

		if (CHud::m_bDraw3dMarkers && !TheCamera.m_bWideScreenOn)
			CRadar::Draw3dMarkers();

		if (!CTimer::m_UserPause) {
			if (!CHud::m_BigMessage[0][0]) {
				if (CMenuSystem::num_menus_in_use)
					CMenuSystem::Process(-99);
				CHud::DrawScriptText(1);
			}

			if (CTheScripts::bDrawSubtitlesBeforeFade)
				CHudNew::DrawSubtitles(s.m_fSubtitles.left, s.m_fSubtitles.top, s.m_fSubtitles.right, s.m_fSubtitles.bottom);

			CHud::DrawOddJobMessage(1);//s.m_fTextBox.left, s.m_fTextBox.top, s.m_fTextBox.right, s.m_fTextBox.bottom);;
		}

		BBHud::ms_bReload = false;
	}
}

void CHudNew::DrawAfterFade() {
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)rwFILTERLINEAR);
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, (void*)rwTEXTUREADDRESSMIRROR);
    RwD3D9SetRenderState(rwRENDERSTATEVERTEXALPHAENABLE, TRUE);
	if (!CTimer::m_UserPause && CReplay::Mode != 1 && !CWeapon::ms_bTakePhoto) {
		if ((!FindPlayerVehicle(-1, 0)
			|| FindPlayerVehicle(-1, 0)->m_nVehicleSubClass != 4
			&& FindPlayerVehicle(-1, 0)->m_nVehicleSubClass != 3)
			&& !CCutsceneMgr::ms_cutsceneProcessing
			&& !FrontEndMenuManager.m_bMenuActive
			&& !TheCamera.m_bWideScreenOn
			&& !CHud::bScriptDontDisplayAreaName) {
		}

		if (!CHud::m_BigMessage[0][0])
			CHud::DrawScriptText(0);

		if (!CTheScripts::bDrawSubtitlesBeforeFade)
			DrawSubtitles(s.m_fSubtitles.left, s.m_fSubtitles.top, s.m_fSubtitles.right, s.m_fSubtitles.bottom);

		//DrawMissionTitle(s.m_fMissionTitle.left, s.m_fMissionTitle.top, s.m_fMissionTitle.right, s.m_fMissionTitle.bottom);
	}
}

void CHudNew::DrawClock(float x, float y, float w, float h) {
    char text[16];
    sprintf_s(text, "%02d:%02d", CClock::ms_nGameClockHours, CClock::ms_nGameClockMinutes);

    // Always use SA settings:
    CFont::SetProportional(false);
    CFont::SetBackground(false, false);
    CFont::SetOrientation(ALIGN_RIGHT);
    CFont::SetRightJustifyWrap(0.0f);
    CFont::SetDropShadowPosition(0);
    CFont::SetEdge(EDGE_SIZE);
    CFont::SetDropColor(CRGBA(0, 0, 0, 255));
    CFont::SetColor(CRGBA(HudColourNew.HUD_COLOUR_CLOCK));
    CFont::SetScale(SCREEN_LEFT(w), SCREEN_TOP(h));
    CFont::PrintString(SCREEN_RIGHT(x), SCREEN_TOP(y), text);
}

void CHudNew::DrawMoneyCounter(float x, float y, float w, float h) {
    char text[16];
    sprintf_s(text, "$%08d", CWorld::Players[CWorld::PlayerInFocus].m_nDisplayMoney);

    CFont::SetProportional(false);
    CFont::SetBackground(false, false);
    CFont::SetOrientation(ALIGN_RIGHT);
    CFont::SetRightJustifyWrap(0.0f);
    CFont::SetDropShadowPosition(0);
    CFont::SetEdge(EDGE_SIZE);
    CFont::SetDropColor(CRGBA(0, 0, 0, HudColourNew.HUD_COLOUR_CASH.a));
    CFont::SetColor(CRGBA(HudColourNew.HUD_COLOUR_CASH));
    CFont::SetScale(SCREEN_LEFT(w), SCREEN_TOP(h));
    CFont::PrintString(SCREEN_RIGHT(x), SCREEN_TOP(y), text);
}

void CHudNew::DrawHealth(int PlayerID, float x, float y, float w, float h) {
    float fProgress = CWorld::Players[PlayerID].m_pPed->m_fHealth /
        (float)CWorld::Players[PlayerID].m_nMaxHealth;
    float fBarSize = (float)CWorld::Players[PlayerID].m_nMaxHealth /
        CStats::GetFatAndMuscleModifier(STAT_MOD_10);
    if (fBarSize > 1.0f)
        fBarSize = 1.0f;

    CProgressBar::DrawProgressBar(
        SCREEN_RIGHT(x + (w * fBarSize)),
        SCREEN_TOP(y),
        SCREEN_LEFT(w * fBarSize),
        SCREEN_TOP(h),
        fProgress,
        SCREEN_TOP(2.5f),
        0,
        CRGBA(HudColourNew.HUD_COLOUR_HEALTH),
        CRGBA(HudColourNew.HUD_COLOUR_HEALTH.r,
            HudColourNew.HUD_COLOUR_HEALTH.g,
            HudColourNew.HUD_COLOUR_HEALTH.b, 150)
    );
}

void CHudNew::DrawArmour(int PlayerID, float x, float y, float w, float h) {
    float fProgress = CWorld::Players[PlayerID].m_pPed->m_fArmour /
        (float)CWorld::Players[PlayerID].m_nMaxArmour;
    CProgressBar::DrawProgressBar(
        SCREEN_RIGHT(x + w),
        SCREEN_TOP(y),
        SCREEN_LEFT(w),
        SCREEN_TOP(h),
        fProgress,
        SCREEN_TOP(2.5f),
        0,
        CRGBA(HudColourNew.HUD_COLOUR_ARMOUR),
        CRGBA(HudColourNew.HUD_COLOUR_ARMOUR.r,
            HudColourNew.HUD_COLOUR_ARMOUR.g,
            HudColourNew.HUD_COLOUR_ARMOUR.b, 150)
    );
}

void CHudNew::DrawBreath(int PlayerID, float x, float y, float w, float h) {
    float fProgress = CWorld::Players[PlayerID].m_pPed->m_pPlayerData->m_fBreath /
        CStats::GetFatAndMuscleModifier(STAT_MOD_AIR_IN_LUNG);
    CProgressBar::DrawProgressBar(
        SCREEN_RIGHT(x + w),
        SCREEN_TOP(y),
        SCREEN_LEFT(w),
        SCREEN_TOP(h),
        fProgress,
        SCREEN_TOP(2.5f),
        0,
        CRGBA(HudColourNew.HUD_COLOUR_BREATH),
        CRGBA(HudColourNew.HUD_COLOUR_BREATH.r,
            HudColourNew.HUD_COLOUR_BREATH.g,
            HudColourNew.HUD_COLOUR_BREATH.b, 150)
    );
}

void CHudNew::DrawRadioStation(float x, float y, float w, float h) {
    CFont::SetProportional(false);
    CFont::SetBackground(false, false);
    CFont::SetOrientation(ALIGN_CENTER);
    CFont::SetCentreSize(SCREEN_LEFT(640.0f));
    CFont::SetDropShadowPosition(0);
    CFont::SetEdge(EDGE_SIZE);
    CFont::SetDropColor(CRGBA(0, 0, 0, 255));
    CFont::SetColor(CRGBA(HudColourNew.HUD_COLOUR_RADIO_NAME_A));
    CFont::SetScale(SCREEN_LEFT(w), SCREEN_TOP(h));
}

void CHudNew::DrawSubtitles(float x, float y, float w, float h) {
    CFont::SetProportional(true);
    CFont::SetOrientation(ALIGN_CENTER);
    CFont::SetBackground(false, false);
    CFont::SetScale(SCREEN_LEFT(w), SCREEN_TOP(h));
    CFont::SetCentreSize(SCREEN_RIGHT(280.0f));
    CFont::SetDropShadowPosition(SUBS_SHADOW_SIZE);
    CFont::SetDropColor(CRGBA(0, 0, 0, HudColourNew.HUD_COLOUR_SUBTITLES.a));
    CFont::SetColor(CRGBA(HudColourNew.HUD_COLOUR_SUBTITLES));
    CFont::PrintString(SCREEN_MIDDLE_X(x), SCREEN_BOTTOM(y), CHud::m_Message);
}

void CHudNew::DrawWanted(float x, float y, float w, float h) {
    char icon[16];
    strcpy_s(icon, "]");
    CFont::SetProportional(false);
    CFont::SetBackground(false, false);
    CFont::SetOrientation(ALIGN_RIGHT);
    CFont::SetRightJustifyWrap(0.0f);
    CFont::SetEdge(0);
    CFont::SetDropShadowPosition(0);
    CFont::SetDropColor(CRGBA(0, 0, 0, HudColourNew.HUD_COLOUR_WANTED_N.a));
    CFont::SetColor(CRGBA(HudColourNew.HUD_COLOUR_WANTED_N));
    CFont::SetScale(SCREEN_LEFT(w), SCREEN_TOP(h));
    for (unsigned int i = 0; i < 6; i++) {
        CFont::PrintString(SCREEN_RIGHT(x + 23.0f * i), SCREEN_TOP(y), icon);
    }
}