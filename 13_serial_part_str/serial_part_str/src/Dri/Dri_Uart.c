#include "Dri_Uart.h"
#include <STC89C5xRC.H>
#include "Com_util.h"
#include "Dri_Timer0.h"

static bit s_is_send = 0; //0：未在发送，1：正在发送
static char s_buffer[16]; //临时存储收到的命令
static u8 s_idle_count = 0; //空闲检测初始值
static u8 s_index  =  0; //将数据放入s_buffer数组的索引
static bit s_is_complete = 0;  //数据接收完毕与否标志位

/**
 * @brief 计时：每收到一个字符将s_idle_count+1，当超过10时说明字符串已经接收完毕
 */
void Dri_Uart_Timer0Callback()
{
    s_idle_count++;
    if (s_index > 0 && s_idle_count >= 10)
    {
        //数据接收完毕
        s_is_complete = 1;
    }
    
}

void Dri_Uart_Init()
{
    //1.设置串口工作模式(8位Uart可变波特率)
    SM0 = 0;
    SM1 = 1;

    //2.1设置波特率
    PCON &= 0x7F;
    //2.2定时器1工作模式(8位自动重装载，GATE=0,C/T=0,M1=1,M0=0)
    TMOD &= 0x0F;
    TMOD |= 0x20;
    //2.3初始值(253)
    TL1 = 0xFD;
    TH1 = 0xFD;
    //2.4启动定时器
    TR1 = 1;

    //3.接收数据相关配置(REN使能开关，SM2=0不检测帧数据停止位)
    REN = 1;
    SM2 = 0;

    //4.串口中断相关配置(EA总开关,ES串口中断分开关,RI&TI串口中断(发送和接收)标志位复位)
    EA = 1;
    ES = 1;
    RI = 0;
    TI = 0;

    //5.注册空闲检测函数
    Dri_Timer0_Register_Callback(Dri_Uart_Timer0Callback);

}

/**
 * @brief 当发送第一个字符时，标志s_is_send初始值为0不进人循环，并将其置为1，
 * 此时当没发送完时会进入循环，当发送完第一个字符时，标志s_is_send复0，开始
 * 发送第二个字符，并将s_is_send置1，以此往复
 * @param c 单个字符
 */
void Dri_Uart_SendChar(char c)
{
    while (s_is_send == 1);
    s_is_send = 1;
    SBUF = c;
}

bit Dri_Uart_RecevieStr(char *str)
{
    if (s_is_complete == 1)
    {
        u8 i;
        for ( i = 0; i < s_index; i++)
        {
            str[i] = s_buffer[i];
        }
        str[i] = '\0'; //利用strcmp遇0即停止比较的特性，覆盖前一次命令
        s_is_complete = 0;
        s_index = 0;
        return 1; 
    }
    return 0;
}

/**
 * @brief 将一个字符串分成若干字符使用Dri_Uart_SendChar()循环发送直至遇到'0'字符串结束
 * @param str 字符串
 */ 
void Dri_Uart_SendStr(char *str)
{
    while (*str != '\0')
    {
        Dri_Uart_SendChar(*str);
        str++;
    }
    
}

void Dri_Uart_Handler() interrupt 4
{
    //接收数据相关函数
    if (RI)
    {
        s_buffer[s_index++] = SBUF; //将接收到的数据按索引赋给s_buffer数组
        s_idle_count = 0;
        RI = 0; //给接受数据串口标志位复位
    }
    //发送数据相关函数
    if (TI)
    {
        s_is_send = 0; //使Dri_Uart_SendChar()函数继续发送字符串内的若干字符
        TI = 0; //给发送数据串口标志位复位
    } 
}