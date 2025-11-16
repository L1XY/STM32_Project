#ifndef __ABS_TIMER_H
#define __ABS_TIMER_H
#include "stdint.h"
#include "stddef.h"

#define ABS_TIMER_CYCLE (10u) /* ms */

typedef enum
{
    ABS_TIMER_ID_TEST = 0,
    ABS_TIMER_ID_NUM,
} Abs_Timer_ID_Type;

typedef enum
{
    ABS_TIMER_WK_ONCE = 0,
    ABS_TIMER_WK_CYCLE,
} Abs_Timer_RunType;

typedef enum
{
    ABS_TIMER_ST_OFF = 0,
    ABS_TIMER_ST_ON,
} Abs_Timer_State_t;

typedef void (*Abs_TimerCbkPtr)(void);

typedef struct
{
    uint32_t value;
    uint32_t counter;
    Abs_Timer_RunType type;
    Abs_Timer_State_t state;
    Abs_TimerCbkPtr timeout_cbk;
} Abs_Timer_t;

void Abs_Timer_Init(void);
void Abs_Timer_Start(Abs_Timer_ID_Type id, Abs_Timer_RunType type, uint32_t value, Abs_TimerCbkPtr callback);
void Abs_Timer_Stop(Abs_Timer_ID_Type id);
void Abs_Timer_MainFunction(void);

#endif
