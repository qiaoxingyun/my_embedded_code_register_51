#ifndef __DS1302_H__
#define __DS1302_H__

/*发送及接收数据时序；命令字节（指定地址和读写标识）-数据字节 
    低位先发，每次写入都要关闭写保护寄存器WP-BIt7：0 允许写入，1 禁止介入*/

#include "com.h"
#include <STDDEF.H>

#define SCLK P11
#define IO P10
#define CE P36

//命令字节地址:LSB-0（写），LSB-1（读）
#define DS1302_SECOND      0x80
#define DS1302_MINUTE      0x82
#define DS1302_HOUR        0x84
#define DS1302_DAY         0x86
#define DS1302_MONTH       0x88
#define DS1302_WEEK_DAY    0x8A
#define DS1302_YEAR        0x8C
#define DS1302_WP          0x8E
 

typedef struct ds1302
{
    uint8_t week_day;
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} DS1302_TimeDate_t;


void DS1302_Init(void);

void DS1302_SetDate(DS1302_TimeDate_t * P_dt_date);

void DS1302_GetDate(DS1302_TimeDate_t * P_dt_date);


#endif /* __DS1302_H__ */