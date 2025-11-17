#include "abs_key.h"

static Abs_Key_Queue_t Abs_Key_Queue;

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
        Abs_Key_Queue.rear = (Abs_Key_Queue.rear + 1) % ABS_KEY_QUEUE_SIZE;
        (void)memcpy(&(Abs_Key_Queue.item_data[Abs_Key_Queue.rear]), item, sizeof(Abs_Key_QueueItem_t));
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

void Abs_Key_MainFunction(void)
{
    Abs_Key_QueueItem_t abs_key_queue_item;
    if (Abs_Key_Event_Dequeue(&abs_key_queue_item) == ABS_KEY_QUEUE_OK)
    {
        printf("key_index = %d, event = %d \r\n", abs_key_queue_item.key_index, abs_key_queue_item.event);
    }
}
