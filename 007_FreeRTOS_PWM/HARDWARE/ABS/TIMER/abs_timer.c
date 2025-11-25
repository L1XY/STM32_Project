#include "abs_timer.h"

static Abs_Timer_t Abs_Timer_Set[ABS_TIMER_ID_NUM];

void Abs_Timer_Init(void)
{
    uint8_t i = 0u;
    for (i = 0u; i < (uint8_t)ABS_TIMER_ID_NUM; i++)
    {
        Abs_Timer_Set[i].state = ABS_TIMER_ST_OFF;
        Abs_Timer_Set[i].counter = 0;
        Abs_Timer_Set[i].value = 0;
        Abs_Timer_Set[i].type = ABS_TIMER_WK_ONCE;
        Abs_Timer_Set[i].timeout_cbk = NULL;
    }
}

void Abs_Timer_Start(Abs_Timer_ID_Type id, Abs_Timer_RunType type, uint32_t value, Abs_TimerCbkPtr callback)
{
    if (id < ABS_TIMER_ID_NUM)
    {
        Abs_Timer_Set[id].state = ABS_TIMER_ST_ON;
        Abs_Timer_Set[id].counter = 0;
        Abs_Timer_Set[id].value = value;
        Abs_Timer_Set[id].type = type;
        Abs_Timer_Set[id].timeout_cbk = callback;
    }
}

void Abs_Timer_Stop(Abs_Timer_ID_Type id)
{
    if (id < ABS_TIMER_ID_NUM)
    {
        Abs_Timer_Set[id].state = ABS_TIMER_ST_OFF;
    }
}

void Abs_Timer_MainFunction(void)
{
    uint8_t i = 0u;
    for (i = 0u; i < (uint8_t)ABS_TIMER_ID_NUM; i++)
    {
        if (Abs_Timer_Set[i].state == ABS_TIMER_ST_ON)
        {
            Abs_Timer_Set[i].counter += ABS_TIMER_CYCLE;
            if (Abs_Timer_Set[i].counter >= Abs_Timer_Set[i].value)
            {
                Abs_Timer_Set[i].counter = 0;

                if (Abs_Timer_Set[i].type == ABS_TIMER_WK_ONCE)
                {
                    Abs_Timer_Set[i].state = ABS_TIMER_ST_OFF;
                }

                if (Abs_Timer_Set[i].timeout_cbk != NULL)
                {
                    Abs_Timer_Set[i].timeout_cbk();
                }
            }
        }
    }
}
