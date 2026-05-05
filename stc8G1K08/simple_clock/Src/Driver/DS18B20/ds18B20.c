#include "ds18B20.h"

bit flag = 1;   //初次复位脉冲的标志位：0-yes，1-no

void DS18B20_Init(void)
{
    One_Wire_GPIOInit();
    Uart1_Init();

    flag =  One_Wire_ResetSignal();  //检测设备

    if (flag == 0)
    {
        One_Wire_SendByte(0xCC);    // 跳过ROM命令
        One_Wire_SendByte(0x4E);    // 写阈值/分辨率
        One_Wire_SendByte(0x3C);    // 高温阈值60℃
        One_Wire_SendByte(0x00);    // 低温阈值0℃
        One_Wire_SendByte(0x1F);    // 9位分辨率
        Delay_us(10);
        Uart1_Transmit_String("DS18B20 init success!\n");
    }
    else
    {
        Uart1_Transmit_String("Ds18B20 not online\n");
    }
}

uint8_t DS18B20_GetTemperature(void)
{
    if (flag == 0)
    {
        uint8_t low_byte,high_byte;
        uint32_t timeout = 0;
        
        if (One_Wire_ResetSignal() == 0)    //检测设备在线
        {
            One_Wire_SendByte(0xCC);
            One_Wire_SendByte(0x44);    //测温命令
           
            Delay_ms(15);

            if (One_Wire_ResetSignal() == 0)
            {
                One_Wire_SendByte(0xCC);    //跳过ROM命令
                One_Wire_SendByte(0xBE);    //读取寄存器中数据
                low_byte = One_Wire_ReceiveByte();
                high_byte = One_Wire_ReceiveByte();
                return (low_byte >> 4) | (high_byte << 4);    //取温度的整数部分
            }
            else
            {
                Uart1_Transmit_String("DS18B20 not online after GetTemperature\n");
                return 0xFF;
            }
        }
        else
        {
            Uart1_Transmit_String("DS18B20 not online after Configuration Register \n");
            return 0xFF;
        }
    }
    else
    {
        Uart1_Transmit_String("Ds18B20 not online...\n");
        return 0xFF;
    }
}
