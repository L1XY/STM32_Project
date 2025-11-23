#include "task_config.h"
#include "FreeRTOS.h"
#include "task.h"

SemaphoreHandle_t xI2C1_Mutex;
SemaphoreHandle_t xSPI2_Mutex;

void vApplicationStartupHook(void)
{
    // 创建互斥锁
    xI2C1_Mutex = xSemaphoreCreateMutex();
    xSPI2_Mutex = xSemaphoreCreateMutex();
}
