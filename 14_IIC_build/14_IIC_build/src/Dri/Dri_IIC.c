#include "Dri_IIC.h"
#include <STC89C5xRC.H>

#define SCL P17
#define SDA P16

/**
 * @brief 发送起始信号
 */
void Dri_IIC_Start()
{
    //确保数据线和时钟信号线处于空闲状态
    SCL = 1; 
    SDA = 1;
    //发送起始信号
    SDA = 0;
    //拉低SCL给SDA时间准备数据
    SCL = 0;
}

/**
 * @brief 发送一个字节(从设备地址+读写表示/数据)
 * @param byte 发送的字节数据
 */
void Dri_IIC_SendByte(u8 byte)
{
    u8 i;
    for ( i = 0; i < 8; i++)
    {
        SDA = (byte & (0x80 >> i)) == 0 ? 0 : 1;
        SCL = 1;
        SCL = 0;
    }
}

/**
 * @brief 接收一位确认信号
 * @return 0：成功接收，1：未成功接收
 */
bit Dri_IIC_ReceiveAck()
{
    bit ack;
    SDA = 1; //主设备释放SDA让从设备控制SDA
    //读取SDA
    SCL = 1;
    ack = SDA;
    SCL = 0;

    return ack;
}

/**
 * @brief 接收一个字节数据
 * @return 字节数据
 */
u8 Dri_IIC_ReceiveByte()
{
    u8 i,byte = 0;
    SDA = 1; //主设备释放SDA让从设备控制SDA

    for ( i = 0; i < 8; i++)
    {
        SCL = 1;
        byte = (byte << 1) | SDA;
        SCL = 0;
    }
    
    return byte;
}

/**
 * @brief 发送一位确认信号
 * @param ack 0：成功接收，1：未成功接收
 */
void Dri_SendAck(bit ack)
{
    SDA = ack;
    SCL = 1;
    SCL = 0;
}

/**
 * @brief 发送停止信号
 */
void Dri_IIC_Stop()
{
    SDA = 0;
    SCL = 1;
    SDA = 1;
}
