#include "ds1302.h"

void DS1302_Init(void)
{
    //配置GPIO：
        //SCLK-P11，IO-P10：双向口
        P1M0 &= 0xFC;
        P1M1 &= 0xFC;
        //CE-P36:推挽输出
        P3M1 &= 0xBF;
        P3M0 |= 0x40;
    SCLK = 0;
    IO = 0;
    CE = 0;
}
static void DS1302_WriteByte(uint8_t byte)
{
    uint8_t i;
    for (i = 0; i < 8; i++) {
        IO   = byte & 0x01;
        Delay_us(2);
        SCLK = 1;
        Delay_us(2);
        SCLK = 0;
        byte >>= 1;
    }
}

static uint8_t DS1302_ReadByte()
{
    uint8_t i, byte = 0;
    for (i = 0; i < 8; i++) {
        byte >>= 1;
        Delay_us(2);
        if (IO == 1) {
            byte = byte | 0x80;
        }
        Delay_us(2);
        SCLK = 1;
        Delay_us(2);
        SCLK = 0; 
    }
    return byte;
}

static void DS1302_SetRegister(uint8_t addr, uint8_t byte)
{
    CE = 1;
    Delay_us(2);
    DS1302_WriteByte(addr);
    DS1302_WriteByte(byte);
    Delay_us(2);
    CE = 0;
    Delay_us(2);
}

static uint8_t DS1302_GetRegister(uint8_t addr)
{
    uint8_t byte;
    CE = 1;
    Delay_us(2);
    DS1302_WriteByte(addr | 1);
    Delay_us(2);
    byte = DS1302_ReadByte();
    Delay_us(2);
    CE   = 0;
    Delay_us(2);
    return byte;
}

void DS1302_SetDate(DS1302_TimeDate_t *p_st_date)
{
    uint8_t temp;

    // 关闭写保护
    DS1302_SetRegister(DS1302_WP,0x00);
    Delay_us(10);

    // 设置秒
    temp = (p_st_date->second % 10) | ((p_st_date->second / 10) << 4);
    temp &= 0x7F;
    DS1302_SetRegister(DS1302_SECOND, temp);

    // 设置分钟
    temp = (p_st_date->minute % 10) | ((p_st_date->minute / 10) << 4);
    DS1302_SetRegister(DS1302_MINUTE, temp);

    // 设置小时
    temp = (p_st_date->hour % 10) | ((p_st_date->hour / 10) << 4);
    temp &= 0x3F;
    DS1302_SetRegister(DS1302_HOUR, temp);

    // 设置日
    temp = (p_st_date->day % 10) | ((p_st_date->day / 10) << 4);
    DS1302_SetRegister(DS1302_DAY, temp);

    // 设置月
    temp = (p_st_date->month % 10) | ((p_st_date->month / 10) << 4);
    DS1302_SetRegister(DS1302_MONTH, temp);

    // 设置年
    temp = (p_st_date->year % 10) | ((p_st_date->year / 10) << 4);
    DS1302_SetRegister(DS1302_YEAR, temp);

    // 设置星期
    DS1302_SetRegister(DS1302_WEEK_DAY, p_st_date->week_day % 10);

    // 开启写保护
    DS1302_SetRegister(DS1302_WP, 0x80);
    Delay_us(10);
}

void DS1302_GetDate(DS1302_TimeDate_t *p_st_date)
{
    uint8_t temp;
    // 获取秒
    temp              = DS1302_GetRegister(DS1302_SECOND);
    p_st_date->second = (temp >> 4) * 10 + (temp & 0x0F);

    temp              = DS1302_GetRegister(DS1302_MINUTE);
    p_st_date->minute = (temp >> 4) * 10 + (temp & 0x0F);

    temp            = DS1302_GetRegister(DS1302_HOUR);
    p_st_date->hour = (temp >> 4) * 10 + (temp & 0x0F);

    temp           = DS1302_GetRegister(DS1302_DAY);
    p_st_date->day = (temp >> 4) * 10 + (temp & 0x0F);

    temp             = DS1302_GetRegister(DS1302_MONTH);
    p_st_date->month = (temp >> 4) * 10 + (temp & 0x0F);

    temp            = DS1302_GetRegister(DS1302_YEAR);
    p_st_date->year = (temp >> 4) * 10 + (temp & 0x0F);

    temp                   = DS1302_GetRegister(DS1302_WEEK_DAY);
    p_st_date->week_day = temp &= 0x07;
}

