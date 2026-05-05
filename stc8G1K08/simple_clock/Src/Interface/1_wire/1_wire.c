#include "1_wire.h"

void One_Wire_GPIOInit(void)
{
    //GPIO初始化：P37双向
    P3M0 &= 0x7F;
    P3M1 &= 0x7F;
    DQ = 1;

}

bit One_Wire_ResetSignal(void)
{
    bit result;
    //主设备发送复位脉冲
    DQ = 0;
    Delay_us(480);
    DQ = 1;
    //从设备回复复位脉冲
    Delay_us(60);
    result = DQ;
    Delay_us(420);
    return result;
}

void One_Wire_SendByte(uint8_t byte)
{
    uint8_t i;
    for ( i = 0; i < 8; i++)
    {
        DQ = 0;      //拉低总线
        Delay_us(2);
        //低位先发    
        DQ = byte & 0x01;   
        Delay_us(60);
        byte >>= 1;
        DQ = 1;     //释放总线
        Delay_us(2);    //总线恢复
    }
}

uint8_t One_Wire_ReceiveByte(void)
{
    uint8_t i,byte = 0;
    for ( i = 0; i < 8; i++) // 去掉开头多余的拉低/释放！
    {
        DQ = 0;     // 拉低总线（起始位）
        Delay_us(2);
        DQ = 1;     // 释放总线
        Delay_us(8); // 等待数据稳定（手册要求≥1us）
        byte >>= 1;
        if (DQ == 1)
        {
            byte |= 0x80;   
        }
        Delay_us(50); // 数据位保持
    }
    return byte;
}
