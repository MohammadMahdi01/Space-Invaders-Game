#include <stdio.h>
#include <stdlib.h>
#include "requisite.h"
#include "game.h"
#include "characters.h"
#include "lcd.h"
#include "buzzer.h"
#include "uart.h"
#include "LiquidCrystal.h"
#include "timeManagement.h"
#include "menu.h"
#include "intro.h"
#include "about.h"
#include "settings.h"
#include "lose.h"

uint32_t score = 0;

uint32_t difficulty = 2;

programStateType programState;

int pBulletsNum = 0;
int eBulletsNum = 0;

time_t t;

void eBulletRemove(int index) {
	eBulletsNum--;
	for (int i = index; i < eBulletsNum; i++)
		eBullets[i] = eBullets[i + 1];
}

void pBulletRemove(int index) {
	pBulletsNum--;
	for (int i = index; i < pBulletsNum; i++)
		pBullets[i] = pBullets[i + 1];
}

void playerMoveUp() {
	playerPos.i--;

}

void playerMoveDown() {
	playerPos.i++;
}

void playerMoveLeft() {
	playerPos.j = playerPos.j == 0 ? 3 : (playerPos.j - 1) % 4;
}

void playerMoveRight() {
	playerPos.j = (playerPos.j + 1) % 4;
}

void enemyGunFire() {
	Pos bullet;
	bullet.i = shooterPos.i + 1;
	bullet.j = playerPos.j;
	if (eBulletsNum < BULLETS_BUFFER_SIZE)
		eBullets[eBulletsNum++] = bullet;
	if (sec[bullet.i][bullet.j] == -1)
		sec[bullet.i][bullet.j] = 6;

}

void playerGunFire() {
	Pos bullet;
	bullet.i = playerPos.i - 1;
	bullet.j = playerPos.j;
	if (pBulletsNum < BULLETS_BUFFER_SIZE)
		pBullets[pBulletsNum++] = bullet;
	sec[bullet.i][bullet.j] = 6;

}

void resetScore() {
	score = 0;
}

void addScore() {
	score += difficulty + 1;
}

bool firstTime = true;

void gameStart() {
	buzzerSetZero();
	playerPos.i = 19;
	playerPos.j = 0;
	osMutexAcquire(lcdMutexHandle, osWaitForever);
	lcdUpdate();
	osMutexRelease(lcdMutexHandle);
}

void bulletHandle() {

}

void playerMoveHandle() {

}

void gameStateKeypadHandle() {
	sec[playerPos.i][playerPos.j] = -1;
	switch (keypadNum) {
	case 10:
		playerMoveUp();
		break;
	case 7:
		playerMoveLeft();
		break;
	case 6:
		playerGunFire();
		break;
	case 5:
		playerMoveRight();
		break;
	case 2:
		playerMoveDown();
		break;
	default:
		break;
	}
	sec[playerPos.i][playerPos.j] = 0;
}
void bulletUpdate() {
	for (int i = 0; i < pBulletsNum; i++) {
		sec[pBullets[i].i][pBullets[i].j] = -1;
		if (pBullets[i].i == 0)
			pBulletRemove(i);

		else {
			pBullets[i].i--;
			if (sec[pBullets[i].i][pBullets[i].j] != -1) {
				pBulletRemove(i);
				sec[pBullets[i].i][pBullets[i].j] = -1;
			} else
				sec[pBullets[i].i][pBullets[i].j] = 6;
		}
	}

	for (int i = 0; i < eBulletsNum; i++) {
		if (sec[eBullets[i].i][eBullets[i].j] == 6)
			sec[eBullets[i].i][eBullets[i].j] = -1;
		if (eBullets[i].i == 19)
			eBulletRemove(i);

		else {
			eBullets[i].i++;
			if (sec[eBullets[i].i][eBullets[i].j] == -1)
				sec[eBullets[i].i][eBullets[i].j] = 6;
			else if (sec[eBullets[i].i][eBullets[i].j] == 0) {
				eBulletRemove(i);
				if (playerHP-- == 1) {
					sec[eBullets[i].i][eBullets[i].j] = -1;
					HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_7);
				}
			}
		}
	}

}

void enemiesMoveLeft(int index) {
//	int delay = enemyMoveTime / 8;
//	osDelay(delay);
	index = index * 2 + enemyMoveCount;
	int J;
	for (int i = index; 0 < index + 2; i++)
		for (int j = 0; j < 4; j++) {
			if ((1 <= sec[i][j]) & (sec[i][j] <= 5)) {
				if (sec[i][(j - 1) % 4] == -1) {
					J = j == 0 ? j = 3 : j - 1;
					sec[i][J] = sec[i][j];
					sec[i][J] = -1;

				}
			}

		}
}
void enemiesMoveRight(int index) {
//	int delay = enemyMoveTime / 8;
//	osDelay(delay);
	index = index * 2 + enemyMoveCount;
	for (int i = index; 0 < index + 2; i++)
		for (int j = 0; j < 4; j++) {
			if ((1 <= sec[i][j]) & (sec[i][j] <= 5)) {
				if (sec[i][(j + 1) % 4] == -1) {
					sec[i][(j + 1) % 4] = sec[i][j];
					sec[i][j] = -1;

				}
			}

		}
}
void allEnemiesMoveDown() {
	for (int i = 19; 0 <= i; i--)
		for (int j = 0; j < 4; j++) {
			if ((1 <= sec[i][j]) & (sec[i][j] <= 5)) {
				if (i == 19) {
					sec[i][j] = -1;
					HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_7);
				} else {
					sec[i + 1][j] = sec[i][j];
					sec[i][j] = -1;
				}

			}
		}
	enemyMoveCount++;
}

Pos randEnemyPos() {
	int pI;
	int pJ;
	do {
		pI = rand() % 20;
		pJ = rand() % 4;
	} while (!(1 <= sec[pI][pJ]) & (sec[pI][pJ] <= 5));

}

void enemiesShoot() {
	Pos shooterPos = randEnemyPos();
	enemyGunFire();
}

void gameSync() {
	if (programState == GameState) {

		osDelay(enemyMoveTime);
//		if (rand() % 2==0)
//			enemiesMoveLeft(0);
//		else
//			enemiesMoveRight(0);
//		enemiesMoveLeft(1);
//		enemiesMoveRight(2);
//		enemiesMoveLeft(3);
//		enemiesMoveRight(4);
//
//		if (rand() % 2==0)
//			enemiesMoveLeft(0);
//		else
//			enemiesMoveRight(0);
//		enemiesMoveLeft(1);
//		enemiesMoveRight(2);
		enemiesShoot();
		allEnemiesMoveDown();

	} else if (programState == GiantState) {

	}

	osDelay(200);
}

int gameHandle() {
	osMutexAcquire(lcdMutexHandle, osWaitForever);
	lcdUpdate();
	osMutexRelease(lcdMutexHandle);
}

int programRun() {
	switch (programState) {
//        case IntroState:
//            introHandle();
//            break;
	case MenuState:
		menuHandle();
		break;
	case GameState:
		gameHandle();
		break;
//        case LoseState:
//            // just wait for blue button interrupt
//            break;
	case AboutState:
		aboutHandle();
		break;
	case SettingsState:
		settingsHandle();
		break;
	default:
		break;
	}
	return 0;
}
