#ifndef __DRV_W25QXX_H
#define __DRV_W25QXX_H

#include "stdio.h"
#include "bsp_spi.h"

typedef enum
{
    DRV_W25QXX_SUCCESS,
    DRV_W25QXX_ERROR,
} Drv_W25QXX_Status_t;

Drv_W25QXX_Status_t Drv_W25QXX_Init(void);
Drv_W25QXX_Status_t Drv_W25QXX_ReadID(uint8_t *MID, uint16_t *DID);
Drv_W25QXX_Status_t Drv_W25QXX_Write(uint32_t addr, uint8_t *data, uint8_t len);
Drv_W25QXX_Status_t Drv_W25QXX_Read(uint32_t addr, uint8_t *data, uint8_t len);

#endif
