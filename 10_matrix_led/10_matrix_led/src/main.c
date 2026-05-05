#include "Com_util.h"
#include <STC89C5xRC.H>
#include "Int_LED_Matrix.h"
#include "Dri_Timer0.h"

void main()
{
    u8 pic[8] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};
    Dri_Timer0_Init();
    Init_LEDMatrix_Init();
    Int_LEDMatrix_SetPic(pic);
    while (1)
    {   
    }
    
}