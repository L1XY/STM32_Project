#ifndef __BSP_ADC_H
#define __BSP_ADC_H
#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_dma.h"

#define ADC_00 0
#define ADC_01 1
#define ADC_02 2
#define ADCMAX_NUM 3

extern uint16_t Bsp_Adc_Value[ADCMAX_NUM];
void Bsp_Adc_Init(void);

#endif
