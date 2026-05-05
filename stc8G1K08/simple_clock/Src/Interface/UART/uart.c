#include "uart.h"

void Uart1_Init(void)
{
    P_SW2 |= 0x80;  //使能外部RAM扩展特殊工能寄存器
    //GPIO工作模式：P30(RXD),P31(TXD)配置为推挽输出（TX需要强驱动）
    P3M0 |= 0x02;   // P31(TXD)推挽输出（02=0000 0010）
    P3M1 &= 0xFC;   // P30/P31清0，保持P30为输入，P31为推挽
    P_SW1 &= 0x3F;  //S1_S：00，串口1功能脚选择P30-RXD，P31-TXD
    P_SW2 &= 0x7F;  // 关闭扩展RAM，避免干扰串口

    PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器时钟1T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xB2;			//设置定时初始值
	TH1 = 0xB2;			//设置定时重载值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
}

void Uart1_Transmit_Char(uint8_t ch)
{
    SBUF = ch;
    while (!TI);
    TI = 0;
}

void Uart1_Transmit_String(uint8_t * str)
{
    while (*str != '\0')
    {
        Uart1_Transmit_Char(*str);
        str++;
    }
}

void Uart1_Isr(void) interrupt 4
{
	if (TI)				//检测串口1发送中断
	{
		TI = 0;			//清除串口1发送中断请求位
	}
	if (RI)				//检测串口1接收中断
	{
		RI = 0;			//清除串口1接收中断请求位
	}
}
