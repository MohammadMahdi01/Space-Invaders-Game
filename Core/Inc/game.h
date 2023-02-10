#ifndef DOODLEJUMP_GAME_H
#define DOODLEJUMP_GAME_H

#include <stdio.h>
#include <stdlib.h>

#include "requisite.h"

#define HIGH_JUMP_HEIGHT 20
#define NORMAL_JUMP_HEIGHT 7


typedef enum {
    IntroState,
    MenuState,
    GameState,
    LoseState,
    AboutState,
	SettingsState,
    GiantState
} programStateType;


typedef enum {
    Up, Down, Left, Right
} moveDirectionType;

extern programStateType programState;

extern uint32_t score;

extern uint32_t difficulty;

extern int bulletsNum;

extern uint32_t shiftUpCount;

extern time_t t;

int programRun();

void gameStart();

void playerMove(moveDirectionType direction);

void addScore();

void resetScore();

void playerGunFire();

void gameStateKeypadHandle();

void bulletUpdate();

void gameSync();

#endif
