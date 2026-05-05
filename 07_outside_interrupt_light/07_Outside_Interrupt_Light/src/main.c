#include "Com_util.h"
#include <STC89C5xRC.H>

#define LED1 P00

void Into_Init()
{
    //1.中断总开关
    EA = 1;
    //2.外部中断0开关
    EX0 = 1;
    //3.选择外部中断0的触发方式（0：低电平触发 1：下降沿触发）
    IT0 = 1;
}

void INTerrupt_Handler() interrupt 0
{
    Com_util_DelayMs(10);
    if (P32 == 0)
    {
        LED1 = ~LED1;
    }
    
}

void main()
{
    Into_Init();
    while (1)
    {
        
    }
    
}