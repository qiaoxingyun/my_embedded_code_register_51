#include "Dri_Timer0.h"
#include <STC89C5xRC.H>
#include "Com_util.h"
#include <STDIO.H>

#define MAX_CALLBACK_COUNT 4

static Timer0_Callback s_callback[MAX_CALLBACK_COUNT];

void Dri_Timer0_Init()
{
    u8 i;
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
    //6.给函数指针数组初始化
    for ( i = 0; i < MAX_CALLBACK_COUNT; i++)
    {
        s_callback[i] = NULL;
    }
    
}

bit Dri_Timer0_Register_Callback(Timer0_Callback callback)
{
    u8 i;
    //1.确保不会重复注册
    for ( i = 0; i < MAX_CALLBACK_COUNT; i++)
    {
        if (s_callback[i] == callback)
        {
            return 1;
        }
    }
    //2.寻找坑位
    for ( i = 0; i < MAX_CALLBACK_COUNT; i++)
    {
        if (s_callback[i] == NULL)
        {
            s_callback[i] = callback;
            return 1;
        }
    }
    return 0;
}

bit Dri_Timer0_Deregister_Callback(Timer0_Callback callback)
{
    u8 i;
    for ( i = 0; i < MAX_CALLBACK_COUNT; i++)
    {
        if (s_callback[i] == callback)
        {
            s_callback[i] = NULL;
            return 1;
        }
        
    }
    return 0;
}

void Dri_Timer0_Handler() interrupt 1
{
    u8 i;
    //1.重新装载初始值
    TL0 = 64614;
    TH0 = 64614 >> 8;
    //2.轮询函数指针数组
    for ( i = 0; i < MAX_CALLBACK_COUNT; i++)
    {
        if (s_callback[i] != NULL)
        {
            s_callback[i]();
        }
        
    }
    

}
