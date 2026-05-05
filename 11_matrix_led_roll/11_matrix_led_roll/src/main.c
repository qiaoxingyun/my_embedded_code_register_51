#include "Com_util.h"
#include "Int_LED_Matrix.h"
#include "Dri_Timer0.h"

u8 picture[27] = {0xF8, 0x0A, 0xEC, 0xAF, 0xEC, 0x8A, 0xF8, 0x00,
                  0x10, 0xF9, 0x97, 0xF1, 0x88, 0xAA, 0xFF, 0xAA,
                  0x88, 0x00, 0x14, 0x0A, 0xF5, 0x92, 0x92, 0xF5,
                  0x0A, 0x14,0x00};

void main()
{
    u8 i;
    Dri_Timer0_Init();
    Init_LEDMatrix_Init();
    while (1)
    {
        for ( i = 0; i < 27; i++)
        {
            Init_LEDMatrix_Shift(~picture[i]);
            Com_util_DelayMs(200);
        }
        
    }
    
}