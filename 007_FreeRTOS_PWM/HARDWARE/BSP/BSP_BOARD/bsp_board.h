#ifndef __BSP_BOARD_H
#define __BSP_BOARD_H

#include "stdio.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_nvic.h"
#include "bsp_uart.h"
#include "bsp_exti.h"
#include "bsp_i2c.h"
#include "bsp_spi.h"
#include "bsp_adc.h"
#include "bsp_tim.h"

void Bsp_Init(void);

#endif
