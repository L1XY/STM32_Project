#include "drv_AT24CXX.h"

Drv_AT24CXX_Status_t Drv_AT24CXX_Write(uint8_t addr, uint8_t *data, uint8_t len)
{
    Drv_AT24CXX_Status_t ret_at24cxx = DRV_AT24CXX_SUCCESS;
    Bsp_I2C_Status_t ret_i2c = I2C_SUCCESS;

    ret_i2c = Bsp_I2C1_Write(EEPROM_ADDR, addr, EEPROM_REG_LEN, data, len);

    if (ret_i2c != I2C_SUCCESS)
    {
        ret_at24cxx = DRV_AT24CXX_ERROR;
    }

    return ret_at24cxx;
}

Drv_AT24CXX_Status_t Drv_AT24CXX_Read(uint8_t addr, uint8_t *data, uint8_t len)
{
    Drv_AT24CXX_Status_t ret_at24cxx = DRV_AT24CXX_SUCCESS;
    Bsp_I2C_Status_t ret_i2c = I2C_SUCCESS;

    ret_i2c = Bsp_I2C1_Read(EEPROM_ADDR, addr, EEPROM_REG_LEN, data, len);

    if (ret_i2c != I2C_SUCCESS)
    {
        ret_at24cxx = DRV_AT24CXX_ERROR;
    }

    return ret_at24cxx;
}
