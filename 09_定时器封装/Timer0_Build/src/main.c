#include "Com_util.h"
#include "Dri_Timer0.h"
#include <STC89C5xRC.H>

#define LED1 P00

void LED_Blink()
{
    static u16 count = 0;
    count++;
    if (count >= 500)
    {
        LED1 = ~LED1;
        count = 0;
    }
    
}

void main()
{
    Dri_Timer0_Init();
    Dri_Timer0_Register_Callback(LED_Blink);
    while (1)
    {
    }
    
}