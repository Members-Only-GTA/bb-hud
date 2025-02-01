#include "plugin.h"
#include "BBHud.h"
#include "CHudColoursNew.h"
#include "CHudNew.h"
#include "CProgressBar.h"
#include "Settings.h"

using namespace plugin;

BBHud bbhud;
bool BBHud::ms_bReload;
bool UpAndRunning;

BBHud::BBHud() {
    if (!UpAndRunning)
    {
        BBHud::ms_bReload = true;
        
		Events::initRwEvent += []() {
            HudColourNew.Initialise();
			CHudNew::Initialise();
		};

        Events::gameProcessEvent += [] {
            ;;
            };

		Events::drawHudEvent += [] {
            CHudNew::Draw();
		};

        Events::drawAfterFadeEvent += [] {
            //CHudNew::DrawAfterFade();
        };

        Events::shutdownRwEvent += [] {
            HudColourNew.Shutdown();
            CHudNew::Shutdown();
            };

        UpAndRunning = true;
    }
}

void BBHud::InitGameMode(std::string gameMode, bool reInit) {
    if (reInit) {
		ReInitialise();
    }
}

void BBHud::ReInitialise() {
	if (!BBHud::ms_bReload) {

		HudColourNew.Shutdown();
		HudColourNew.Initialise();

		CHudNew::Shutdown();
		CHudNew::Initialise();

		BBHud::ms_bReload = true;
	}
}