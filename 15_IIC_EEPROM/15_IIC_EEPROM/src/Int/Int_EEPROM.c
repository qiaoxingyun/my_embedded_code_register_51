#include "Int_EEPROM.h"
#include "Dri_IIC.h"
#include "Com_util.h"

#define DEV_ADDR_W 0xA0 //设备地址(写操作)
#define DEV_ADDR_R 0xA1 //设备地址(读操作)
#define PAGE_SIZE 16 //一页字节长度

/**
 * @brief 页写函数
 * @param addr 字节地址
 * @param bytes 页写的字节数组
 * @param len 页写的数组长度
 */
void Int_EEPROM_WritePage(u8 addr, u8 bytes[], u8 len)
{
    u8 i;
    Dri_IIC_Start(); //发送起始信号
    Dri_IIC_SendByte(DEV_ADDR_W); //发送设备地址(写操作)
    Dri_IIC_ReceiveAck(); //接收确认信号
    Dri_IIC_SendByte(addr); //发送字节地址
    Dri_IIC_ReceiveAck(); //接收确认信号
    //发送页写字节数据
    for ( i = 0; i < len; i++)
    {
        Dri_IIC_SendByte(bytes[i]);
        Dri_IIC_ReceiveAck();
    }
    Dri_IIC_Stop(); //发送结束信号
    Com_util_DelayMs(5); //给EEPROM写周期的时间
}

void Int_EEPROM_WriteBytes(u8 addr, u8 bytes[], u8 len)
{
    u8 page_remain = PAGE_SIZE - addr % PAGE_SIZE; //当前页可用字节长度
    if (len > page_remain)
    {
        //当前页空间不足
        //写满当前页
        Int_EEPROM_WritePage(addr,bytes,page_remain);
        //写剩余内容(使用递归：相同类型，向下软化)
        Int_EEPROM_WriteBytes(addr + page_remain,bytes + page_remain,len - page_remain);
    }
    else
    {
        //当前页空间充足
        Int_EEPROM_WritePage(addr,bytes,len);
    }
    
}

void Int_EEPROM_ReadBytes(u8 addr, u8 bytes[], u8 len)
{
    u8 i;
    Dri_IIC_Start();
    Dri_IIC_SendByte(DEV_ADDR_W);
    Dri_IIC_ReceiveAck();
    Dri_IIC_SendByte(addr);
    Dri_IIC_ReceiveAck();
    Dri_IIC_Start();
    Dri_IIC_SendByte(DEV_ADDR_R);
    Dri_IIC_ReceiveAck();
    for ( i = 0; i < len; i++)
    {
        bytes[i] = Dri_IIC_ReceiveByte();
        Dri_SendAck(i == len - 1 ? 1 : 0);
    }
    Dri_IIC_Stop();
    
}
