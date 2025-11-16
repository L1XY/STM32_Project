#include "bsp_nvic.h"

static const NVIC_InitTypeDef Bsp_Nvic_Table[NVICNAX_NUM] = 
{
    {
        .NVIC_IRQChannel = USART1_IRQn,
        .NVIC_IRQChannelPreemptionPriority = 3,
        .NVIC_IRQChannelSubPriority = 3,
        .NVIC_IRQChannelCmd = ENABLE,
    },
};

void Bsp_Nvic_Init(void)
{
    uint8_t i = 0;
    for (i = 0; i < NVICNAX_NUM; i++)
    {
        NVIC_Init((NVIC_InitTypeDef*)&Bsp_Nvic_Table[i]);
    }
}
