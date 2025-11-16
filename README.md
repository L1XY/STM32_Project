# STM32_Project

本工程基于正点原子STM32战舰开发板实现。主控芯片为**STM32F103ZET6**。

**《000_FreeRTOS_LED》**：移植FreeRTOS，简单实现了任务的创建和调用。

**《001_FreeRTOS_UART》**：增加串口收发功能，串口中断接收。

**《002_FreeRTOS_KEY》**：增加按键功能，实现外部触发；增加周期调度的软件定时器，用于按键定时。