#include "bsp_uart.h"

#pragma import(__use_no_semihosting)
struct __FILE
{
    int handle;
};

FILE __stdout;

void _sys_exit(int x)
{
    x = x;
}

int fputc(int ch, FILE *f)
{
    while ((USART1->SR & USART_SR_TC) == 0)
        ;
    USART1->DR = (u8)ch;
    return ch;
}

typedef struct
{
    uint8_t uart_num;
    uint32_t uart_clock;
    uint32_t uart_gpio_clock;
    GPIO_TypeDef *uart_tx_port;
    GPIO_InitTypeDef uart_tx_gpio_type;
    GPIO_TypeDef *uart_rx_port;
    GPIO_InitTypeDef uart_rx_gpio_type;
    USART_TypeDef *uartx;
    USART_InitTypeDef uart_init_type;
    uint8_t uart_enable;
} Bsp_Uart_Init_Type_t;

static const Bsp_Uart_Init_Type_t Bsp_Uart_Table[UARTMAX_NUM] =
{
    {
        .uart_num = UART1,
        .uart_clock = RCC_APB2Periph_USART1,
        .uart_gpio_clock = RCC_APB2Periph_GPIOA,
        .uart_tx_port = GPIOA,
        .uart_tx_gpio_type = 
        {
            .GPIO_Pin = GPIO_Pin_9,
            .GPIO_Speed = GPIO_Speed_50MHz,
            .GPIO_Mode = GPIO_Mode_AF_PP,
        },
        .uart_rx_port = GPIOA,
        .uart_rx_gpio_type = 
        {
            .GPIO_Pin = GPIO_Pin_10,
            .GPIO_Speed = GPIO_Speed_50MHz,
            .GPIO_Mode = GPIO_Mode_IN_FLOATING,
        },
        .uartx = USART1,
        .uart_init_type = 
        {
            .USART_BaudRate = 115200,
            .USART_WordLength = USART_WordLength_8b,
            .USART_StopBits = USART_StopBits_1,
            .USART_Parity = USART_Parity_No,
            .USART_Mode = USART_Mode_Rx | USART_Mode_Tx,
            .USART_HardwareFlowControl = USART_HardwareFlowControl_None,
        },
        UART_ENABLE,
    },
};

void Bsp_Uart_Init(void)
{
    uint8_t i = 0;
    for (i = 0; i < UARTMAX_NUM; i++)
    {
        if (Bsp_Uart_Table[i].uart_enable == UART_ENABLE)
        {
            RCC_APB2PeriphClockCmd(Bsp_Uart_Table[i].uart_clock, ENABLE);
            RCC_APB2PeriphClockCmd(Bsp_Uart_Table[i].uart_gpio_clock, ENABLE);
            GPIO_Init((GPIO_TypeDef*)Bsp_Uart_Table[i].uart_tx_port, (GPIO_InitTypeDef*)&Bsp_Uart_Table[i].uart_tx_gpio_type);
            GPIO_Init((GPIO_TypeDef*)Bsp_Uart_Table[i].uart_rx_port, (GPIO_InitTypeDef*)&Bsp_Uart_Table[i].uart_rx_gpio_type);
            USART_Init((USART_TypeDef*)Bsp_Uart_Table[i].uartx, (USART_InitTypeDef*)&Bsp_Uart_Table[i].uart_init_type);
            USART_ITConfig((USART_TypeDef*)Bsp_Uart_Table[i].uartx, USART_IT_RXNE, ENABLE);
            USART_Cmd((USART_TypeDef*)Bsp_Uart_Table[i].uartx, ENABLE);
        }
    }
}

void Bsp_Uart1_Send(uint8_t *data, uint32_t len)
{
    uint32_t i = 0;
    for (i = 0; i < len; i++)
    {
        while ((USART1->SR & USART_SR_TC) == 0)
            ;
        USART1->DR = data[i];
    }
}

void USART1_IRQHandler(void)
{
    uint8_t res = USART_ReceiveData(USART1);
    printf("%c", res);
}
