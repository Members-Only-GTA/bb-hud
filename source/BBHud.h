#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

class BBHud {
public:
	static char* ms_nGamePrefix;
	static bool ms_bReload;

public:
	BBHud();

	static void InitGameMode(std::string gameMode, bool reInit = false);
	static void ReInitialise();
};