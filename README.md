# STM32_Project

本工程基于正点原子STM32战舰开发板实现。主控芯片为**STM32F103ZET6**。

**《000_FreeRTOS_LED》**：移植FreeRTOS，简单实现了任务的创建和调用。

**《001_FreeRTOS_UART》**：增加串口收发功能，串口中断接收。

**《002_FreeRTOS_KEY》**：增加按键功能，实现外部触发；增加周期调度的软件定时器，用于按键定时。

**《003_FreeRTOS_I2C》**：新增I2C驱动，通过按键回调函数实现AT24CXX的I2C协议的EEPROM读写功能。

**《004_FreeRTOS_SPI》**：新增SPI驱动，通过按键回调函数实现读取W25Q128的MID和DID的功能。

**《005_FreeRTOS_OLED》**：移植“江协科技”的OLED显示屏。

**《006_FreeRTOS_ADC》**：新增ADC驱动，通过DMA读取转换完成的ADC多通道数据到数组中，应用层直接读取数组。
