#ifndef __DRV_AT24CXX_H
#define __DRV_AT24CXX_H

#include "stdio.h"
#include "bsp_i2c.h"

#define EEPROM_ADDR 0xA0 // 硬件地址引脚接GND
#define EEPROM_REG_LEN 1

typedef enum
{
    DRV_AT24CXX_SUCCESS,
    DRV_AT24CXX_ERROR,
} Drv_AT24CXX_Status_t;

Drv_AT24CXX_Status_t Drv_AT24CXX_Init(void);
Drv_AT24CXX_Status_t Drv_AT24CXX_Write(uint8_t addr, uint8_t *data, uint8_t len);
Drv_AT24CXX_Status_t Drv_AT24CXX_Read(uint8_t addr, uint8_t *data, uint8_t len);

#endif
