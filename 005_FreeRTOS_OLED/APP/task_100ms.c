#include "FreeRTOS.h"
#include "task.h"
#include "task_100ms.h"
#include "task_config.h"
#include "bsp_board.h"
#include "drv_board.h"

void App_Task_100ms(void *pvParameters)
{
    uint8_t i;
    TickType_t lastWakeTime = xTaskGetTickCount();
    while (1)
    {
        vTaskDelayUntil(&lastWakeTime, 100);
        i++;
        OLED_Clear();
        OLED_Printf(0, 20 + i, OLED_8X16, "你好，世界。");
        OLED_ShowString(0, 0 + i, "Hello World!", OLED_8X16);
        if (i >= 5)
        {
            i = 0;
            Bsp_Led_Flip(LED0);
            Bsp_Led_Flip(LED1);
        }
        if (xSemaphoreTake(xI2C1_Mutex, portMAX_DELAY) == pdPASS)
        {
            Drv_OLED_MainFunction();
            xSemaphoreGive(xI2C1_Mutex);
        }
        else
        {
            printf("xI2C1_Mutex Take Error! ");
        }
    }
}
