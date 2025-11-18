#include "FreeRTOS.h"
#include "task.h"
#include "task_10ms.h"
#include "bsp_board.h"
#include "abs_board.h"

void Abs_Timer_Test_Callback(void)
{
    printf("Timer Out Event. \n");
}

void App_Task_10ms(void *pvParameters)
{
    uint8_t i, j;
    Abs_Key_QueueItem_t test_key_queue_item;
    TickType_t lastWakeTime = xTaskGetTickCount();
    Abs_Timer_Start(ABS_TIMER_ID_TEST, ABS_TIMER_WK_CYCLE, 2000, Abs_Timer_Test_Callback);
    while (1)
    {
        vTaskDelayUntil(&lastWakeTime, 10);
        i++;
        if (i >= 50)
        {
            i = 0;
            j++;
            if (j >= 100)
            {
                j = 0;
            }
            test_key_queue_item.key_index = j;
            test_key_queue_item.event = (Abs_Key_Event_t)(j % 5);
            if (Abs_Key_Event_Enqueue(&test_key_queue_item) == ABS_KEY_QUEUE_OK)
            {
                printf("Abs_Key_Event_Enqueue, key_index = %d, event = %d \r\n", test_key_queue_item.key_index, test_key_queue_item.event);
            }
            Bsp_Led_Flip(LED0);
            Bsp_Led_Flip(LED1);
        }
        Abs_Key_MainFunction();
        Abs_Timer_MainFunction();
    }
}
