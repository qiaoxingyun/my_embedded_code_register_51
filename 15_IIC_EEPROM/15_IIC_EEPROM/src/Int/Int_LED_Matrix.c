#include "Int_LED_Matrix.h"
#include <STC89C5xRC.H>
#include "Dri_Timer0.h"

#define SER P10
#define SCK P12
#define RCK P11
#define LED_MATRIX_EN P35
#define LED_EN P34

static u8 s_buffer[8];

void Init_LEDMatrix_Refresh_Timer0();

void Init_LEDMatrix_Init()
{
    u8 i;
    LED_MATRIX_EN = 0; //打开点阵屏的开关使能引脚
    LED_EN = 0; //关闭公用P0端口的LED
    for ( i = 0; i < 8; i++)
    {
        s_buffer[i] = 0xFF; //给连接点阵屏的共阴极P0端口初始化
    }
    Dri_Timer0_Register_Callback(Init_LEDMatrix_Refresh_Timer0);

}

void Init_LEDMatrix_Refresh_Timer0()
{
    static u8 i = 0;
    P0 = 0xFF; //每行开始显示前清零，避免上一行的内容留存此行
    //1.设置显示的行
    if (i == 0)
        {
            SER = 1;
        }
        else
        {
            SER = 0;
        }
        SCK = 0;  //设置P12上升沿将要显示的行传入移位寄存器
        SCK = 1;

        RCK = 0; //设置P11上升沿将移位寄存器内容移入存储寄存器
        RCK = 1;
    //2.设置当前行显示内容
    P0 = s_buffer[i];
    //重置
    i++;
    if (i == 8)
    {
        i = 0;
    }
    
}

void Init_LEDMatrix_Shift(u8 pic)
{
    u8 i = 7;
    for ( i = 7; i >= 1; i--)
    {
        s_buffer[i] = s_buffer[i-1];
    }
    s_buffer[0] = pic;
}