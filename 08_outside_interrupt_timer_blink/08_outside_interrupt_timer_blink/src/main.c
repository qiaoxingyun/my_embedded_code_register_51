#include "Com_util.h"
#include <STC89C5xRC.H>

#define LED1 P00

/**
 * @brief 设置定时器初始化
 */
void Into_Init()
{
    //1.总开关
    EA = 1;
    //2.定时器0开关
    ET0 = 1;
    //3.设置TMOD寄存器（低四位）：GATE:0  c/T：0 M1：0  M0:1 
    TMOD &= 0xF0;
    TMOD |= 0x01;
    //4.给寄存器设置初始值（TH0为高8位）
    TL0 = 64614;
    TH0 = 64614 >> 8;
    //5.启动定时器
    TR0 = 1;
}

/**
 * @breief 中断服务程序
 */
void Interrup_handler() interrupt 1
{
    static u16 count = 0;
    //1.重置初始值
    TL0 = 64614;
    TH0 = 64614 >> 8;
    //2.使LED1闪烁
    count++;
    if (count >= 500)
    {
        LED1 = ~LED1;
        count = 0;
    }
    
    
}


void main()
{
    Into_Init();
    while (1)
    {
        
    }
    
}