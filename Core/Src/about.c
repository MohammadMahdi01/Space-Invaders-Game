#include <stdio.h>
#include <stdlib.h>
#include "requisite.h"
#include "LiquidCrystal.h"
#include "timeManagement.h"
#include "game.h"
#include "menu.h"

char groupName[25] = " ";
char name1[25] = "Salmani";
char name2[25] = "kishbafan";
static char timeStr[20];
static char scoreStr[10];
static char difficultyStr[2];

void aboutStart() {

    updateDateTime();
    sprintf(timeStr, "%d/%d/%d - %d:%d:%d",
            getDateTime().dateVar.Year, getDateTime().dateVar.Month, getDateTime().dateVar.Date,
            getDateTime().timeVar.Hours, getDateTime().timeVar.Minutes, getDateTime().timeVar.Seconds);

//    itoa((int) score, scoreStr, 10);
//    itoa((int) difficulty, difficultyStr, 10);

    osMutexAcquire(lcdMutexHandle, 100);

    clear();

    setCursor(0, 0);
    print("Name: ");
    print(groupName);

    setCursor(0, 1);
    print(": ");
    print(name1);

    setCursor(0, 2);
    print(": ");
    print(name2);

    setCursor(0, 3);
    print(timeStr);
    osMutexRelease(lcdMutexHandle);
}

void aboutHandle() {
    updateDateTime();
    sprintf(timeStr, "%d/%d/%d - %d:%d:%d",
            getDateTime().dateVar.Year, getDateTime().dateVar.Month, getDateTime().dateVar.Date,
            getDateTime().timeVar.Hours, getDateTime().timeVar.Minutes, getDateTime().timeVar.Seconds);

    osMutexAcquire(lcdMutexHandle, osWaitForever);
    setCursor(0, 3);
    print(timeStr);
    osMutexRelease(lcdMutexHandle);
}

void aboutKeypadHandle() {
    switch (keypadNum) {
        case 1:
            programState = MenuState;
            menuStart();
            break;
        default:
            break;
    }
}
