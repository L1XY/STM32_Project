#include "bsp_i2c.h"

#if (BSP_I2C1_MODE == BSP_I2C1_SOFTWARE_MODE)
static void Bsp_I2C1_Write_SCL(uint8_t value);
static void Bsp_I2C1_Write_SDA(uint8_t value);
static uint8_t Bsp_I2C1_Read_SDA(void);
static void Bsp_I2C1_Start(void);
static void Bsp_I2C1_Stop(void);
static void Bsp_I2C1_SendByte(uint8_t Byte);
static uint8_t Bsp_I2C1_ReceiveByte(void);
static void Bsp_I2C1_SendAck(uint8_t AckBit);
static Bsp_I2C_Status_t Bsp_I2C1_ReceiveAck(void);

void Bsp_I2C1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    Bsp_I2C1_Write_SCL(1);
    Bsp_I2C1_Write_SDA(1);
}

static void Bsp_I2C1_Write_SCL(uint8_t value)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_6, (BitAction)value);
}

static void Bsp_I2C1_Write_SDA(uint8_t value)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_7, (BitAction)value);
}

static uint8_t Bsp_I2C1_Read_SDA(void)
{
    uint8_t value = 0;
    value = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7);
    return value;
}

static void Bsp_I2C1_Start(void)
{
    Bsp_I2C1_Write_SDA(1);
    Bsp_I2C1_Write_SCL(1);
    Bsp_I2C1_Write_SDA(0);
    Bsp_I2C1_Write_SCL(0);
}

static void Bsp_I2C1_Stop(void)
{
    Bsp_I2C1_Write_SDA(0);
    Bsp_I2C1_Write_SCL(1);
    Bsp_I2C1_Write_SDA(1);
}

static void Bsp_I2C1_SendByte(uint8_t Byte)
{
    uint8_t i = 0;

    for (i = 0; i < 8; i++)
    {
        Bsp_I2C1_Write_SDA(!!(Byte & (0x80 >> i)));
        Bsp_I2C1_Write_SCL(1);
        Bsp_I2C1_Write_SCL(0);
    }
}

static uint8_t Bsp_I2C1_ReceiveByte(void)
{
    uint8_t i = 0;
    uint8_t Byte = 0;

    Bsp_I2C1_Write_SDA(1);

    for (i = 0; i < 8; i++)
    {
        Bsp_I2C1_Write_SCL(1);
        if (Bsp_I2C1_Read_SDA() == 1)
        {
            Byte |= (0x80 >> i);
        }
        Bsp_I2C1_Write_SCL(0);
    }

    return Byte;
}

static void Bsp_I2C1_SendAck(uint8_t AckBit)
{
    Bsp_I2C1_Write_SDA(AckBit);
    Bsp_I2C1_Write_SCL(1);
    Bsp_I2C1_Write_SCL(0);
}

static Bsp_I2C_Status_t Bsp_I2C1_ReceiveAck(void)
{
    uint8_t AckBit = 0;
    Bsp_I2C_Status_t ret = I2C_SUCCESS;

    Bsp_I2C1_Write_SDA(1);
    Bsp_I2C1_Write_SCL(1);
    AckBit = Bsp_I2C1_Read_SDA();
    Bsp_I2C1_Write_SCL(0);

    if (AckBit == 1)
    {
        ret = I2C_ERROR_NOT_RECV_ACK;
    }

    return ret;
}

Bsp_I2C_Status_t Bsp_I2C1_Write(uint8_t devAddr, uint32_t regAddr, uint8_t regByteSize, uint8_t *data, uint8_t len)
{
    uint8_t i = 0;
    Bsp_I2C_Status_t ret = I2C_SUCCESS;

    Bsp_I2C1_Start();
    Bsp_I2C1_SendByte(devAddr);
    ret = Bsp_I2C1_ReceiveAck();

    if (ret == I2C_SUCCESS)
    {
        for (i = 0; i < regByteSize; i++)
        {
            Bsp_I2C1_SendByte((uint8_t)(regAddr >> ((regByteSize - 1 - i) * 8)));
            ret = Bsp_I2C1_ReceiveAck();

            if (ret != I2C_SUCCESS)
            {
                break;
            }
        }
    }

    if (ret == I2C_SUCCESS)
    {
        for (i = 0; i < len; i++)
        {
            Bsp_I2C1_SendByte(data[i]);
            ret = Bsp_I2C1_ReceiveAck();

            if (ret != I2C_SUCCESS)
            {
                break;
            }
        }
    }

    Bsp_I2C1_Stop();

    return ret;
}

Bsp_I2C_Status_t Bsp_I2C1_Read(uint8_t devAddr, uint32_t regAddr, uint8_t regByteSize, uint8_t *data, uint8_t len)
{
    uint8_t i = 0;
    Bsp_I2C_Status_t ret = I2C_SUCCESS;

    Bsp_I2C1_Start();
    Bsp_I2C1_SendByte(devAddr);
    ret = Bsp_I2C1_ReceiveAck();

    if (ret == I2C_SUCCESS)
    {
        for (i = 0; i < regByteSize; i++)
        {
            Bsp_I2C1_SendByte((uint8_t)(regAddr >> ((regByteSize - 1 - i) * 8)));
            ret = Bsp_I2C1_ReceiveAck();

            if (ret != I2C_SUCCESS)
            {
                break;
            }
        }
    }

    if (ret == I2C_SUCCESS)
    {
        Bsp_I2C1_Start();
        Bsp_I2C1_SendByte(devAddr | 0x01);
        ret = Bsp_I2C1_ReceiveAck();

        if (ret == I2C_SUCCESS)
        {
            for (i = 0; i < len; i++)
            {
                data[i] = Bsp_I2C1_ReceiveByte();
                if (i < (len - 1))
                {
                    Bsp_I2C1_SendAck(0);
                }
                else
                {
                    Bsp_I2C1_SendAck(1);
                }
            }
        }
    }

    Bsp_I2C1_Stop();

    return ret;
}

#elif (BSP_I2C1_MODE == BSP_I2C1_HARDWARE_MODE)

static Bsp_I2C_Status_t Bsp_I2C1_WaitEventAndAck(uint32_t event, uint8_t ack);

void Bsp_I2C1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    I2C_InitTypeDef I2C_InitStruct;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // SCL
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6,
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz,
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD,
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    // SDA
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7,
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz,
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD,
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    I2C_InitStruct.I2C_ClockSpeed = 400000,
    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C,
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2,
    I2C_InitStruct.I2C_OwnAddress1 = 0x00,
    I2C_InitStruct.I2C_Ack = I2C_Ack_Enable,
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit,
    I2C_Init(I2C1, &I2C_InitStruct);

    I2C_Cmd(I2C1, ENABLE);
}

static Bsp_I2C_Status_t Bsp_I2C1_WaitEventAndAck(uint32_t event, uint8_t ack)
{
    Bsp_I2C_Status_t ret = I2C_SUCCESS;
    uint32_t timeout = 7200; // 72M, 72000000:1s,72000:1ms,72:1us

    while (I2C_CheckEvent(I2C1, event) != SUCCESS)
    {
        timeout--;
        if (timeout == 0)
        {
            ret = I2C_ERROR_HARDWARE_TIMEOUT;
            break;
        }
    }
    if (ack == 1)
    {
        if (I2C_GetFlagStatus(I2C1, I2C_FLAG_AF) == SET)
        {
            ret = I2C_ERROR_NOT_RECV_ACK;
        }
    }

    return ret;
}

Bsp_I2C_Status_t Bsp_I2C1_Write(uint8_t devAddr, uint32_t regAddr, uint8_t regByteSize, uint8_t *data, uint8_t len)
{
    uint16_t i = 0;
    Bsp_I2C_Status_t ret = I2C_SUCCESS;

    I2C_GenerateSTART(I2C1, ENABLE);
    ret = Bsp_I2C1_WaitEventAndAck(I2C_EVENT_MASTER_MODE_SELECT, 0);

    if (ret == I2C_SUCCESS)
    {
        I2C_Send7bitAddress(I2C1, devAddr, I2C_Direction_Transmitter);
        ret = Bsp_I2C1_WaitEventAndAck(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED, 1);

        if (ret == I2C_SUCCESS)
        {
            for (i = 0; i < regByteSize; i++)
            {
                I2C_SendData(I2C1, (uint8_t)(regAddr >> ((regByteSize - 1 - i) * 8)));
                ret = Bsp_I2C1_WaitEventAndAck(I2C_EVENT_MASTER_BYTE_TRANSMITTED, 1);

                if ((ret == I2C_SUCCESS) && (I2C_GetFlagStatus(I2C1, I2C_FLAG_AF) != SET))
                {
                    break;
                }
            }

            if (ret == I2C_SUCCESS)
            {
                for (i = 0; i < len; i++)
                {
                    I2C_SendData(I2C1, data[i]);
                    ret = Bsp_I2C1_WaitEventAndAck(I2C_EVENT_MASTER_BYTE_TRANSMITTED, 1);

                    if (ret != I2C_SUCCESS)
                    {
                        break;
                    }
                }
            }
        }
    }

    I2C_GenerateSTOP(I2C1, ENABLE);

    return ret;
}

Bsp_I2C_Status_t Bsp_I2C1_Read(uint8_t devAddr, uint32_t regAddr, uint8_t regByteSize, uint8_t *data, uint8_t len)
{
    uint16_t i = 0;
    Bsp_I2C_Status_t ret = I2C_SUCCESS;

    I2C_GenerateSTART(I2C1, ENABLE);
    ret = Bsp_I2C1_WaitEventAndAck(I2C_EVENT_MASTER_MODE_SELECT, 0);

    if (ret == I2C_SUCCESS)
    {
        I2C_Send7bitAddress(I2C1, devAddr, I2C_Direction_Transmitter);
        ret = Bsp_I2C1_WaitEventAndAck(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED, 1);

        if (ret == I2C_SUCCESS)
        {
            for (i = 0; i < regByteSize; i++)
            {
                I2C_SendData(I2C1, (uint8_t)(regAddr >> ((regByteSize - 1 - i) * 8)));
                ret = Bsp_I2C1_WaitEventAndAck(I2C_EVENT_MASTER_BYTE_TRANSMITTED, 1);

                if (ret != I2C_SUCCESS)
                {
                    break;
                }
            }

            if (ret == I2C_SUCCESS)
            {
                I2C_GenerateSTART(I2C1, ENABLE);
                ret = Bsp_I2C1_WaitEventAndAck(I2C_EVENT_MASTER_MODE_SELECT, 1);

                if (ret == I2C_SUCCESS)
                {
                    I2C_Send7bitAddress(I2C1, devAddr, I2C_Direction_Receiver);
                    ret = Bsp_I2C1_WaitEventAndAck(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED, 1);

                    if (ret == I2C_SUCCESS)
                    {
                        if (len == 1)
                        {
                            I2C_AcknowledgeConfig(I2C1, DISABLE);
                            I2C_GenerateSTOP(I2C1, ENABLE);
                            ret = Bsp_I2C1_WaitEventAndAck(I2C_EVENT_MASTER_BYTE_RECEIVED, 0);
                            if (ret == I2C_SUCCESS)
                            {
                                data[0] = I2C_ReceiveData(I2C1);
                            }
                        }
                        else
                        {
                            for (i = 0; i < len; i++)
                            {
                                ret = Bsp_I2C1_WaitEventAndAck(I2C_EVENT_MASTER_BYTE_RECEIVED, 0);

                                if (ret == I2C_SUCCESS)
                                {
                                    data[i] = I2C_ReceiveData(I2C1);

                                    if (i < len - 2)
                                    {
                                        I2C_AcknowledgeConfig(I2C1, ENABLE);
                                    }
                                    else if (i == len - 2)
                                    {
                                        I2C_AcknowledgeConfig(I2C1, DISABLE);
                                        I2C_GenerateSTOP(I2C1, ENABLE);
                                    }
                                    else
                                    {
                                        I2C_AcknowledgeConfig(I2C1, ENABLE);
                                    }
                                }
                                else
                                {
                                    I2C_AcknowledgeConfig(I2C1, DISABLE);
                                    I2C_GenerateSTOP(I2C1, ENABLE);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (ret != I2C_SUCCESS)
    {
        I2C_GenerateSTOP(I2C1, ENABLE);
    }

    return ret;
}
#endif
