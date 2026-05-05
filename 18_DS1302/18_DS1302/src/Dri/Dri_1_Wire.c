#include "Dri_1_Wire.h"
#include <STC89C5xRC.H>
#define DQ P44

bit Dri_1Wire_Init()
{
    bit result;
    //发送复位脉冲
    DQ = 0;
    Com_Delay480us();
    DQ = 1; //主设备释放DQ
    Com_Delay60us();
    result = ~DQ; //获取从设备返回的存在脉冲
    Com_Delay420us();
    return result;
}

void Dri_1Wire_WriteByte(u8 byte)
{
    u8 i;
    for ( i = 0; i < 8; i++)
    {
        DQ = 0;
        DQ = byte & 0x01;
        byte >>= 1;
        Com_Delay60us();
        DQ = 1;
    }
    
}

u8 Dri_1Wire_ReadByte()
{
    u8 i,byte = 0x00;
    for ( i = 0; i < 8; i++)
    {
        DQ = 0;
        DQ = 1;
        Com_Delay10us();
        byte >>= 1;
        if (DQ == 1)
        {
            byte |= 0x80;
        }
        Com_Delay50us();
    }
    return byte;
}
