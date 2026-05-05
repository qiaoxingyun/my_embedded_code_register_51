#include "Int_DS18B20.h"
#include "Dri_1_Wire.h"

char Int_DS18B20_Get_Temperature()
{
    u8 ls_byte,ms_byte;

    //初始还
    Dri_1Wire_Init();
    //发送ROM命令
    Dri_1Wire_WriteByte(0xCC);
    //发送测温命令
    Dri_1Wire_WriteByte(0x44);

    //初始还
    Dri_1Wire_Init();
    //发送ROM命令
    Dri_1Wire_WriteByte(0xCC);
    //发送读取温度命令
    Dri_1Wire_WriteByte(0xBE);

    ls_byte = Dri_1Wire_ReadByte();
    ms_byte = Dri_1Wire_ReadByte();

    return (ls_byte >>= 4) | (ms_byte <<= 4);
}