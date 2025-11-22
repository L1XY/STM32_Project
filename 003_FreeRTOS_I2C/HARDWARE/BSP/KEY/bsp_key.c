#include "bsp_key.h"

typedef struct
{
    uint8_t key_num;
    uint32_t key_clock;
    GPIO_TypeDef *key_port;
    GPIO_InitTypeDef gpio_type;
    uint8_t key_enable;
} Bsp_Key_Init_Type_t;

static const Bsp_Key_Init_Type_t Bsp_Key_Table[KEYMAX_NUM] =
    {
        {
            .key_num = KEY0,
            .key_clock = RCC_APB2Periph_GPIOE,
            .key_port = GPIOE,
            .gpio_type =
                {
                    .GPIO_Pin = GPIO_Pin_4,
                    .GPIO_Speed = GPIO_Speed_50MHz,
                    .GPIO_Mode = GPIO_Mode_IPU,
                },
            .key_enable = KEY_ENABLE,
        },
        {
            .key_num = KEY1,
            .key_clock = RCC_APB2Periph_GPIOE,
            .key_port = GPIOE,
            .gpio_type =
                {
                    .GPIO_Pin = GPIO_Pin_3,
                    .GPIO_Speed = GPIO_Speed_50MHz,
                    .GPIO_Mode = GPIO_Mode_IPU,
                },
            .key_enable = KEY_ENABLE,
        },
        {
            .key_num = KEY2,
            .key_clock = RCC_APB2Periph_GPIOE,
            .key_port = GPIOE,
            .gpio_type =
                {
                    .GPIO_Pin = GPIO_Pin_2,
                    .GPIO_Speed = GPIO_Speed_50MHz,
                    .GPIO_Mode = GPIO_Mode_IPU,
                },
            .key_enable = KEY_ENABLE,
        },
        {
            .key_num = KEY3,
            .key_clock = RCC_APB2Periph_GPIOA,
            .key_port = GPIOA,
            .gpio_type =
                {
                    .GPIO_Pin = GPIO_Pin_0,
                    .GPIO_Speed = GPIO_Speed_50MHz,
                    .GPIO_Mode = GPIO_Mode_IPD,
                },
            .key_enable = KEY_ENABLE,
        },
};

void Bsp_Key_Init(void)
{
    uint8_t i = 0;
    for (i = 0; i < (uint8_t)KEYMAX_NUM; i++)
    {
        if (Bsp_Key_Table[i].key_enable == KEY_ENABLE)
        {
            RCC_APB2PeriphClockCmd(Bsp_Key_Table[i].key_clock, ENABLE);
            GPIO_Init(Bsp_Key_Table[i].key_port, (GPIO_InitTypeDef *)&Bsp_Key_Table[i].gpio_type);
        }
    }
}

uint8_t Bsp_Key_GetState(uint8_t keyx)
{
    /* 按下为1，抬起为0 */
    /* KEY_RELEASE 0 */
    /* KEY_PRESS   1 */
    uint8_t ret;
    if (Bsp_Key_Table[keyx].gpio_type.GPIO_Mode == GPIO_Mode_IPU)
    {
        /* 上拉，按下为低电平，读取为0，取反表示按下为1 */
        ret = !GPIO_ReadInputDataBit(Bsp_Key_Table[keyx].key_port, Bsp_Key_Table[keyx].gpio_type.GPIO_Pin);
    }
    else
    {
        /* 下拉，按下为高电平，读取为1，表示按下为1 */
        ret = GPIO_ReadInputDataBit(Bsp_Key_Table[keyx].key_port, Bsp_Key_Table[keyx].gpio_type.GPIO_Pin);
    }
    return ret;
}
