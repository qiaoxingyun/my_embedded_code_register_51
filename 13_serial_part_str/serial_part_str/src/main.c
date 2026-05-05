#include "Com_util.h"
#include "Dri_Uart.h"
#include <STC89C5xRC.H>
#include <STRING.H>
#include "Dri_Timer0.h"

void main()
{
    char str[16];
    Dri_Timer0_Init(); //先初始化定时器
    Dri_Uart_Init(); //后初始化串口
    while (1)
    {
        //循环检测(Dri_Uart_RecevieStr()函数是否有返回值，有则把值放赋给str
        if (Dri_Uart_RecevieStr(str))
        {
            //分支检测返回给str的内容，并向PC发送相关数据
            if (strcmp(str,"on") == 0)
            {
                P0 = 0x00;
                Dri_Uart_SendStr("OK:LED is on");
            }
            else if (strcmp(str,"off") == 0)
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