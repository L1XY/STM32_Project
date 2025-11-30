#ifndef __TASK_CONFIG_H
#define __TASK_CONFIG_H
#include "FreeRTOS.h"
#include "semphr.h"

extern SemaphoreHandle_t xI2C1_Mutex;
extern SemaphoreHandle_t xSPI2_Mutex;
void vApplicationStartupHook(void);

#endif
