#include "FreeRTOS.h"
#include "task.h"
#include "task_100ms.h"
#include "task_config.h"
#include "bsp_board.h"
#include "abs_board.h"
#include "drv_board.h"

uint32_t encoder_counter;
void App_Task_100ms(void *pvParameters)
{
    uint8_t i;
    TickType_t lastWakeTime = xTaskGetTickCount();

    while (1)
    {
        vTaskDelayUntil(&lastWakeTime, 100);

        // OLED_ShowHexNum(1, 1, Bsp_Adc_Value[ADC_00], 4, OLED_8X16);
        // OLED_ShowHexNum(1, 16, Bsp_Adc_Value[ADC_01], 4, OLED_8X16);
        // OLED_ShowHexNum(1, 32, Bsp_Adc_Value[ADC_02], 4, OLED_8X16);

        i++;
        if (i >= 5)
        {
            i = 0;
            Bsp_Led_Flip(LED0);
            Bsp_Led_Flip(LED1);
        }
        if (xSemaphoreTake(xI2C1_Mutex, portMAX_DELAY) == pdPASS)
        {
            encoder_counter = Bsp_Tim3_Encoder_Get();
            OLED_ShowNum(0, 8, (uint32_t)encoder_counter, 6, OLED_8X16);
            Drv_OLED_MainFunction();

            xSemaphoreGive(xI2C1_Mutex);
        }
        else
        {
            printf("xI2C1_Mutex Take Error! ");
        }
    }
}
