#ifndef DOODLEJUMP_BUZZER_H
#define DOODLEJUMP_BUZZER_H

#include "requisite.h"

extern bool buzzerPlayingMelody;

typedef struct {
	uint16_t frequency;
	uint16_t duration;
} Tone;

extern const Tone super_mario_bros[];
extern int super_mario_bros_size;
extern int harrypotter_size;

void PWM_Start();

void buzzerHandle();

void buzzerSetZero();

void Update_Melody();

void buzzerChangeTone(uint16_t freq, uint16_t volume);

void buzzerInit();

void buzzerMelodyIntro();

void buzzerMelodyFireBall();

void buzzerMelody1Up();

void buzzerMelodyJumpLittle();

void buzzerMelodyJumpBig();

void buzzerMelodyLose();

void Change_Melody(const Tone *melody, uint16_t tone_count);

#endif
