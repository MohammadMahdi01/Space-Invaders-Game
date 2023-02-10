#ifndef DOODLEJUMP_SETTINGS_H
#define DOODLEJUMP_SETTINGS_H

extern bool gameLoaded;
extern int target;
extern int playerHP;
extern int enemyMoveTime;
extern int enemyMoveCount;

void settingsStart();

void settingsHandle();

void settingsKeypadHandle();

#endif
