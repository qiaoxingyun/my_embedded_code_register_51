#include "key.h"

Select_item current_select_item = SELECT_YEAR;      //当前按下时的状态
bit Int0_is_first_press_dowm = 0;                   //是否第一次按下：0-是，1-否
DS1302_TimeDate_t st_data;                          //时间结构体变量
bit is_blink = 0;                                   //是否正在闪烁标志位：0-未在闪烁，1-在闪烁
idata bit add_flag = 0;                             //增加标志位：0-不增加，1-增加


const char *WEEK_NAME[] = {
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};


void Key_Init(void)
{
    P_SW2 |= 0x80;	//开启扩展寄存器访问
	RSTCFG |= 0x50;	//使能P54作为低压复位
	RSTCFG &= 0xFC;	//使能低压检测门槛电压为2v
    P5PU |= 0x10;   //使能内部上拉电阻
    P5NCS |= 0x10;  //使能端口施密特触发
    //P32,P33:外部中断0和1，双向口
    P3M0 &= 0xF3;
    P3M1 &= 0xF3;
    P3PU |= 0x0C;   //使能内部上拉电阻
    P3NCS &= 0xF3;  //使能端口施密特
    //允许INt0和INt1中断
    EX0 = 1;
    EX1 = 1;
    P3INTE |= 0x0C; //使能P32,P33端口中断
    EA = 1;     //使能总中断

    Buzzer_Init();  //将蜂鸣器初始化
}

void Scan_Int0_Blink(Select_item si,DS1302_TimeDate_t *st)
{
    idata uint8_t i;
    idata char str[17] = {0};
    idata char week_lens[10] = {0};

    if (add_flag)
    {
        switch (si)
        {
        case SELECT_YEAR:
            st->year += 1;
            break;
        case SELECT_MONTH:
            st->month += 1;
            if (st->month == 13)
            {
                st->month = 1;
                st->year += 1;
            }
            break;
        case SELECT_DAY:
            st->day += 1;
            if (st->day ==32)
            {
                st->day = 1;
                st->month += 1;
            } 
            break;
        case SELECT_WEEK:
            st->week_day += 1;
            if (st->week_day == 8)
            {
                st->week_day = 1;
                st->day += 1;
            }
            break;
        case SELECT_HOUR:
            st->hour += 1;
            if (st->hour == 24)
            {
                st->hour = 0;
                st->day += 1;
                st->week_day += 1;
            }
            break;
        case SELECT_MINUTE:
            st->minute += 1;
            if (st->minute == 60)
            {
                st->minute = 0;
                st->hour += 1;
            }
            break;
        default:
            break;
        }

        add_flag = 0;
    }

    DS1302_SetDate(st);

    switch (si)
    {
    case SELECT_YEAR:
        sprintf(str,"20%02d",(int)st->year);
        for ( i = 0; i < 4; i++)
        {
            OLED_ShowStr(0,0,"####");
            Delay_ms(50);
            OLED_ShowStr(0,0,str);
            Delay_ms(50);
        }
        break;
    case SELECT_MONTH:
        sprintf(str,"%02d",(int)st->month);
        str[2] = '\0';
        for ( i = 0; i < 4; i++)
        {
            OLED_ShowStr(7,0,"##");
            Delay_ms(50);
            OLED_ShowStr(7,0,str);
            Delay_ms(50);
        }
        break;
    case SELECT_DAY:
        sprintf(str,"%02d",(int)st->day);
        str[2] = '\0';
        for ( i = 0; i < 4; i++)
        {
            OLED_ShowStr(12,0,"##");
            Delay_ms(50);
            OLED_ShowStr(12,0,str);
            Delay_ms(50);
        }
        break;
    case SELECT_WEEK:
        memset(week_lens, 0, sizeof(week_lens));
        sprintf(str,"%s",WEEK_NAME[st->week_day - 1]);
        for ( i = 0; i < strlen(str); i++)
        {
            week_lens[i] = '#';
        }
        week_lens[i] = '\0';
        for ( i = 0; i < 4; i++)
        {
            OLED_ShowStr(0,1,week_lens);
            Delay_ms(50);
            OLED_ShowStr(0,1,str);
            Delay_ms(50);
        }
        break;
    case SELECT_HOUR:
        sprintf(str,"%02d",(int)st->hour);
        str[2] = '\0';
        for ( i = 0; i < 4; i++)
        {
            OLED_ShowStr(0,2,"##");
            Delay_ms(50);
            OLED_ShowStr(0,2,str);
            Delay_ms(50);
        }
        break;
    case SELECT_MINUTE:
        sprintf(str,"%02d",(int)st->minute);
        str[2] = '\0';
        for ( i = 0; i < 4; i++)
        {
            OLED_ShowStr(3,2,"##");
            Delay_ms(50);
            OLED_ShowStr(3,2,str);
            Delay_ms(50);
        }
        break;
    default:
        break;
    }
}

//切换显示位置
void INT0_Isr() interrupt 0
{
    Delay_ms(10);
    if (EXCHANGE_INT0 == 0)
    {
        while (EXCHANGE_INT0 == 0);
        Buzzer_500Hz();
        //按键切换枚举状态：
        if (Int0_is_first_press_dowm == 0)
        {
            Int0_is_first_press_dowm = 1;   //清除第一次按下标志位
        }
        else
        {
            current_select_item = (Select_item)((current_select_item + 1) % 6);
        }
        is_blink = 1;

    }
    P3INTF &= 0xFB;     //清除P32端口中断标志位
}

//增加数值
void INT1_Isr() interrupt 2
{
    Delay_ms(10);
    if (NUM_ADD_INT1 == 0)
    {
        while (NUM_ADD_INT1 == 0);
        Buzzer_500Hz();
        add_flag = 1;   //置位增加标志位
    }
    P3INTF &= 0xF7;    //清除P33端口中断标志位
}
