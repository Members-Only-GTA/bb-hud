#include "BBHud.h"
#include "HudColoursNew.h"
#include "HudNew.h"


using namespace plugin;

int& gGameState = *(int*)0xC8D4C0;

bool BBHud::bInitialized = false;
HANDLE BBHud::pThread = NULL;
bool BBHud::bRwInitialized = false;
bool BBHud::bRwQuit = false;

bool BBHud::Init() {
	if (bInitialized)
		return false;

    auto init = []() {
        HudColourNew.ReadColorsFromFile();

        bRwInitialized = true;
    };

    Events::initRwEvent += init;

	auto initAfterRw = []() {
		CHudNew::Init();
	};

    auto reInitForRestart = []() {
        CHudNew::ReInit();
     };

    Events::reInitGameEvent += reInitForRestart;

	auto shutdown = []() {
        CHudNew::Shutdown();

        bRwQuit = true;
	};

	Events::shutdownRwEvent += shutdown;
	bInitialized = true;
	return true;
}

void BBHud::Shutdown() {
    if (bInitialized)
        return;

	bInitialized = false;
}

void BBHud::Run() {
	while (!bRwQuit) {
		if (bRwInitialized) {
			//HudColor.Process();
		}
		Sleep(100);
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        if (BBHud::Init())
            BBHud::pThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(void(__cdecl*)())BBHud::Run, 0, 0, 0);
    }
    return TRUE;
}