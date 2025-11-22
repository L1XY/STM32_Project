#ifndef __BSP_I2C_H
#define __BSP_I2C_H
#include "stdio.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_i2c.h"
#include "bsp_config.h"

// I2C状态枚举
typedef enum
{
    I2C_SUCCESS,
    I2C_ERROR_NOT_RECV_ACK,
    I2C_ERROR_HARDWARE_TIMEOUT,
} Bsp_I2C_Status_t;

void Bsp_I2C1_Init(void);
Bsp_I2C_Status_t Bsp_I2C1_Write(uint8_t devAddr, uint32_t regAddr, uint8_t regByteSize, uint8_t *data, uint8_t len);
Bsp_I2C_Status_t Bsp_I2C1_Read(uint8_t devAddr, uint32_t regAddr, uint8_t regByteSize, uint8_t *data, uint8_t len);
Bsp_I2C_Status_t Bsp_I2C1_Get_I2C_Status(void);

#endif
