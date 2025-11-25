#include "bsp_tim.h"

void Bsp_Tim_Pwm_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_7; // PA8: TIM1_CH1; PA7: TIM1_CH1N
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* 时基单元 */
    TIM_InternalClockConfig(TIM1);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0; // PSC
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 2000 - 1; // ARR
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

    /* 定时器比较输出PWM */
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1000; // CCR
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);

    /* 定时器死区控制 */
    TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
    TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
    TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
    TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
    TIM_BDTRInitStructure.TIM_DeadTime = 50; // DT
    TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
    TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
    TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
    TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);

    /* 使能TIM1主输出，高级定时器必须调用 */
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    /* 开启TIM1 */
    TIM_Cmd(TIM1, ENABLE);
    /* 频率：
     * Freq = CK_PSC / (PSC + 1) / (ARR + 1)
     * 其中，CK_PSC = 72M
     */
    /* 占空比：
     * Duty = CCR / (ARR + 1)
     */
    /* 分辨率：
     * Reso = 1 / (ARR + 1)
     */
    /* 死区时间：
     * DT7为0：DT_Time = DT * (1 / CK_PSC)
     * DT7为1：DT_Time = (DT - 128) * (1 / CK_PSC)
     * 其中，CK_PSC = 72M
     */
}
