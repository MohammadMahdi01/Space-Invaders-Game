#include "requisite.h"
#include "keypad.h"
#include "LiquidCrystal.h"
#include "game.h"
#include "about.h"
#include "settings.h"

typedef enum {
	GameOption, GiantOption, AboutOption
} menuOptionType;

static menuOptionType optionsArr[3] = { GameOption, GiantOption, AboutOption };
static int currentOptionIdx = 0;
static int newOptionIdx = 0;
static bool selectKeyPressed = false;

void menuStart() {
	osMutexAcquire(lcdMutexHandle, osWaitForever);
	clear();
//    uartStringTransmit("menu:");
	setCursor(0, 0);
	print("Normal Game");
	setCursor(0, 1);
	print("Giant Game");
	setCursor(0, 2);
	print("About");

//    setCursor(0, currentOptionIdx);
//    print("*");
	osMutexRelease(lcdMutexHandle);
}

void menuKeypadHandle() {
	switch (keypadNum) {
	case 1:
		settingsStart();
		programState = SettingsState;
		break;
//    case 2:
//    	giantStart();
	case 3:
		aboutStart();
		programState = AboutState;
		break;
	}
}

void menuHandle() {
}
