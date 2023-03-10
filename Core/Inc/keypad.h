#ifndef DOODLEJUMP_KEYPAD_H
#define DOODLEJUMP_KEYPAD_H

#include "requisite.h"

extern GPIO_TypeDef *const Row_ports[];
extern const uint16_t Row_pins[];
extern GPIO_TypeDef *const Column_ports[];
extern const uint16_t Column_pins[];
extern uint32_t lastGpioExti;

void keypadAssign(uint16_t gpioPin);
void keypadHandle();

#endif
