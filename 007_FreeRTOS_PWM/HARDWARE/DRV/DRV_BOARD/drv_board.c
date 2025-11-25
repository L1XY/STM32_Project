#include "drv_board.h"

void Drv_Init(void)
{
    Drv_AT24CXX_Init();
    Drv_W25QXX_Init();
    Drv_OLED_Init();
}
