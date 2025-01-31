#pragma once

#include "plugin.h"
#include "LateStaticInit.h"

#ifdef GTASA
#define PLAYER_ID 0
#else
#define PLAYER_ID
#endif

class BBHud {
public:
	static bool bInitialized;
	static HANDLE pThread;
	static bool bRwInitialized;
	static bool bRwQuit;

public:
	static bool Init();
	static void Shutdown();
	static void Run();
};

extern int& gGameState;