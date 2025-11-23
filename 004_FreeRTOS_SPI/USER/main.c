#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"
#include "bsp_board.h"
#include "abs_board.h"
#include "task_10ms.h"

// 任务句柄
TaskHandle_t Start_TaskHandler;
TaskHandle_t App_10ms_TaskHandler;

void Start_task(void *pvParameters)
{
    taskENTER_CRITICAL();
    xTaskCreate((TaskFunction_t)App_Task_10ms,          // 任务函数
                (const char *)"App_Task_10ms",          // 任务名称
                (uint16_t)50,                           // 任务堆栈大小
                (void *)NULL,                           // 传递给任务函数的参数
                (UBaseType_t)2,                         // 任务优先级
                (TaskHandle_t *)&App_10ms_TaskHandler); // 任务句柄
    printf("App_Task_10ms Create Success! \n");
    vTaskDelete(Start_TaskHandler);
    taskEXIT_CRITICAL();
}

int main(void)
{
    Bsp_Init();
    Abs_Init();
    xTaskCreate((TaskFunction_t)Start_task,          // 任务函数
                (const char *)"Start_task",          // 任务名称
                (uint16_t)50,                        // 任务堆栈大小
                (void *)NULL,                        // 传递给任务函数的参数
                (UBaseType_t)1,                      // 任务优先级
                (TaskHandle_t *)&Start_TaskHandler); // 任务句柄
    printf("Start_task Create Success! \n");
    vTaskStartScheduler();
    while (1)
        ;
}
