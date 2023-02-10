#include <stdio.h>
#include <stdlib.h>
#include "requisite.h"
#include "LiquidCrystal.h"
#include "lcd.h"
#include "characters.h"
#include "game.h"

void lcdInit() {
	osMutexAcquire(lcdMutexHandle, osWaitForever);

	LiquidCrystal(GPIOD, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11,
	GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14);
	begin(20, 4);
	createChar(0, player);
	createChar(1, one);
	createChar(2, tow);
	createChar(3, three);
	createChar(4, four);
	createChar(5, five);
	createChar(6, pBullet);
	osMutexRelease(lcdMutexHandle);
}

int lcdWriteCount = 0;

int lcdUpdate(void) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 4; j++) {
			if (cur[i][j] != sec[i][j]) {
				setCursor(i, 3 - j);
				if (sec[i][j] < 0) {
					print(" ");
				} else
					write(sec[i][j]);
			}
			cur[i][j] = sec[i][j];
		}
	}
	return 0;
}

