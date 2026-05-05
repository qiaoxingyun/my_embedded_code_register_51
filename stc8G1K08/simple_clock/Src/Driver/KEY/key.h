#ifndef __KEY_H__
#define __KEY_H__

#include "com.h"
#include "buzzer.h"
#include "ss1314.h"
#include "ds1302.h"
#include "STDIO.H"
#include "STRING.H"
#include "uart.h"

#define EXCHANGE_INT0 P32
#define NUM_ADD_INT1 P33
#define RST P54

//定义切换的枚举项，保持不变，每个元素与OLED显示的信息元素的位置绑定
typedef enum
{
    SELECT_YEAR,    //年：20xx，4位
    SELECT_MONTH,   //月：xx,2位
    SELECT_DAY,     //日：xx,2位
    SELECT_WEEK,    //星期：不固定，根据字符串
    SELECT_HOUR,    //时：xx,2位
    SELECT_MINUTE   //分：xx,2位
} Select_item;

extern DS1302_TimeDate_t st_data;
extern const char *WEEK_NAME[];
extern bit is_blink;
extern Select_item current_select_item;
extern idata bit add_flag;

void Key_Init(void);

void Scan_Int0_Blink(Select_item si,DS1302_TimeDate_t *st);

#endif /* __KEY_H__ */