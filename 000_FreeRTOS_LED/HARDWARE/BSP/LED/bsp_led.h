#ifndef __BSP_LED_H
#define __BSP_LED_H
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define LED_OFF         0
#define LED_ON          1

#define LED_DISABLE     0
#define LED_ENABLE      1

#define LED0            0
#define LED1            1
#define LEDMAX_NUM      2

void Bsp_Led_Init(void);
void Bsp_Led_On(uint8_t ledx);
void Bsp_Led_Off(uint8_t ledx);
void Bsp_Led_Flip(uint8_t ledx);
void Bsp_Led_task(void *pvParameters);

#endif
