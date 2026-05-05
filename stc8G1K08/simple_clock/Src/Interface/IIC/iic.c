#include "iic.h"

void IIC_Init(void)
{
    P_SW2 |= 0x80;
    //配置P16，P17为开漏模式
    P1M0 |= 0xC0;
    P1M1 |= 0xC0;
    //默认高电平，空闲状态
    SCL = 1;
    SDA = 1;
    Delay_ms(1);
}

void IIC_Start(void)
{
    SCL = 1;
    SDA = 1;
    Delay_us(5);
    SDA = 0;
    Delay_us(5);
    SCL = 0;
    Delay_us(5);
}

void IIC_Stop(void)
{
    SDA = 0;
    SCL = 0;
    Delay_us(5);
    SCL = 1;
    Delay_us(5);
    SDA = 1;
    Delay_us(5);
}

void IIC_SendByte(uint8_t byte)
{
    
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        SCL = 0;
        Delay_us(5);
        // 精准取最高位（bit7→bit0），替换你原有的移位逻辑
        SDA = (byte >> (7 - i)) & 0x01; 
        Delay_us(5);  // 确保SDA电平稳定后，再拉高SCL采样
        SCL = 1;      
        Delay_us(5);
        SCL = 0;
        Delay_us(5);
    }
    Delay_us(10);
}

uint8_t IIC_ReceiveByte(void)
{
    uint8_t i, byte = 0;
    SCL = 0;
    SDA = 1;
    Delay_us(5);
    for ( i = 0; i < 8; i++)
    {
        SCL = 1;
        Delay_us(5);
        byte = (byte << 1) | SDA;
        SCL = 0;
        Delay_us(5);
    }
    return byte;
}

void IIC_SendAck(bit ack)
{
    SCL = 0;
    Delay_us(5);
    SDA = ack;
    SCL = 1;
    Delay_us(5);
    SCL = 0;
    SDA = 1;
    Delay_us(5);
}

bit IIC_ReceiveAck(void)
{
    bit ack;
    SCL = 0;
    SDA = 1;
    Delay_us(5);
    SCL = 1;
    Delay_us(5);
    ack = SDA;
    SCL = 0;
    Delay_us(5);
    return ack;
}
