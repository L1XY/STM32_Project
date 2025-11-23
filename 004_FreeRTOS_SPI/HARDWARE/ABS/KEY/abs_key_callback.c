#include "stdio.h"
#include "abs_key_callback.h"
#include "drv_AT24CXX.h"
#include "drv_W25QXX.h"

void Abs_Key_Key0_Event_Single_Click(void)
{
    uint8_t i = 0;
    uint8_t readData[8] = {0};
    Drv_AT24CXX_Status_t ret = DRV_AT24CXX_SUCCESS;

    ret = Drv_AT24CXX_Read(0x08, readData, 8);

    if (ret == DRV_AT24CXX_SUCCESS)
    {
        printf("Read AT24Cxx Finish! Read Data: \n");

        for (i = 0; i < 8; i++)
        {
            printf("0x%02X ", readData[i]);
        }

        printf("\n");
    }
    else
    {
        printf("Read AT24Cxx Error!\n");
    }

    /* printf("Abs_Key_Key0_Event_Single_Click! \n"); */
}
void Abs_Key_Key0_Event_Double_Click(void)
{
    uint8_t i = 0;
    uint8_t writeData[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    Drv_AT24CXX_Status_t ret = DRV_AT24CXX_SUCCESS;

    ret = Drv_AT24CXX_Write(0x08, &writeData[0], 8);

    if (ret == DRV_AT24CXX_SUCCESS)
    {
        printf("Write AT24Cxx Finish! Write Data: \n");

        for (i = 0; i < 8; i++)
        {
            printf("0x%02X ", writeData[i]);
        }

        printf("\n");
    }
    else
    {
        printf("Write AT24Cxx Error!\n");
    }

    /* printf("Abs_Key_Key0_Event_Double_Click! \n"); */
}
void Abs_Key_Key0_Event_Triple_Click(void)
{
    uint8_t i = 0;
    uint8_t writeData[8] = {8, 7, 6, 5, 4, 3, 2, 1};
    Drv_AT24CXX_Status_t ret = DRV_AT24CXX_SUCCESS;

    ret = Drv_AT24CXX_Write(0x08, &writeData[0], 8);

    if (ret == DRV_AT24CXX_SUCCESS)
    {
        printf("Write AT24Cxx Finish! Write Data: \n");

        for (i = 0; i < 8; i++)
        {
            printf("0x%02X ", writeData[i]);
        }

        printf("\n");
    }
    else
    {
        printf("Write AT24Cxx Error!\n");
    }

    /* printf("Abs_Key_Key0_Event_Triple_Click! \n"); */
}
void Abs_Key_Key0_Event_Long_Press(void)
{
    printf("Abs_Key_Key0_Event_Long_Press! \n");
}
void Abs_Key_Key0_Event_Long_Press_Repeat(void)
{
    printf("Abs_Key_Key0_Event_Long_Press_Repeat! \n");
}
void Abs_Key_Key0_Event_Long_Press_Release(void)
{
    printf("Abs_Key_Key0_Event_Long_Press_Release! \n");
}

void Abs_Key_Key1_Event_Single_Click(void)
{
    uint8_t mid;
    uint16_t did;
    Drv_W25QXX_Status_t ret = DRV_W25QXX_SUCCESS;

    ret = Drv_W25QXX_ReadID(&mid, &did);

    if (ret == DRV_W25QXX_SUCCESS)
    {
        printf("Read W25QXX MID: %02X, DID: %04X!\n", mid, did);
    }
    else
    {
        printf("Read W25QXX MID And DID Error!\n");
    }

    /* printf("Abs_Key_Key1_Event_Single_Click! \n"); */
}
void Abs_Key_Key1_Event_Double_Click(void)
{
    printf("Abs_Key_Key1_Event_Double_Click! \n");
}
void Abs_Key_Key1_Event_Triple_Click(void)
{
    printf("Abs_Key_Key1_Event_Triple_Click! \n");
}
void Abs_Key_Key1_Event_Long_Press(void)
{
    printf("Abs_Key_Key1_Event_Long_Press! \n");
}
void Abs_Key_Key1_Event_Long_Press_Repeat(void)
{
    printf("Abs_Key_Key1_Event_Long_Press_Repeat! \n");
}
void Abs_Key_Key1_Event_Long_Press_Release(void)
{
    printf("Abs_Key_Key1_Event_Long_Press_Release! \n");
}

void Abs_Key_Key2_Event_Single_Click(void)
{
    printf("Abs_Key_Key2_Event_Single_Click! \n");
}
void Abs_Key_Key2_Event_Double_Click(void)
{
    printf("Abs_Key_Key2_Event_Double_Click! \n");
}
void Abs_Key_Key2_Event_Triple_Click(void)
{
    printf("Abs_Key_Key2_Event_Triple_Click! \n");
}
void Abs_Key_Key2_Event_Long_Press(void)
{
    printf("Abs_Key_Key2_Event_Long_Press! \n");
}
void Abs_Key_Key2_Event_Long_Press_Repeat(void)
{
    printf("Abs_Key_Key2_Event_Long_Press_Repeat! \n");
}
void Abs_Key_Key2_Event_Long_Press_Release(void)
{
    printf("Abs_Key_Key2_Event_Long_Press_Release! \n");
}

void Abs_Key_Key3_Event_Single_Click(void)
{
    printf("Abs_Key_Key3_Event_Single_Click! \n");
}
void Abs_Key_Key3_Event_Double_Click(void)
{
    printf("Abs_Key_Key3_Event_Double_Click! \n");
}
void Abs_Key_Key3_Event_Triple_Click(void)
{
    printf("Abs_Key_Key3_Event_Triple_Click! \n");
}
void Abs_Key_Key3_Event_Long_Press(void)
{
    printf("Abs_Key_Key3_Event_Long_Press! \n");
}
void Abs_Key_Key3_Event_Long_Press_Repeat(void)
{
    printf("Abs_Key_Key3_Event_Long_Press_Repeat! \n");
}
void Abs_Key_Key3_Event_Long_Press_Release(void)
{
    printf("Abs_Key_Key3_Event_Long_Press_Release! \n");
}
