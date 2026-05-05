#include "Com_util.h"
#include "Dri_Uart.h"
#include <STC89C5xRC.H>

void main()
{
    char c;
    Dri_Uart_Init();
    while (1)
    {
        //循环检测(Dri_Uart_RecevieChar()函数是否有返回值，有则把值放在c的地址上
        if (Dri_Uart_RecevieChar(&c))
        {
            //分支检测返回给c地址值的内容，并向PC发送相关数据
            if (c == 'A')
            {
                P0 = 0x00;
                Dri_Uart_SendStr("OK:LED is on");
            }
            else if (c == 'B')
            {
                P0 = 0xFF;
                Dri_Uart_SendStr("OK:LED is off");
            }
            else
            {
                Dri_Uart_SendStr("Error command");
            }
        }
        
    }
    
}