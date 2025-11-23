#ifndef __BSP_EXTI_H
#define __BSP_EXTI_H
#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#define EXTIMAX_NUM 4

void Bsp_Exti_Init(void);

#endif
