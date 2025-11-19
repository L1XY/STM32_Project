#include "bsp_key.h"
#include "abs_key.h"
#include "abs_key_cfg.h"

static Abs_Key_Queue_t Abs_Key_Queue;
static Abs_Key_Data_t Abs_Key_Data[KEYMAX_NUM];

void Abs_Key_InitQueue(void)
{
    Abs_Key_Queue.front = 0;
    Abs_Key_Queue.rear = 0;
}

uint8_t Abs_Key_Queue_IsEmpty(void)
{
    uint8_t ret = ABS_KEY_QUEUE_NOK;
    if (Abs_Key_Queue.front == Abs_Key_Queue.rear)
    {
        ret = ABS_KEY_QUEUE_OK;
    }
    return ret;
}

uint8_t Abs_Key_Queue_IsFull(void)
{
    uint8_t ret = ABS_KEY_QUEUE_NOK;
    if (((Abs_Key_Queue.rear + 1) % ABS_KEY_QUEUE_SIZE) == Abs_Key_Queue.front)
    {
        ret = ABS_KEY_QUEUE_OK;
    }
    return ret;
}

uint8_t Abs_Key_Event_Enqueue(Abs_Key_QueueItem_t *item)
{
    uint8_t ret = ABS_KEY_QUEUE_OK;
    if (Abs_Key_Queue_IsFull() == ABS_KEY_QUEUE_OK)
    {
        ret = ABS_KEY_QUEUE_NOK;
    }
    else
    {
        (void)memcpy(&(Abs_Key_Queue.item_data[Abs_Key_Queue.rear]), item, sizeof(Abs_Key_QueueItem_t));
        Abs_Key_Queue.rear = (Abs_Key_Queue.rear + 1) % ABS_KEY_QUEUE_SIZE;
    }
    return ret;
}

uint8_t Abs_Key_Event_Dequeue(Abs_Key_QueueItem_t *item)
{
    uint8_t ret = ABS_KEY_QUEUE_OK;
    if (Abs_Key_Queue_IsEmpty() == ABS_KEY_QUEUE_OK)
    {
        ret = ABS_KEY_QUEUE_NOK;
    }
    else
    {
        (void)memcpy(item, &(Abs_Key_Queue.item_data[Abs_Key_Queue.front]), sizeof(Abs_Key_QueueItem_t));
        Abs_Key_Queue.front = (Abs_Key_Queue.front + 1) % ABS_KEY_QUEUE_SIZE;
    }
    return ret;
}

uint8_t Abs_Key_Event_Peek(Abs_Key_QueueItem_t *item)
{
    uint8_t ret = ABS_KEY_QUEUE_OK;
    if (Abs_Key_Queue_IsEmpty() == ABS_KEY_QUEUE_OK)
    {
        ret = ABS_KEY_QUEUE_NOK;
    }
    else
    {
        (void)memcpy(item, &(Abs_Key_Queue.item_data[Abs_Key_Queue.front]), sizeof(Abs_Key_QueueItem_t));
    }
    return ret;
}

void Abs_Key_InitData(void)
{
    uint8_t i = 0;
    for (i = 0; i < KEYMAX_NUM; i++)
    {
        Abs_Key_Data[i].state = ABS_KEY_STATE_RELEASED;
        Abs_Key_Data[i].pin_state = 0;
        Abs_Key_Data[i].click_count = 0;
        Abs_Key_Data[i].debounce_id = (Abs_Timer_ID_Type)(i * ABS_KEY_TIMER_NUM + 0);
        Abs_Key_Data[i].multi_click_id = (Abs_Timer_ID_Type)(i * ABS_KEY_TIMER_NUM + 1);
        Abs_Key_Data[i].long_press_id = (Abs_Timer_ID_Type)(i * ABS_KEY_TIMER_NUM + 2);
        Abs_Key_Data[i].long_press_repeat_id = (Abs_Timer_ID_Type)(i * ABS_KEY_TIMER_NUM + 3);
    }
}

void Abs_Key_Init(void)
{
    Abs_Key_InitQueue();
    Abs_Key_InitData();
}

/***************************************************************************************************/
/* KEY0 CALLBACK START */
void Abs_Key_Key0_MultiClick_Callback(void)
{
    switch (Abs_Key_Data[KEY0].state)
    {
    case ABS_KEY_STATE_RELEASED: // 释放状态
        break;
    case ABS_KEY_STATE_PRESS_DETECTED: // 按下检测(消抖中)
        break;
    case ABS_KEY_STATE_PRESSED: // 按下状态
        break;
    case ABS_KEY_STATE_RELEASE_DETECTED: // 释放检测(消抖中)
        break;
    case ABS_KEY_STATE_WAIT_DOUBLE: // 等待双击
        Abs_Key_Data[KEY0].state = ABS_KEY_STATE_RELEASED;
        Abs_Key_Data[KEY0].click_count = 0;
        Abs_Key_Data[KEY0].queue_item.key_index = KEY0;
        Abs_Key_Data[KEY0].queue_item.event = ABS_KEY_EVENT_SINGLE_CLICK;
        Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY0].queue_item);
        break;
    case ABS_KEY_STATE_WAIT_TRIPLE: // 等待三击
        Abs_Key_Data[KEY0].state = ABS_KEY_STATE_RELEASED;
        Abs_Key_Data[KEY0].click_count = 0;
        Abs_Key_Data[KEY0].queue_item.key_index = KEY0;
        Abs_Key_Data[KEY0].queue_item.event = ABS_KEY_EVENT_DOUBLE_CLICK;
        Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY0].queue_item);
        break;
    case ABS_KEY_STATE_LONG_PRESS: // 长按状态
        break;
    default:
        break;
    }
}

void Abs_Key_Key0_LongPressRepeat_Callback(void)
{
    Abs_Key_Data[KEY0].queue_item.key_index = KEY0;
    Abs_Key_Data[KEY0].queue_item.event = ABS_KEY_EVENT_LONG_REPEAT;
    Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY0].queue_item);
}

void Abs_Key_Key0_LongPress_Callback(void)
{
    switch (Abs_Key_Data[KEY0].state)
    {
    case ABS_KEY_STATE_RELEASED: // 释放状态
        break;
    case ABS_KEY_STATE_PRESS_DETECTED: // 按下检测(消抖中)
        break;
    case ABS_KEY_STATE_PRESSED: // 按下状态
        Abs_Key_Data[KEY0].state = ABS_KEY_STATE_LONG_PRESS;
        Abs_Key_Data[KEY0].queue_item.key_index = KEY0;
        Abs_Key_Data[KEY0].queue_item.event = ABS_KEY_EVENT_LONG_PRESS;
        Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY0].queue_item);
        Abs_Timer_Start(Abs_Key_Data[KEY0].long_press_repeat_id, ABS_TIMER_WK_CYCLE, ABS_KEY_LONG_PRESS_REPEA_TIME, Abs_Key_Key0_LongPressRepeat_Callback);
        break;
    case ABS_KEY_STATE_RELEASE_DETECTED: // 释放检测(消抖中)
        break;
    case ABS_KEY_STATE_WAIT_DOUBLE: // 等待双击
        break;
    case ABS_KEY_STATE_WAIT_TRIPLE: // 等待三击
        break;
    case ABS_KEY_STATE_LONG_PRESS: // 长按状态
        break;
    default:
        break;
    }
}

void Abs_Key_Key0_Debounce_Callback(void)
{
    uint8_t current_state;
    current_state = Bsp_Key_GetState(KEY0);
    switch (Abs_Key_Data[KEY0].state)
    {
    case ABS_KEY_STATE_RELEASED: // 释放状态
        break;
    case ABS_KEY_STATE_PRESS_DETECTED: // 按下检测(消抖中)
        if (current_state == KEY_PRESS)
        {
            Abs_Key_Data[KEY0].state = ABS_KEY_STATE_PRESSED;
            Abs_Timer_Start(Abs_Key_Data[KEY0].long_press_id, ABS_TIMER_WK_ONCE, ABS_KEY_LONG_PRESS_TIME, Abs_Key_Key0_LongPress_Callback);
        }
        else
        {
            Abs_Key_Data[KEY0].state = ABS_KEY_STATE_RELEASED;
        }
        break;
    case ABS_KEY_STATE_PRESSED: // 按下状态
        break;
    case ABS_KEY_STATE_RELEASE_DETECTED: // 释放检测(消抖中)
        if (current_state == KEY_PRESS)
        {
            Abs_Key_Data[KEY0].state = ABS_KEY_STATE_PRESSED;
        }
        else
        {
            if ((Abs_Key_Data[KEY0].queue_item.event == ABS_KEY_EVENT_LONG_PRESS) || (Abs_Key_Data[KEY0].queue_item.event == ABS_KEY_EVENT_LONG_REPEAT))
            {
                Abs_Key_Data[KEY0].state = ABS_KEY_STATE_RELEASED;
                Abs_Key_Data[KEY0].queue_item.key_index = KEY0;
                Abs_Key_Data[KEY0].queue_item.event = ABS_KEY_EVENT_LONG_PRESS_RELEASE;
                Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY0].queue_item);
                Abs_Timer_Stop(Abs_Key_Data[KEY0].long_press_repeat_id);
            }
            else
            {
                Abs_Key_Data[KEY0].click_count++;
                if (Abs_Key_Data[KEY0].click_count == 1)
                {
                    Abs_Key_Data[KEY0].state = ABS_KEY_STATE_WAIT_DOUBLE;
                    Abs_Timer_Start(Abs_Key_Data[KEY0].multi_click_id, ABS_TIMER_WK_ONCE, ABS_KEY_MULTI_CLICK_TIME, Abs_Key_Key0_MultiClick_Callback);
                }
                else if (Abs_Key_Data[KEY0].click_count == 2)
                {
                    Abs_Key_Data[KEY0].state = ABS_KEY_STATE_WAIT_TRIPLE;
                    Abs_Timer_Start(Abs_Key_Data[KEY0].multi_click_id, ABS_TIMER_WK_ONCE, ABS_KEY_MULTI_CLICK_TIME, Abs_Key_Key0_MultiClick_Callback);
                }
                else if (Abs_Key_Data[KEY0].click_count >= 3)
                {
                    Abs_Key_Data[KEY0].state = ABS_KEY_STATE_RELEASED;
                    Abs_Key_Data[KEY0].click_count = 0;
                    Abs_Key_Data[KEY0].queue_item.key_index = KEY0;
                    Abs_Key_Data[KEY0].queue_item.event = ABS_KEY_EVENT_TRIPLE_CLICK;
                    Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY0].queue_item);
                }
                else
                {
                }
            }
        }
        break;
    case ABS_KEY_STATE_WAIT_DOUBLE: // 等待双击
        break;
    case ABS_KEY_STATE_WAIT_TRIPLE: // 等待三击
        break;
    case ABS_KEY_STATE_LONG_PRESS: // 长按状态
        if (current_state == KEY_PRESS)
        {
            Abs_Key_Data[KEY0].state = ABS_KEY_STATE_LONG_PRESS;
        }
        else
        {
            Abs_Key_Data[KEY0].state = ABS_KEY_STATE_RELEASED;
            Abs_Key_Data[KEY0].queue_item.key_index = KEY0;
            Abs_Key_Data[KEY0].queue_item.event = ABS_KEY_EVENT_LONG_PRESS_RELEASE;
            Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY0].queue_item);
        }
        break;
    default:
        break;
    }
}
/* KEY0 CALLBACK END */
/***************************************************************************************************/

/***************************************************************************************************/
/* KEY1 CALLBACK START */
void Abs_Key_Key1_MultiClick_Callback(void)
{
    switch (Abs_Key_Data[KEY1].state)
    {
    case ABS_KEY_STATE_RELEASED: // 释放状态
        break;
    case ABS_KEY_STATE_PRESS_DETECTED: // 按下检测(消抖中)
        break;
    case ABS_KEY_STATE_PRESSED: // 按下状态
        break;
    case ABS_KEY_STATE_RELEASE_DETECTED: // 释放检测(消抖中)
        break;
    case ABS_KEY_STATE_WAIT_DOUBLE: // 等待双击
        Abs_Key_Data[KEY1].state = ABS_KEY_STATE_RELEASED;
        Abs_Key_Data[KEY1].click_count = 0;
        Abs_Key_Data[KEY1].queue_item.key_index = KEY1;
        Abs_Key_Data[KEY1].queue_item.event = ABS_KEY_EVENT_SINGLE_CLICK;
        Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY1].queue_item);
        break;
    case ABS_KEY_STATE_WAIT_TRIPLE: // 等待三击
        Abs_Key_Data[KEY1].state = ABS_KEY_STATE_RELEASED;
        Abs_Key_Data[KEY1].click_count = 0;
        Abs_Key_Data[KEY1].queue_item.key_index = KEY1;
        Abs_Key_Data[KEY1].queue_item.event = ABS_KEY_EVENT_DOUBLE_CLICK;
        Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY1].queue_item);
        break;
    case ABS_KEY_STATE_LONG_PRESS: // 长按状态
        break;
    default:
        break;
    }
}

void Abs_Key_Key1_LongPressRepeat_Callback(void)
{
    Abs_Key_Data[KEY1].queue_item.key_index = KEY1;
    Abs_Key_Data[KEY1].queue_item.event = ABS_KEY_EVENT_LONG_REPEAT;
    Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY1].queue_item);
}

void Abs_Key_Key1_LongPress_Callback(void)
{
    switch (Abs_Key_Data[KEY1].state)
    {
    case ABS_KEY_STATE_RELEASED: // 释放状态
        break;
    case ABS_KEY_STATE_PRESS_DETECTED: // 按下检测(消抖中)
        break;
    case ABS_KEY_STATE_PRESSED: // 按下状态
        Abs_Key_Data[KEY1].state = ABS_KEY_STATE_LONG_PRESS;
        Abs_Key_Data[KEY1].queue_item.key_index = KEY1;
        Abs_Key_Data[KEY1].queue_item.event = ABS_KEY_EVENT_LONG_PRESS;
        Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY1].queue_item);
        Abs_Timer_Start(Abs_Key_Data[KEY1].long_press_repeat_id, ABS_TIMER_WK_CYCLE, ABS_KEY_LONG_PRESS_REPEA_TIME, Abs_Key_Key1_LongPressRepeat_Callback);
        break;
    case ABS_KEY_STATE_RELEASE_DETECTED: // 释放检测(消抖中)
        break;
    case ABS_KEY_STATE_WAIT_DOUBLE: // 等待双击
        break;
    case ABS_KEY_STATE_WAIT_TRIPLE: // 等待三击
        break;
    case ABS_KEY_STATE_LONG_PRESS: // 长按状态
        break;
    default:
        break;
    }
}

void Abs_Key_Key1_Debounce_Callback(void)
{
    uint8_t current_state;
    current_state = Bsp_Key_GetState(KEY1);
    switch (Abs_Key_Data[KEY1].state)
    {
    case ABS_KEY_STATE_RELEASED: // 释放状态
        break;
    case ABS_KEY_STATE_PRESS_DETECTED: // 按下检测(消抖中)
        if (current_state == KEY_PRESS)
        {
            Abs_Key_Data[KEY1].state = ABS_KEY_STATE_PRESSED;
            Abs_Timer_Start(Abs_Key_Data[KEY1].long_press_id, ABS_TIMER_WK_ONCE, ABS_KEY_LONG_PRESS_TIME, Abs_Key_Key1_LongPress_Callback);
        }
        else
        {
            Abs_Key_Data[KEY1].state = ABS_KEY_STATE_RELEASED;
        }
        break;
    case ABS_KEY_STATE_PRESSED: // 按下状态
        break;
    case ABS_KEY_STATE_RELEASE_DETECTED: // 释放检测(消抖中)
        if (current_state == KEY_PRESS)
        {
            Abs_Key_Data[KEY1].state = ABS_KEY_STATE_PRESSED;
        }
        else
        {
            if ((Abs_Key_Data[KEY1].queue_item.event == ABS_KEY_EVENT_LONG_PRESS) || (Abs_Key_Data[KEY1].queue_item.event == ABS_KEY_EVENT_LONG_REPEAT))
            {
                Abs_Key_Data[KEY1].state = ABS_KEY_STATE_RELEASED;
                Abs_Key_Data[KEY1].queue_item.key_index = KEY1;
                Abs_Key_Data[KEY1].queue_item.event = ABS_KEY_EVENT_LONG_PRESS_RELEASE;
                Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY1].queue_item);
                Abs_Timer_Stop(Abs_Key_Data[KEY1].long_press_repeat_id);
            }
            else
            {
                Abs_Key_Data[KEY1].click_count++;
                if (Abs_Key_Data[KEY1].click_count == 1)
                {
                    Abs_Key_Data[KEY1].state = ABS_KEY_STATE_WAIT_DOUBLE;
                    Abs_Timer_Start(Abs_Key_Data[KEY1].multi_click_id, ABS_TIMER_WK_ONCE, ABS_KEY_MULTI_CLICK_TIME, Abs_Key_Key1_MultiClick_Callback);
                }
                else if (Abs_Key_Data[KEY1].click_count == 2)
                {
                    Abs_Key_Data[KEY1].state = ABS_KEY_STATE_WAIT_TRIPLE;
                    Abs_Timer_Start(Abs_Key_Data[KEY1].multi_click_id, ABS_TIMER_WK_ONCE, ABS_KEY_MULTI_CLICK_TIME, Abs_Key_Key1_MultiClick_Callback);
                }
                else if (Abs_Key_Data[KEY1].click_count >= 3)
                {
                    Abs_Key_Data[KEY1].state = ABS_KEY_STATE_RELEASED;
                    Abs_Key_Data[KEY1].click_count = 0;
                    Abs_Key_Data[KEY1].queue_item.key_index = KEY1;
                    Abs_Key_Data[KEY1].queue_item.event = ABS_KEY_EVENT_TRIPLE_CLICK;
                    Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY1].queue_item);
                }
                else
                {
                }
            }
        }
        break;
    case ABS_KEY_STATE_WAIT_DOUBLE: // 等待双击
        break;
    case ABS_KEY_STATE_WAIT_TRIPLE: // 等待三击
        break;
    case ABS_KEY_STATE_LONG_PRESS: // 长按状态
        if (current_state == KEY_PRESS)
        {
            Abs_Key_Data[KEY1].state = ABS_KEY_STATE_LONG_PRESS;
        }
        else
        {
            Abs_Key_Data[KEY1].state = ABS_KEY_STATE_RELEASED;
            Abs_Key_Data[KEY1].queue_item.key_index = KEY1;
            Abs_Key_Data[KEY1].queue_item.event = ABS_KEY_EVENT_LONG_PRESS_RELEASE;
            Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY1].queue_item);
        }
        break;
    default:
        break;
    }
}
/* KEY1 CALLBACK END */
/***************************************************************************************************/

/***************************************************************************************************/
/* KEY2 CALLBACK START */
void Abs_Key_Key2_MultiClick_Callback(void)
{
    switch (Abs_Key_Data[KEY2].state)
    {
    case ABS_KEY_STATE_RELEASED: // 释放状态
        break;
    case ABS_KEY_STATE_PRESS_DETECTED: // 按下检测(消抖中)
        break;
    case ABS_KEY_STATE_PRESSED: // 按下状态
        break;
    case ABS_KEY_STATE_RELEASE_DETECTED: // 释放检测(消抖中)
        break;
    case ABS_KEY_STATE_WAIT_DOUBLE: // 等待双击
        Abs_Key_Data[KEY2].state = ABS_KEY_STATE_RELEASED;
        Abs_Key_Data[KEY2].click_count = 0;
        Abs_Key_Data[KEY2].queue_item.key_index = KEY2;
        Abs_Key_Data[KEY2].queue_item.event = ABS_KEY_EVENT_SINGLE_CLICK;
        Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY2].queue_item);
        break;
    case ABS_KEY_STATE_WAIT_TRIPLE: // 等待三击
        Abs_Key_Data[KEY2].state = ABS_KEY_STATE_RELEASED;
        Abs_Key_Data[KEY2].click_count = 0;
        Abs_Key_Data[KEY2].queue_item.key_index = KEY2;
        Abs_Key_Data[KEY2].queue_item.event = ABS_KEY_EVENT_DOUBLE_CLICK;
        Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY2].queue_item);
        break;
    case ABS_KEY_STATE_LONG_PRESS: // 长按状态
        break;
    default:
        break;
    }
}

void Abs_Key_Key2_LongPressRepeat_Callback(void)
{
    Abs_Key_Data[KEY2].queue_item.key_index = KEY2;
    Abs_Key_Data[KEY2].queue_item.event = ABS_KEY_EVENT_LONG_REPEAT;
    Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY2].queue_item);
}

void Abs_Key_Key2_LongPress_Callback(void)
{
    switch (Abs_Key_Data[KEY2].state)
    {
    case ABS_KEY_STATE_RELEASED: // 释放状态
        break;
    case ABS_KEY_STATE_PRESS_DETECTED: // 按下检测(消抖中)
        break;
    case ABS_KEY_STATE_PRESSED: // 按下状态
        Abs_Key_Data[KEY2].state = ABS_KEY_STATE_LONG_PRESS;
        Abs_Key_Data[KEY2].queue_item.key_index = KEY2;
        Abs_Key_Data[KEY2].queue_item.event = ABS_KEY_EVENT_LONG_PRESS;
        Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY2].queue_item);
        Abs_Timer_Start(Abs_Key_Data[KEY2].long_press_repeat_id, ABS_TIMER_WK_CYCLE, ABS_KEY_LONG_PRESS_REPEA_TIME, Abs_Key_Key2_LongPressRepeat_Callback);
        break;
    case ABS_KEY_STATE_RELEASE_DETECTED: // 释放检测(消抖中)
        break;
    case ABS_KEY_STATE_WAIT_DOUBLE: // 等待双击
        break;
    case ABS_KEY_STATE_WAIT_TRIPLE: // 等待三击
        break;
    case ABS_KEY_STATE_LONG_PRESS: // 长按状态
        break;
    default:
        break;
    }
}

void Abs_Key_Key2_Debounce_Callback(void)
{
    uint8_t current_state;
    current_state = Bsp_Key_GetState(KEY2);
    switch (Abs_Key_Data[KEY2].state)
    {
    case ABS_KEY_STATE_RELEASED: // 释放状态
        break;
    case ABS_KEY_STATE_PRESS_DETECTED: // 按下检测(消抖中)
        if (current_state == KEY_PRESS)
        {
            Abs_Key_Data[KEY2].state = ABS_KEY_STATE_PRESSED;
            Abs_Timer_Start(Abs_Key_Data[KEY2].long_press_id, ABS_TIMER_WK_ONCE, ABS_KEY_LONG_PRESS_TIME, Abs_Key_Key2_LongPress_Callback);
        }
        else
        {
            Abs_Key_Data[KEY2].state = ABS_KEY_STATE_RELEASED;
        }
        break;
    case ABS_KEY_STATE_PRESSED: // 按下状态
        break;
    case ABS_KEY_STATE_RELEASE_DETECTED: // 释放检测(消抖中)
        if (current_state == KEY_PRESS)
        {
            Abs_Key_Data[KEY2].state = ABS_KEY_STATE_PRESSED;
        }
        else
        {
            if ((Abs_Key_Data[KEY2].queue_item.event == ABS_KEY_EVENT_LONG_PRESS) || (Abs_Key_Data[KEY2].queue_item.event == ABS_KEY_EVENT_LONG_REPEAT))
            {
                Abs_Key_Data[KEY2].state = ABS_KEY_STATE_RELEASED;
                Abs_Key_Data[KEY2].queue_item.key_index = KEY2;
                Abs_Key_Data[KEY2].queue_item.event = ABS_KEY_EVENT_LONG_PRESS_RELEASE;
                Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY2].queue_item);
                Abs_Timer_Stop(Abs_Key_Data[KEY2].long_press_repeat_id);
            }
            else
            {
                Abs_Key_Data[KEY2].click_count++;
                if (Abs_Key_Data[KEY2].click_count == 1)
                {
                    Abs_Key_Data[KEY2].state = ABS_KEY_STATE_WAIT_DOUBLE;
                    Abs_Timer_Start(Abs_Key_Data[KEY2].multi_click_id, ABS_TIMER_WK_ONCE, ABS_KEY_MULTI_CLICK_TIME, Abs_Key_Key2_MultiClick_Callback);
                }
                else if (Abs_Key_Data[KEY2].click_count == 2)
                {
                    Abs_Key_Data[KEY2].state = ABS_KEY_STATE_WAIT_TRIPLE;
                    Abs_Timer_Start(Abs_Key_Data[KEY2].multi_click_id, ABS_TIMER_WK_ONCE, ABS_KEY_MULTI_CLICK_TIME, Abs_Key_Key2_MultiClick_Callback);
                }
                else if (Abs_Key_Data[KEY2].click_count >= 3)
                {
                    Abs_Key_Data[KEY2].state = ABS_KEY_STATE_RELEASED;
                    Abs_Key_Data[KEY2].click_count = 0;
                    Abs_Key_Data[KEY2].queue_item.key_index = KEY2;
                    Abs_Key_Data[KEY2].queue_item.event = ABS_KEY_EVENT_TRIPLE_CLICK;
                    Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY2].queue_item);
                }
                else
                {
                }
            }
        }
        break;
    case ABS_KEY_STATE_WAIT_DOUBLE: // 等待双击
        break;
    case ABS_KEY_STATE_WAIT_TRIPLE: // 等待三击
        break;
    case ABS_KEY_STATE_LONG_PRESS: // 长按状态
        if (current_state == KEY_PRESS)
        {
            Abs_Key_Data[KEY2].state = ABS_KEY_STATE_LONG_PRESS;
        }
        else
        {
            Abs_Key_Data[KEY2].state = ABS_KEY_STATE_RELEASED;
            Abs_Key_Data[KEY2].queue_item.key_index = KEY2;
            Abs_Key_Data[KEY2].queue_item.event = ABS_KEY_EVENT_LONG_PRESS_RELEASE;
            Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY2].queue_item);
        }
        break;
    default:
        break;
    }
}
/* KEY2 CALLBACK END */
/***************************************************************************************************/

/***************************************************************************************************/
/* KEY3 CALLBACK START */
void Abs_Key_Key3_MultiClick_Callback(void)
{
    switch (Abs_Key_Data[KEY3].state)
    {
    case ABS_KEY_STATE_RELEASED: // 释放状态
        break;
    case ABS_KEY_STATE_PRESS_DETECTED: // 按下检测(消抖中)
        break;
    case ABS_KEY_STATE_PRESSED: // 按下状态
        break;
    case ABS_KEY_STATE_RELEASE_DETECTED: // 释放检测(消抖中)
        break;
    case ABS_KEY_STATE_WAIT_DOUBLE: // 等待双击
        Abs_Key_Data[KEY3].state = ABS_KEY_STATE_RELEASED;
        Abs_Key_Data[KEY3].click_count = 0;
        Abs_Key_Data[KEY3].queue_item.key_index = KEY3;
        Abs_Key_Data[KEY3].queue_item.event = ABS_KEY_EVENT_SINGLE_CLICK;
        Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY3].queue_item);
        break;
    case ABS_KEY_STATE_WAIT_TRIPLE: // 等待三击
        Abs_Key_Data[KEY3].state = ABS_KEY_STATE_RELEASED;
        Abs_Key_Data[KEY3].click_count = 0;
        Abs_Key_Data[KEY3].queue_item.key_index = KEY3;
        Abs_Key_Data[KEY3].queue_item.event = ABS_KEY_EVENT_DOUBLE_CLICK;
        Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY3].queue_item);
        break;
    case ABS_KEY_STATE_LONG_PRESS: // 长按状态
        break;
    default:
        break;
    }
}

void Abs_Key_Key3_LongPressRepeat_Callback(void)
{
    Abs_Key_Data[KEY3].queue_item.key_index = KEY3;
    Abs_Key_Data[KEY3].queue_item.event = ABS_KEY_EVENT_LONG_REPEAT;
    Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY3].queue_item);
}

void Abs_Key_Key3_LongPress_Callback(void)
{
    switch (Abs_Key_Data[KEY3].state)
    {
    case ABS_KEY_STATE_RELEASED: // 释放状态
        break;
    case ABS_KEY_STATE_PRESS_DETECTED: // 按下检测(消抖中)
        break;
    case ABS_KEY_STATE_PRESSED: // 按下状态
        Abs_Key_Data[KEY3].state = ABS_KEY_STATE_LONG_PRESS;
        Abs_Key_Data[KEY3].queue_item.key_index = KEY3;
        Abs_Key_Data[KEY3].queue_item.event = ABS_KEY_EVENT_LONG_PRESS;
        Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY3].queue_item);
        Abs_Timer_Start(Abs_Key_Data[KEY3].long_press_repeat_id, ABS_TIMER_WK_CYCLE, ABS_KEY_LONG_PRESS_REPEA_TIME, Abs_Key_Key3_LongPressRepeat_Callback);
        break;
    case ABS_KEY_STATE_RELEASE_DETECTED: // 释放检测(消抖中)
        break;
    case ABS_KEY_STATE_WAIT_DOUBLE: // 等待双击
        break;
    case ABS_KEY_STATE_WAIT_TRIPLE: // 等待三击
        break;
    case ABS_KEY_STATE_LONG_PRESS: // 长按状态
        break;
    default:
        break;
    }
}

void Abs_Key_Key3_Debounce_Callback(void)
{
    uint8_t current_state;
    current_state = Bsp_Key_GetState(KEY3);
    switch (Abs_Key_Data[KEY3].state)
    {
    case ABS_KEY_STATE_RELEASED: // 释放状态
        break;
    case ABS_KEY_STATE_PRESS_DETECTED: // 按下检测(消抖中)
        if (current_state == KEY_PRESS)
        {
            Abs_Key_Data[KEY3].state = ABS_KEY_STATE_PRESSED;
            Abs_Timer_Start(Abs_Key_Data[KEY3].long_press_id, ABS_TIMER_WK_ONCE, ABS_KEY_LONG_PRESS_TIME, Abs_Key_Key3_LongPress_Callback);
        }
        else
        {
            Abs_Key_Data[KEY3].state = ABS_KEY_STATE_RELEASED;
        }
        break;
    case ABS_KEY_STATE_PRESSED: // 按下状态
        break;
    case ABS_KEY_STATE_RELEASE_DETECTED: // 释放检测(消抖中)
        if (current_state == KEY_PRESS)
        {
            Abs_Key_Data[KEY3].state = ABS_KEY_STATE_PRESSED;
        }
        else
        {
            if ((Abs_Key_Data[KEY3].queue_item.event == ABS_KEY_EVENT_LONG_PRESS) || (Abs_Key_Data[KEY3].queue_item.event == ABS_KEY_EVENT_LONG_REPEAT))
            {
                Abs_Key_Data[KEY3].state = ABS_KEY_STATE_RELEASED;
                Abs_Key_Data[KEY3].queue_item.key_index = KEY3;
                Abs_Key_Data[KEY3].queue_item.event = ABS_KEY_EVENT_LONG_PRESS_RELEASE;
                Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY3].queue_item);
                Abs_Timer_Stop(Abs_Key_Data[KEY3].long_press_repeat_id);
            }
            else
            {
                Abs_Key_Data[KEY3].click_count++;
                if (Abs_Key_Data[KEY3].click_count == 1)
                {
                    Abs_Key_Data[KEY3].state = ABS_KEY_STATE_WAIT_DOUBLE;
                    Abs_Timer_Start(Abs_Key_Data[KEY3].multi_click_id, ABS_TIMER_WK_ONCE, ABS_KEY_MULTI_CLICK_TIME, Abs_Key_Key3_MultiClick_Callback);
                }
                else if (Abs_Key_Data[KEY3].click_count == 2)
                {
                    Abs_Key_Data[KEY3].state = ABS_KEY_STATE_WAIT_TRIPLE;
                    Abs_Timer_Start(Abs_Key_Data[KEY3].multi_click_id, ABS_TIMER_WK_ONCE, ABS_KEY_MULTI_CLICK_TIME, Abs_Key_Key3_MultiClick_Callback);
                }
                else if (Abs_Key_Data[KEY3].click_count >= 3)
                {
                    Abs_Key_Data[KEY3].state = ABS_KEY_STATE_RELEASED;
                    Abs_Key_Data[KEY3].click_count = 0;
                    Abs_Key_Data[KEY3].queue_item.key_index = KEY3;
                    Abs_Key_Data[KEY3].queue_item.event = ABS_KEY_EVENT_TRIPLE_CLICK;
                    Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY3].queue_item);
                }
                else
                {
                }
            }
        }
        break;
    case ABS_KEY_STATE_WAIT_DOUBLE: // 等待双击
        break;
    case ABS_KEY_STATE_WAIT_TRIPLE: // 等待三击
        break;
    case ABS_KEY_STATE_LONG_PRESS: // 长按状态
        if (current_state == KEY_PRESS)
        {
            Abs_Key_Data[KEY3].state = ABS_KEY_STATE_LONG_PRESS;
        }
        else
        {
            Abs_Key_Data[KEY3].state = ABS_KEY_STATE_RELEASED;
            Abs_Key_Data[KEY3].queue_item.key_index = KEY3;
            Abs_Key_Data[KEY3].queue_item.event = ABS_KEY_EVENT_LONG_PRESS_RELEASE;
            Abs_Key_Event_Enqueue(&Abs_Key_Data[KEY3].queue_item);
        }
        break;
    default:
        break;
    }
}
/* KEY3 CALLBACK END */
/***************************************************************************************************/

void Abs_Key_ProcessState(uint8_t keyx, uint8_t new_state)
{
    if (new_state != Abs_Key_Data[keyx].state)
    {
        Abs_Key_Data[keyx].pin_state = new_state;
        if (new_state == KEY_PRESS)
        {
            switch (Abs_Key_Data[keyx].state)
            {
            case ABS_KEY_STATE_RELEASED: // 释放状态
                Abs_Key_Data[keyx].state = ABS_KEY_STATE_PRESS_DETECTED;
                Abs_Timer_Start(Abs_Key_Data[keyx].debounce_id, ABS_TIMER_WK_ONCE, ABS_KEY_DEBOUNCE_TIME, Abs_Key_DebounceTimerCallBack_Table[keyx].callback);
                break;
            case ABS_KEY_STATE_PRESS_DETECTED: // 按下检测(消抖中)
                break;
            case ABS_KEY_STATE_PRESSED: // 按下状态
                break;
            case ABS_KEY_STATE_RELEASE_DETECTED: // 释放检测(消抖中)
                break;
            case ABS_KEY_STATE_WAIT_DOUBLE: // 等待双击
                Abs_Key_Data[keyx].state = ABS_KEY_STATE_PRESS_DETECTED;
                Abs_Timer_Start(Abs_Key_Data[keyx].debounce_id, ABS_TIMER_WK_ONCE, ABS_KEY_DEBOUNCE_TIME, Abs_Key_DebounceTimerCallBack_Table[keyx].callback);
                break;
            case ABS_KEY_STATE_WAIT_TRIPLE: // 等待三击
                Abs_Key_Data[keyx].state = ABS_KEY_STATE_PRESS_DETECTED;
                Abs_Timer_Start(Abs_Key_Data[keyx].debounce_id, ABS_TIMER_WK_ONCE, ABS_KEY_DEBOUNCE_TIME, Abs_Key_DebounceTimerCallBack_Table[keyx].callback);
                break;
            case ABS_KEY_STATE_LONG_PRESS: // 长按状态
                Abs_Key_Data[keyx].state = ABS_KEY_STATE_PRESS_DETECTED;
                Abs_Timer_Start(Abs_Key_Data[keyx].debounce_id, ABS_TIMER_WK_ONCE, ABS_KEY_DEBOUNCE_TIME, Abs_Key_DebounceTimerCallBack_Table[keyx].callback);
                break;
            default:
                break;
            }
        }
        else
        {
            switch (Abs_Key_Data[keyx].state)
            {
            case ABS_KEY_STATE_RELEASED: // 释放状态
                break;
            case ABS_KEY_STATE_PRESS_DETECTED: // 按下检测(消抖中)
                break;
            case ABS_KEY_STATE_PRESSED: // 按下状态
                Abs_Key_Data[keyx].state = ABS_KEY_STATE_RELEASE_DETECTED;
                Abs_Timer_Start(Abs_Key_Data[keyx].debounce_id, ABS_TIMER_WK_ONCE, ABS_KEY_DEBOUNCE_TIME, Abs_Key_DebounceTimerCallBack_Table[keyx].callback);
                break;
            case ABS_KEY_STATE_RELEASE_DETECTED: // 释放检测(消抖中)
                break;
            case ABS_KEY_STATE_WAIT_DOUBLE: // 等待双击
                break;
            case ABS_KEY_STATE_WAIT_TRIPLE: // 等待三击
                break;
            case ABS_KEY_STATE_LONG_PRESS: // 长按状态
                Abs_Key_Data[keyx].state = ABS_KEY_STATE_RELEASE_DETECTED;
                Abs_Timer_Start(Abs_Key_Data[keyx].debounce_id, ABS_TIMER_WK_ONCE, ABS_KEY_DEBOUNCE_TIME, Abs_Key_DebounceTimerCallBack_Table[keyx].callback);
                break;
            default:
                break;
            }
        }
    }
}

void Abs_Key_MainFunction(void)
{
    uint8_t i, j;
    Abs_Key_QueueItem_t abs_key_queue_item;
    const Abs_Key_CallBack_t *callback_table;
    if (Abs_Key_Event_Dequeue(&abs_key_queue_item) == ABS_KEY_QUEUE_OK)
    {
        for (i = 0; i < KEYMAX_NUM; i++)
        {
            if (abs_key_queue_item.key_index == Abs_Key_CallBackCfg_Table[i].key_index)
            {
                callback_table = Abs_Key_CallBackCfg_Table[i].key_event_table;
                for (j = 0; j < (uint8_t)ABS_KEY_EVENT_NUM; j++)
                {
                    if (abs_key_queue_item.event == callback_table[j].event)
                    {
                        if (callback_table[j].callback != NULL)
                        {
                            callback_table[j].callback();
                        }
                        break;
                    }
                }
                break;
            }
        }
        // printf("Abs_Key_Event_Dequeue, key_index = %d, event = %d \r\n", abs_key_queue_item.key_index, abs_key_queue_item.event);
    }
}
