#include "FreeRTOS.h"
#include "task.h"
#include "task_10ms.h"
#include "bsp_led.h"
#include "abs_board.h"

void SW_Timer_Test_Callback(void)
{
    printf("Timer Out Event. \n");
}

void App_Task_10ms(void *pvParameters)
{
    uint8_t i;
    TickType_t lastWakeTime = xTaskGetTickCount();
    Abs_Timer_Start(ABS_TIMER_ID_TEST, ABS_TIMER_WK_CYCLE, 500, SW_Timer_Test_Callback);
    while (1)
    {
        vTaskDelayUntil(&lastWakeTime, 10);
        Abs_Timer_MainFunction();
        i++;
        if (i == 50)
        {
            i = 0;
            Bsp_Led_Flip(LED0);
            Bsp_Led_Flip(LED1);
        }
    }
}
