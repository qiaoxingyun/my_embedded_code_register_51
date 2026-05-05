#include <STC89C5xRC.H>
#include "Com_util.h"

#define SW1 P42
#define SW2 P43
#define SW3 P32
#define SW4 P33

#define LED1 P00
#define LED2 P01
#define LED3 P02
#define LED4 P03


void main()
{
    while (1)
    {
       if (SW1 == 0)
       {
            Com_util_DelayMs(10);
            if (SW1 == 0)
            {
                while (SW1 == 0);
                LED1 = ~LED1;
            }
            
       }
       if (SW2 == 0)
       {
            Com_util_DelayMs(10);
            if (SW2 == 0)
            {
                while (SW2 == 0);
                LED2 = ~LED2;
            }
            
       }
       if (SW3 == 0)
       {
            Com_util_DelayMs(10);
            if (SW3 == 0)
            {
                while (SW3 == 0);
                LED3 = ~LED3;
            }
            
       }
       if (SW4 == 0)
       {
            Com_util_DelayMs(10);
            if (SW4 ==0)
            {
                while (SW4 == 0);
                LED4 = ~LED4;
            }
            
       }
        
    }
    
}