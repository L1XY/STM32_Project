#ifndef __BSP_KEY_H
#define __BSP_KEY_H
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define KEY_DISABLE     0
#define KEY_ENABLE      1

#define KEY0            0
#define KEY1            1
#define KEY2            2
#define KEY3            3
#define KEYMAX_NUM      4

void Bsp_Key_Init(void);
uint8_t Bsp_Key_GetState(uint8_t buttonx);

#endif
