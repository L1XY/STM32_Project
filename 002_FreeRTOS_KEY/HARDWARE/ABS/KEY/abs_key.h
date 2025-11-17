#ifndef __ABS_KEY_H
#define __ABS_KEY_H
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "bsp_key.h"

#define ABS_KEY_QUEUE_SIZE 20
#define ABS_KEY_QUEUE_OK 0
#define ABS_KEY_QUEUE_NOK 1

typedef enum
{
    ABS_KEY_EVENT_SINGLE_CLICK,       // 单击事件
    ABS_KEY_EVENT_DOUBLE_CLICK,       // 双击事件
    ABS_KEY_EVENT_TRIPLE_CLICK,       // 三击事件
    ABS_KEY_EVENT_LONG_PRESS,         // 长按事件
    ABS_KEY_EVENT_LONG_REPEAT,        // 长按重复执行事件
    ABS_KEY_EVENT_LONG_PRESS_RELEASE, // 长按释放事件
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

void Abs_Key_InitQueue(void);
uint8_t Abs_Key_Event_Enqueue(Abs_Key_QueueItem_t *item);
uint8_t Abs_Key_Event_Dequeue(Abs_Key_QueueItem_t *item);
uint8_t Abs_Key_Event_Peek(Abs_Key_QueueItem_t *item);
void Abs_Key_MainFunction(void);

#endif
