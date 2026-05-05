#include "Com_util.h"
#include <STC89C5xRC.H>
#include "Dri_DigitalTube_Matrix.h"

#define MATRIX_COUNT 4
#define LED_en P34
#define SMG_en P36
#define BUZZER P46

u8 Check_Matrix_Keypad()
{
    u8 i,j;
    u8 colums[] = {0xFE,0xFD,0xFB,0xF7}; //判断的行
    u8 lines[] = {0x10,0x20,0x40,0x80}; //用这个判断行内的每一列
    for ( i = 0; i < MATRIX_COUNT; i++)
    {
        P2 = colums[i];
        for (j = 0;j < MATRIX_COUNT; j++)
        {
            if ((P2 & lines[j]) == 0x00)
            {
                Com_util_DelayMs(10);
                if ((P2 & lines[j]) == 0x00)
                {
                    while ((P2 & lines[j]) == 0x00);
                    return 5 + j + i *4;
                }   
            }       
        }
    } 
    return 0;
}

void buzzer()
{
    u8 count = 100;
    while (count > 0)
    {
        BUZZER = ~BUZZER;
        Com_util_DelayMs(1);
        --count;
    }
    
}

void main()
{
    u8 key;
    LED_en = 0;
    SMG_en = 0;
    while (1)
    {
        key = Check_Matrix_Keypad();
        if (key)
        {
            Dri_DigitalTube_Displaynum(key);
            buzzer();
        }
        Dri_DigitalTube_Refresh();     
    }
}