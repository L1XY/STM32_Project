#include "drv_W25QXX.h"

Drv_W25QXX_Status_t Drv_W25QXX_Init(void)
{
    Drv_W25QXX_Status_t ret = DRV_W25QXX_SUCCESS;

    return ret;
}

Drv_W25QXX_Status_t Drv_W25QXX_ReadID(uint8_t *MID, uint16_t *DID)
{
    uint16_t i = 0;
    uint8_t temp[4] = {0x9F};
    Drv_W25QXX_Status_t ret_w25qxx = DRV_W25QXX_SUCCESS;
    Bsp_SPI_Status_t ret_spi = SPI_SUCCESS;

    Bsp_SPI2_Start();

    for (i = 0; i < 4; i++)
    {
        ret_spi = Bsp_SPI2_SwapByte(&temp[i], &temp[i]);
        if (ret_spi != SPI_SUCCESS)
        {
            ret_w25qxx = DRV_W25QXX_ERROR;
            break;
        }
    }

    if (ret_spi == SPI_SUCCESS)
    {
        *MID = temp[1];
        *DID = (((uint16_t)temp[2] << 8) & 0xFF00) | ((uint16_t)temp[3] & 0x00FF);
    }

    Bsp_SPI2_Stop();

    return ret_w25qxx;
}

Drv_W25QXX_Status_t Drv_W25QXX_Write(uint32_t addr, uint8_t *data, uint8_t len)
{
    Drv_W25QXX_Status_t ret_w25qxx = DRV_W25QXX_SUCCESS;

    return ret_w25qxx;
}

Drv_W25QXX_Status_t Drv_W25QXX_Read(uint32_t addr, uint8_t *data, uint8_t len)
{
    Drv_W25QXX_Status_t ret_w25qxx = DRV_W25QXX_SUCCESS;

    return ret_w25qxx;
}
