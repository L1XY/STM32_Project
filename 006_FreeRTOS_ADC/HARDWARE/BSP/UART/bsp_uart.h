#ifndef __BSP_UART_H
#define __BSP_UART_H
#include "stdio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

#define UART0            0
#define UART1            1
#define UARTMAX_NUM      1

#define UART_DISABLE     0
#define UART_ENABLE      1

void Bsp_Uart_Init(void);
void Bsp_Uart1_Send(uint8_t *data, uint32_t len);

#endif
