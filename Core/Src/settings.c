#include "requisite.h"
#include "LiquidCrystal.h"
#include "about.h"
#include "game.h"
#include "menu.h"
#include "acceleroGyro.h"
#include "uart.h"

#define maxUNSize  10



int target;
int playerHP;
int enemyMoveTime;
int enemyMoveCount=0;

char username[maxUNSize];

void settingsStart() {

	HAL_UART_Transmit(&huart1, "Pleas Enter Your Name:\n", 23, 100);
	HAL_UART_Receive(&huart1, username, maxUNSize, 20000);

	osMutexAcquire(lcdMutexHandle, osWaitForever);
	clear();
	setCursor(0, 0);
	print("Choose Difficulty:");
	setCursor(0, 1);
	print("Easy");
	setCursor(0, 2);
	print("Normal");
	setCursor(0, 3);
	print("Hard");
	osMutexRelease(lcdMutexHandle);
}

void keyboardHandle() {

}

void chooseDifficulty(int keypadNum) {
	switch (keypadNum) {
	case 1:
		difficulty = 1;
		target = 15;
		playerHP = 7;
		enemyMoveTime = 5000;
		break;
	case 2:
		difficulty = 2;
		target = 25;
		playerHP = 5;
		enemyMoveTime = 3000;
		break;
	case 3:
		difficulty = 3;
		target = 35;
		playerHP = 3;
		enemyMoveTime = 1000;
		break;
	default:
		break;
	}
}

void settingsKeypadHandle() {
	if(1<=keypadNum&keypadNum<=3){
	chooseDifficulty(keypadNum);
	programState = GameState;
	gameStart();
	}
}

void settingsHandle() {

}
