#include "FreeRTOS.h"
#include "task.h"
#include "task_10ms.h"
#include "bsp_board.h"
#include "abs_board.h"

void App_Task_10ms(void *pvParameters)
{
    uint8_t i, j;
    TickType_t lastWakeTime = xTaskGetTickCount();
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
            Bsp_Led_Flip(LED0);
            Bsp_Led_Flip(LED1);
        }
        Abs_Key_MainFunction();
        Abs_Timer_MainFunction();
    }
}
