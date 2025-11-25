#include "bsp_led.h"

typedef struct
{
    uint8_t led_num;
    uint32_t led_clock;
    GPIO_TypeDef *led_port;
    GPIO_InitTypeDef gpio_type;
    uint8_t led_enable;
} Bsp_Led_Init_t;

static uint8_t Bsp_Led_State[LEDMAX_NUM] = {0};
static const Bsp_Led_Init_t Bsp_Led_Table[LEDMAX_NUM] =
    {
        {
            .led_num = LED0,
            .led_clock = RCC_APB2Periph_GPIOB,
            .led_port = GPIOB,
            .gpio_type =
                {
                    .GPIO_Pin = GPIO_Pin_5,
                    .GPIO_Speed = GPIO_Speed_50MHz,
                    .GPIO_Mode = GPIO_Mode_Out_PP,
                },
            .led_enable = LED_ENABLE,
        },
        {
            .led_num = LED1,
            .led_clock = RCC_APB2Periph_GPIOE,
            .led_port = GPIOE,
            .gpio_type =
                {
                    .GPIO_Pin = GPIO_Pin_5,
                    .GPIO_Speed = GPIO_Speed_50MHz,
                    .GPIO_Mode = GPIO_Mode_Out_PP,
                },
            .led_enable = LED_ENABLE,
        },
};

void Bsp_Led_Init(void)
{
    uint8_t i = 0;
    for (i = 0; i < (uint8_t)LEDMAX_NUM; i++)
    {
        if (Bsp_Led_Table[i].led_enable == LED_ENABLE)
        {
            RCC_APB2PeriphClockCmd(Bsp_Led_Table[i].led_clock, ENABLE);
            GPIO_Init((GPIO_TypeDef *)Bsp_Led_Table[i].led_port, (GPIO_InitTypeDef *)&Bsp_Led_Table[i].gpio_type);
            Bsp_Led_Off(i);
        }
    }
}

void Bsp_Led_On(uint8_t ledx)
{
    Bsp_Led_State[ledx] = 1;
    GPIO_ResetBits(Bsp_Led_Table[ledx].led_port, Bsp_Led_Table[ledx].gpio_type.GPIO_Pin);
}

void Bsp_Led_Off(uint8_t ledx)
{
    Bsp_Led_State[ledx] = 0;
    GPIO_SetBits(Bsp_Led_Table[ledx].led_port, Bsp_Led_Table[ledx].gpio_type.GPIO_Pin);
}

void Bsp_Led_Flip(uint8_t ledx)
{
    if (Bsp_Led_State[ledx] == 0)
    {
        Bsp_Led_On(ledx);
    }
    else
    {
        Bsp_Led_Off(ledx);
    }
}
