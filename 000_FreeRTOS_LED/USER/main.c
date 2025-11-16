#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bsp_led.h"

// 任务句柄
TaskHandle_t Start_TaskHandler;
TaskHandle_t Bsp_Led_TaskHandler;

void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();
    xTaskCreate((TaskFunction_t)Bsp_Led_task,          // 任务函数
                (const char *)"Bsp_Led_task",          // 任务名称
                (uint16_t)50,                          // 任务堆栈大小
                (void *)NULL,                          // 传递给任务函数的参数
                (UBaseType_t)2,                        // 任务优先级
                (TaskHandle_t *)&Bsp_Led_TaskHandler); // 任务句柄
    vTaskDelete(Start_TaskHandler);
    taskEXIT_CRITICAL();
}

int main(void)
{
    Bsp_Led_Init();

    xTaskCreate((TaskFunction_t)start_task,          // 任务函数
                (const char *)"start_task",          // 任务名称
                (uint16_t)50,                        // 任务堆栈大小
                (void *)NULL,                        // 传递给任务函数的参数
                (UBaseType_t)1,                      // 任务优先级
                (TaskHandle_t *)&Start_TaskHandler); // 任务句柄
    vTaskStartScheduler();                           // 开启任务调度
    while(1);
}
