#include "Com_util.h"
#include <STC89C5xRC.H>

void main()
{
u8 temp = 0x01;
    while (1)
    {
        P0 = ~temp;
        temp <<= 1;
        Com_util_DelayMs(100);
        if (temp == 0x00)
        {
            temp = 0x01;
        }
        
    }
    
}