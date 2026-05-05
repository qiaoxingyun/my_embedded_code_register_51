#include "Com_util.h"
#include "Int_OLED.h"
#include "Int_DS18B20.h"

void main()
{
    Int_OLED_Init();
    Int_OLED_Clean();
    while (1)
    {
        Int_OLED_ShowNum(0,0,Int_DS18B20_Get_Temperature());
        Com_util_DelayMs(500);
    }
    
}