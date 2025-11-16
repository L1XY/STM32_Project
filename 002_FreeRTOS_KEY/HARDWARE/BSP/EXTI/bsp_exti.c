#include "bsp_exti.h"
#include "bsp_led.h"
#include "bsp_key.h"

typedef struct
{
    uint8_t exti_port_source;
    uint8_t exti_pin_source;
    EXTI_InitTypeDef exti_type;
} Bsp_Exti_Init_Type_t;

static const Bsp_Exti_Init_Type_t Bsp_Exti_Table[EXTIMAX_NUM] =
    {
        {
            .exti_port_source = GPIO_PortSourceGPIOE,
            .exti_pin_source = GPIO_PinSource4,
            .exti_type =
                {
                    .EXTI_Line = EXTI_Line4,
                    .EXTI_Mode = EXTI_Mode_Interrupt,
                    .EXTI_Trigger = EXTI_Trigger_Rising_Falling,
                    .EXTI_LineCmd = ENABLE,
                },
        },
        {
            .exti_port_source = GPIO_PortSourceGPIOE,
            .exti_pin_source = GPIO_PinSource3,
            .exti_type =
                {
                    .EXTI_Line = EXTI_Line3,
                    .EXTI_Mode = EXTI_Mode_Interrupt,
                    .EXTI_Trigger = EXTI_Trigger_Rising_Falling,
                    .EXTI_LineCmd = ENABLE,
                },
        },
        {
            .exti_port_source = GPIO_PortSourceGPIOE,
            .exti_pin_source = GPIO_PinSource2,
            .exti_type =
                {
                    .EXTI_Line = EXTI_Line2,
                    .EXTI_Mode = EXTI_Mode_Interrupt,
                    .EXTI_Trigger = EXTI_Trigger_Rising_Falling,
                    .EXTI_LineCmd = ENABLE,
                },
        },
        {
            .exti_port_source = GPIO_PortSourceGPIOA,
            .exti_pin_source = GPIO_PinSource0,
            .exti_type =
                {
                    .EXTI_Line = EXTI_Line0,
                    .EXTI_Mode = EXTI_Mode_Interrupt,
                    .EXTI_Trigger = EXTI_Trigger_Rising_Falling,
                    .EXTI_LineCmd = ENABLE,
                },
        },
};

void Bsp_Exti_Init(void)
{
    uint8_t i = 0;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    for (i = 0; i < (uint8_t)EXTIMAX_NUM; i++)
    {
        GPIO_EXTILineConfig(Bsp_Exti_Table[i].exti_port_source, Bsp_Exti_Table[i].exti_pin_source);
        EXTI_Init((EXTI_InitTypeDef *)&Bsp_Exti_Table[i].exti_type);
    }
}

void EXTI4_IRQHandler(void) // E4
{
    if (EXTI_GetITStatus(EXTI_Line4) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line4);
    }
}

void EXTI3_IRQHandler(void) // E3
{
    if (EXTI_GetITStatus(EXTI_Line3) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
}

void EXTI2_IRQHandler(void) // E2
{
    if (EXTI_GetITStatus(EXTI_Line2) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
}

void EXTI0_IRQHandler(void) // A0
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}
