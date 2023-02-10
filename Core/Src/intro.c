#include <stdio.h>
#include <stdlib.h>
#include "requisite.h"
#include "game.h"
#include "lcd.h"
#include "buzzer.h"
#include "LiquidCrystal.h"
#include "menu.h"
#include "uart.h"

int started = 0;
void introKeypadHandle() {
	if (keypadNum == 1) {
//            if (programState == LoseState)
//                return;
		programState = MenuState;

		// if (osThreadGetState(updateLcdTskHandle) == osThreadBlocked) {
		menuStart();
		//   osThreadResume(updateLcdTskHandle);
		//}
	}
}

void introAnimation(){
	setCursor(0, 3);
	for (int j = 14; 0 <= j; j--) {

			write(j/3+1);
		}
	setCursor(19, 3);
	write(0);
	for (int j = 14; 0 <= j; j--) {
		setCursor(j, 3);
		print(" ");
		osDelay(300);
	}
}

void introStart() {
	//    if (!buzzerPlayingMelody)
	//        melodyQueueSend(MelodyIntro);

	osMutexAcquire(lcdMutexHandle, osWaitForever);

	//    clear();
//	lcdUpdate();
	setCursor(0, 0);
	print("Welcome to");
	setCursor(0, 1);
	print("Space Invaders");
	setCursor(0, 2);
	print("Press 1 to go menu");

	introAnimation();

	osMutexRelease(lcdMutexHandle);
}

void introHandle() {

}
