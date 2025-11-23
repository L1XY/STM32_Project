#include "bsp_spi.h"

#if (BSP_SPI2_MODE == BSP_SPI2_SOFTWARE_MODE)

static void Bsp_SPI2_W_SCK(uint8_t value);
static void Bsp_SPI2_W_MOSI(uint8_t value);
static uint8_t Bsp_SPI2_R_MISO(void);

void Bsp_SPI2_W_SS(uint8_t value)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, (BitAction)value);
}

static void Bsp_SPI2_W_SCK(uint8_t value)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_13, (BitAction)value);
}

static void Bsp_SPI2_W_MOSI(uint8_t value)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_15, (BitAction)value);
}

static uint8_t Bsp_SPI2_R_MISO(void)
{
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14);
}

void Bsp_SPI2_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    /* SS:      PB12
     * CLK:     PB13
     * MOSI:    PB15
     * MISO:    PB14 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    Bsp_SPI2_W_SS(1);
    Bsp_SPI2_W_SCK(0);
    Bsp_SPI2_W_MOSI(0);
}

void Bsp_SPI2_Start(void)
{
    Bsp_SPI2_W_SS(0);
}

void Bsp_SPI2_Stop(void)
{
    Bsp_SPI2_W_SS(1);
    Bsp_SPI2_W_MOSI(0);
}

Bsp_SPI_Status_t Bsp_SPI2_SwapByte(uint8_t *send_byte, uint8_t *recv_byte)
{
    uint8_t i = 0;
    uint8_t temp_byte;
    Bsp_SPI_Status_t ret = SPI_SUCCESS;

    if (send_byte == NULL)
    {
        ret = SPI_ERROR_PARAM_ERROR;
    }
    else
    {
        temp_byte = *send_byte;

        for (i = 0; i < 8; i++)
        {
            Bsp_SPI2_W_MOSI(temp_byte & 0x80);
            temp_byte <<= 1;
            Bsp_SPI2_W_SCK(1);
            if (Bsp_SPI2_R_MISO() == 1)
            {
                temp_byte |= 0x01;
            }
            Bsp_SPI2_W_SCK(0);
        }

        if (recv_byte != NULL)
        {
            *recv_byte = temp_byte;
        }
    }

    return ret;
}

#elif (BSP_SPI2_MODE == BSP_SPI2_HARDWARE_MODE)

static Bsp_SPI_Status_t Bsp_SPI2_WaitEvent(uint32_t event);
static void Bsp_SPI2_W_SS(uint8_t value);

static void Bsp_SPI2_W_SS(uint8_t value)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, (BitAction)value);
}

void Bsp_SPI2_Start(void)
{
    Bsp_SPI2_W_SS(0);
}

void Bsp_SPI2_Stop(void)
{
    Bsp_SPI2_W_SS(1);
}

void Bsp_SPI2_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef SPI_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    /* SS:      PB12
     * CLK:     PB13
     * MOSI:    PB15
     * MISO:    PB14 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_Init(SPI2, &SPI_InitStructure);

    SPI_Cmd(SPI2, ENABLE);

    Bsp_SPI2_Stop();
}

static Bsp_SPI_Status_t Bsp_SPI2_WaitEvent(uint32_t event)
{
    Bsp_SPI_Status_t ret = SPI_SUCCESS;
    uint32_t timeout = 7200; // 72M, 72000000:1s,72000:1ms,72:1us

    while (SPI_I2S_GetFlagStatus(SPI2, event) != SET)
    {
        timeout--;
        if (timeout == 0)
        {
            ret = SPI_ERROR_HARDWARE_TIMEOUT;
            break;
        }
    }

    return ret;
}

Bsp_SPI_Status_t Bsp_SPI2_SwapByte(uint8_t *send_byte, uint8_t *recv_byte)
{
    Bsp_SPI_Status_t ret = SPI_SUCCESS;
    uint8_t temp_byte;

    if (send_byte == NULL)
    {
        ret = SPI_ERROR_PARAM_ERROR;
    }
    else
    {
        ret = Bsp_SPI2_WaitEvent(SPI_I2S_FLAG_TXE);

        if (ret == SPI_SUCCESS)
        {
            SPI_I2S_SendData(SPI2, *send_byte);
            ret = Bsp_SPI2_WaitEvent(SPI_I2S_FLAG_RXNE);

            if (ret == SPI_SUCCESS)
            {
                if (recv_byte != NULL)
                {
                    *recv_byte = SPI_I2S_ReceiveData(SPI2);
                }
                else
                {
                    temp_byte = SPI_I2S_ReceiveData(SPI2);
                    (void)temp_byte;
                }
            }
        }
    }

    return ret;
}

#endif
