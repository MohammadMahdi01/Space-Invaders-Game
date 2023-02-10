#include <stdio.h>
#include <stdlib.h>
#include "requisite.h"
#include "globals.h"
#include "game.h"
#include "lcd.h"
#include "menu.h"
#include "intro.h"
#include "settings.h"
#include "about.h"
#include "lose.h"
#include "uart.h"

extern UART_HandleTypeDef huart1;
// Input pull down rising edge trigger interrupt pins:
// Row1 PD3, Row2 PD5, Row3 PD7, Row4 PB4
GPIO_TypeDef *const Row_ports[] = { GPIOA, GPIOA, GPIOA, GPIOA }; // iterrupt
const uint16_t Row_pins[] = { GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3 };
// Output pins: Column1 PD4, Column2 PD6, Column3 PB3, Column4 PB5
GPIO_TypeDef *const Column_ports[] = { GPIOC, GPIOC, GPIOC, GPIOC };
const uint16_t Column_pins[] =
		{ GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3 };
volatile uint32_t last_gpio_exti;
uint8_t keypadNum;

int count = 0;
int flag = 0;

void keypadHandle() {
	switch (programState) {
	case IntroState:
		introKeypadHandle();
		break;
	case MenuState:
		menuKeypadHandle();
		break;
	case GameState:
		gameStateKeypadHandle();
		break;
//        case LoseState:
//            loseKeypadHandle();
//            break;
	case AboutState:
		aboutKeypadHandle();
		break;
	case SettingsState:
		settingsKeypadHandle();
		break;
	}

}

//void keypadAssign(uint16_t gpioPin) {
//
//    if (gpioPin == 0) {
//        keypadNum = 0;
//        return;
//    }
//    int rowNumber = -1;
//    int columnNumber = -1;
//
//#pragma unroll
//    for (int row = 0; row < 4; row++) // Loop through Rows
//        if (gpioPin == Row_pins[row]) {
//            rowNumber = row;
//            break;
//        }
//
//#pragma unroll
//    for (int i = 0; i < 4; i++)
//        HAL_GPIO_WritePin(Column_ports[i], Column_pins[i], GPIO_PIN_RESET);
//
//#pragma unroll
//    for (int col = 0; col < 4; col++) {     // Loop through Columns
//        HAL_GPIO_WritePin(Column_ports[col], Column_pins[col], GPIO_PIN_SET);
//        if (HAL_GPIO_ReadPin(Row_ports[rowNumber], Row_pins[rowNumber])) {
//            columnNumber = col;
//            break;
//        }
//        //HAL_GPIO_WritePin(columnPorts[col], columnPins[col], GPIO_PIN_RESET); //  not sure if commenting this is ok
//    }
//
//#pragma unroll
//    for (int i = 0; i < 4; i++)
//        HAL_GPIO_WritePin(Column_ports[i], Column_pins[i], GPIO_PIN_SET);
//
//    if (rowNumber == -1 || columnNumber == -1)
//        return; // Reject invalid scan
//
//    const uint8_t buttonNumber = rowNumber * 4 + columnNumber + 1;
//
//    keypadNum = buttonNumber;
//}

//   C0   C1   C2   C3
// +----+----+----+----+
// | 1  | 2  | 3  | 4  |  R0
// +----+----+----+----+
// | 5  | 6  | 7  | 8  |  R1
// +----+----+----+----+
// | 9  | 10 | 11 | 12 |  R2
// +----+----+----+----+
// | 13 | 14 | 15 | 16 |  R3
// +----+----+----+----+

void keypadAssign(uint16_t GPIO_Pin) {

	int8_t row_number = -1;
	int8_t column_number = -1;

	if (GPIO_Pin == GPIO_PIN_0) {
		// blue_button_pressed = 1;
		// return;
	}

	for (uint8_t row = 0; row < 4; row++) // Loop through Rows
			{
		if (GPIO_Pin == Row_pins[row]) {
			row_number = row;
//			len = sprintf(op, "%d\n", row_number);
//			HAL_UART_Transmit(&huart1, op, len, 100);
		}
	}

	HAL_GPIO_WritePin(Column_ports[0], Column_pins[0], 0);
	HAL_GPIO_WritePin(Column_ports[1], Column_pins[1], 0);
	HAL_GPIO_WritePin(Column_ports[2], Column_pins[2], 0);
	HAL_GPIO_WritePin(Column_ports[3], Column_pins[3], 0);

	for (uint8_t col = 0; col < 4; col++) // Loop through Columns
			{
		HAL_GPIO_WritePin(Column_ports[col], Column_pins[col], 1);
		if (HAL_GPIO_ReadPin(Row_ports[row_number], Row_pins[row_number])) {
			column_number = col;
		}
		HAL_GPIO_WritePin(Column_ports[col], Column_pins[col], 0);
	}

	HAL_GPIO_WritePin(Column_ports[0], Column_pins[0], 1);
	HAL_GPIO_WritePin(Column_ports[1], Column_pins[1], 1);
	HAL_GPIO_WritePin(Column_ports[2], Column_pins[2], 1);
	HAL_GPIO_WritePin(Column_ports[3], Column_pins[3], 1);

	if (row_number == -1 || column_number == -1) {
		return; // Reject invalid scan
	}
	keypadNum = row_number * 4 + column_number + 1;
}

uint32_t lastGpioExti = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (lastGpioExti + 300 > osKernelGetTickCount())
		return;

	keypadAssign(GPIO_Pin);
	osSemaphoreRelease(keypadSemHandle);
	lastGpioExti = osKernelGetTickCount();
}
