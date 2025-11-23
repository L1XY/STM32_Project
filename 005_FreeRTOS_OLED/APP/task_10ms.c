#include "FreeRTOS.h"
#include "task.h"
#include "task_10ms.h"
#include "task_config.h"
#include "bsp_board.h"
#include "abs_board.h"

void App_Task_10ms(void *pvParameters)
{
    TickType_t lastWakeTime = xTaskGetTickCount();
    while (1)
    {
        vTaskDelayUntil(&lastWakeTime, 10);
        Abs_Timer_MainFunction();
        Abs_Key_MainFunction();
    }
}
