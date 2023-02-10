#ifndef DOODLEJUMP_GLOBALS_H
#define DOODLEJUMP_GLOBALS_H

#include "cmsis_os.h"
#include "requisite.h"

extern RTC_HandleTypeDef hrtc;

extern ADC_HandleTypeDef hadc1;

extern UART_HandleTypeDef huart1;

extern TIM_HandleTypeDef htim8;

extern PCD_HandleTypeDef hpcd_USB_FS;

extern osThreadId_t playMelodyTskHandle;
extern osMessageQueueId_t melodyNameQuHandle;
extern osThreadId_t updateLcdTskHandle;

extern osMutexId_t lcdMutexHandle;
extern osMutexId_t gameLoadMutexHandle;

extern osSemaphoreId_t uartITSemHandle;
extern osSemaphoreId_t keypadSemHandle;
extern osSemaphoreId_t volumeSemHandle;
extern osSemaphoreId_t uartDmaRxSemHandle;

extern uint8_t keypadNum;//32 biid

extern uint32_t generateProbability;
extern uint32_t twoStepProbability;
extern uint32_t springStepProbability;
extern uint32_t brokenStepProbability;
extern uint32_t monsterProbability;
extern uint32_t blackHoleProbability;


//extern enum ProgramState programState;


#endif
