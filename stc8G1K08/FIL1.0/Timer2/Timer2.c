#include "Timer2.h"

U8 duty = 0;
//随中断不断增加的值，与占空比做对比
U8 count = 0;
//占空比变化的标志位
U8 flag = 0;
//占空比延时计数器
U16 duty_delay = 0;

void Timer2_Init(void)
{
    //GPIO初始化
		//配置P32，P33，P34为推挽输出
		P3M0 |= 0x1C;
		P3M1 &= 0xE3;
		P3SR &= 0xE3;	//P34,P33,P32的端口电平转换速度加快
		P3DR &= 0xE3;	//增强P34,P33,P32的端口输出驱动能力

    AUXR &= 0xEF;   //B4 T2R = 0: 先将定时器2停止计数，将自动重装载的值写入影子寄存器，溢出后自动装载
    AUXR &= 0xF7;   //B3 T2_C/T = 0:定时器2用作定时器对系统时钟进行计数
    AUXR |= 0x04;   //B2 T2x12 = 1:定时器2为1T工作模式，系统时钟不分频
    TM2PS = 23;     //定时器2的时钟 = 系统时钟做（23 + 1）做24分频得到1Mhz
    //T2时钟周期 = 65536 - [T2H,T2L]/SYSCLK/(TM2PS + 1),得到100us的周期
    T2L = 0x9C;     //T2的自动装载值低8位
    T2H = 0xFF;     //T2的自定装载值高8位
    INTCLKO &= 0xFB;    //B2 T2CLKO = 0:关闭定时器2的时钟输出
    IE2 |= 0x04;    //B2 ET2 = 1:允许T2中断
    EA = 1;     //开启总中断
    AUXR |= 0x10;   //B4 T2R = 1: 定时器2开始计数
}

void Timer2_Stop(void)
{
    AUXR &= 0xEF;   // 停止定时器2计数
    IE2 &= 0xFB;    // 关闭定时器2中断
    duty = 0;    //重置占空比，避免切换状态时LED异常
    count = 0;
}

//Timer2中断溢出函数：100 * 1us一次溢出
void TM2_Isr(void) interrupt 12
{   
    count ++;
    //当duty大于count，LED点亮
  if(duty > count)
    {
        LED1 = 0;
        LED2 = 0;
        LED3 = 0;
    }
    else
    {
        LED1 = 1;
        LED2 = 1;
        LED3 = 1;
    }
    if (count >= 100)
    {
        count = 0;
    }

    duty_delay++;
    if (duty_delay >= 100)
    {
        duty_delay = 0;
        if (flag == 0)
        {
           duty += 2;
           if (duty >= 100)
           {
                flag = 1;
           } 
        }
        else
        {
            duty -= 2;
            if (duty <= 0)
            {
                flag = 0;
            }
            
        }
    }
} 
