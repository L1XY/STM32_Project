#ifndef __ABS_KEY_H
#define __ABS_KEY_H
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "bsp_key.h"
#include "abs_timer.h"

#define ABS_KEY_QUEUE_SIZE 20
#define ABS_KEY_QUEUE_OK 0
#define ABS_KEY_QUEUE_NOK 1
#define ABS_KEY_TIMER_NUM 4

#define ABS_KEY_DEBOUNCE_TIME 20
#define ABS_KEY_MULTI_CLICK_TIME 300
#define ABS_KEY_LONG_PRESS_TIME 1000
#define ABS_KEY_LONG_PRESS_REPEA_TIME 100

typedef void (*Abs_Key_EventCallBack)(void);
typedef void (*Abs_Key_DebounceTimerCallBack)(void);

typedef enum
{
    ABS_KEY_EVENT_SINGLE_CLICK = 0,       // 单击事件
    ABS_KEY_EVENT_DOUBLE_CLICK = 1,       // 双击事件
    ABS_KEY_EVENT_TRIPLE_CLICK = 2,       // 三击事件
    ABS_KEY_EVENT_LONG_PRESS = 3,         // 长按事件
    ABS_KEY_EVENT_LONG_REPEAT = 4,        // 长按重复执行事件
    ABS_KEY_EVENT_LONG_PRESS_RELEASE = 5, // 长按释放事件
    ABS_KEY_EVENT_NUM = 6,
} Abs_Key_Event_t;

typedef struct
{
    uint8_t key_index;
    Abs_Key_Event_t event;
} Abs_Key_QueueItem_t;

typedef struct
{
    Abs_Key_QueueItem_t item_data[ABS_KEY_QUEUE_SIZE];
    uint8_t front;
    uint8_t rear;
} Abs_Key_Queue_t;

typedef enum
{
    ABS_KEY_STATE_RELEASED,         // 释放状态
    ABS_KEY_STATE_PRESS_DETECTED,   // 按下检测(消抖中)
    ABS_KEY_STATE_PRESSED,          // 按下状态
    ABS_KEY_STATE_RELEASE_DETECTED, // 释放检测(消抖中)
    ABS_KEY_STATE_WAIT_DOUBLE,      // 等待双击
    ABS_KEY_STATE_WAIT_TRIPLE,      // 等待三击
    ABS_KEY_STATE_LONG_PRESS,       // 长按状态
} Abs_Key_State_t;

typedef struct
{
    Abs_Key_State_t state; // 按键状态
    uint8_t pin_state;     // 引脚状态
    uint8_t click_count;   // 多击次数检测
    Abs_Timer_ID_Type debounce_id;
    Abs_Timer_ID_Type multi_click_id;
    Abs_Timer_ID_Type long_press_id;
    Abs_Timer_ID_Type long_press_repeat_id;
    Abs_Key_QueueItem_t queue_item; // 按键事件
} Abs_Key_Data_t;

typedef struct
{
    Abs_Key_Event_t event;
    const Abs_Key_EventCallBack callback; // 事件回调函数
} Abs_Key_CallBack_t;

typedef struct
{
    uint8_t key_index;
    const Abs_Key_CallBack_t *key_event_table;
} Abs_Key_CallBackCfg_t;

typedef struct
{
    uint8_t key_index;
    Abs_Key_DebounceTimerCallBack callback;
} Abs_Key_DebounceTimer_t;

void Abs_Key_Init(void);
uint8_t Abs_Key_Event_Enqueue(Abs_Key_QueueItem_t *item);
uint8_t Abs_Key_Event_Dequeue(Abs_Key_QueueItem_t *item);
uint8_t Abs_Key_Event_Peek(Abs_Key_QueueItem_t *item);
void Abs_Key_MainFunction(void);
void Abs_Key_ProcessState(uint8_t keyx, uint8_t new_state);
void Abs_Key_Key0_Debounce_Callback(void);
void Abs_Key_Key1_Debounce_Callback(void);
void Abs_Key_Key2_Debounce_Callback(void);
void Abs_Key_Key3_Debounce_Callback(void);

#endif
