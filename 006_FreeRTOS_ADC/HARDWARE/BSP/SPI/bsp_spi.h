#ifndef __BSP_SPI_H
#define __BSP_SPI_H
#include "stdio.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "bsp_config.h"

// SPI状态枚举
typedef enum
{
    SPI_SUCCESS,
    SPI_ERROR_PARAM_ERROR,
    SPI_ERROR_HARDWARE_TIMEOUT,
} Bsp_SPI_Status_t;

void Bsp_SPI2_Init(void);
void Bsp_SPI2_Start(void);
void Bsp_SPI2_Stop(void);
Bsp_SPI_Status_t Bsp_SPI2_SwapByte(uint8_t *send_byte, uint8_t *recv_byte);

#endif
