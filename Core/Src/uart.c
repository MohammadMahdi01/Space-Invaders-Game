#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "cmsis_os.h"

#include "requisite.h"
#include "globals.h"
#include "game.h"
#include "lcd.h"
#include "characters.h"
#include "acceleroGyro.h"
#include "timeManagement.h"


#define GAME_SYNC_SIGNAL_NUMBER '0'
#define GAME_SAVE_SIGNAL_NUMBER '1'

#define GAME_SYNC_MESSAGE_LENGTH 166
#define GAME_SAVE_MESSAGE_LENGTH 1000

typedef enum {
    ControlLeft, ControlRight, ControlFire, ClockSync, LoadApprove, Loading
} uartSignalType;


char uartTmpStr[100];
char uartRxTmpStr[450];


void uartFormatTransmit(const char *format, ...) {
    int len;
    va_list arguments;

    va_start(arguments, format);
    len = vsnprintf(uartTmpStr, strlen(format) + 1, format, arguments);
    va_end(arguments);

    osSemaphoreAcquire(uartITSemHandle, osWaitForever);

    HAL_UART_Transmit_IT(&huart1, (uint8_t *) uartTmpStr, len);
}

void uartStringTransmit(const char *string) {

    osSemaphoreAcquire(uartITSemHandle, osWaitForever);

//    HAL_UART_Transmit_DMA(&huart1, (uint8_t *) string, strlen(string));
    HAL_UART_Transmit_IT(&huart1, (uint8_t *) string, strlen(string));
}

void uartReceive(uint16_t size) {
    HAL_UART_Receive_IT(&huart1, (uint8_t *) uartRxTmpStr, size);
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        osSemaphoreRelease(uartITSemHandle);
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        osSemaphoreRelease(uartDmaRxSemHandle);
    }
}
