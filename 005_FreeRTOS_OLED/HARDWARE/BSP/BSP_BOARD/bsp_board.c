#include "bsp_board.h"

void Bsp_Init(void)
{
    Bsp_Led_Init();
    Bsp_Key_Init();
    Bsp_Uart_Init();
    Bsp_I2C1_Init();
    Bsp_SPI2_Init();
    Bsp_Exti_Init();
    Bsp_Nvic_Init();
}
