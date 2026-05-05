#include "Com_util.h"
#include "Int_OLED.h"

void main()
{
    Int_OLED_Init();
    Int_OLED_Clean();
    Int_OLED_ShowStr(0,0,"Hello World!");
    Int_OLED_ShowStr(0,1,"Q X Y");
    Int_OLED_ShowNum(0,2,-12345678);
    while (1)
    {
        
    }
    
}