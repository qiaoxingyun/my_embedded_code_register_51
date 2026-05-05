#include "led.h"
#include "key.h"
#include "ss1314.h"
#include "ds1302.h"
#include "STDIO.H"

extern DS1302_TimeDate_t st_data;
extern const char *WEEK_NAME[];
extern Select_item current_select_item;
extern idata bit add_flag;

void main(void)
{
    xdata uint8_t str[17];            //原内容显示的暂存数组
    st_data.year        = 26;
    st_data.month       = 3;
    st_data.day         = 18;
    st_data.week_day    = 3;
    st_data.hour        = 22;
    st_data.minute      = 40;
    st_data.second      = 00;
    

    //基本外设初始化
    Key_Init();
    LED_Init();
    OLED_Init();
    DS1302_Init();
    DS1302_SetDate(&st_data);

    LED_ON();
    OLED_Clear();

    while (1)
    {   
        DS1302_GetDate(&st_data);
        if (is_blink)
        {
            Scan_Int0_Blink(current_select_item,&st_data);
            is_blink = 0;
        }
        else
        {
            //OLED第一行：年月日
            sprintf(str, "20%02d / %02d / %02d",
                    (int)st_data.year,
                    (int)st_data.month,
                    (int)st_data.day);
            OLED_ShowStr(0,0,str);

            //OLED第二行：星期
            sprintf(str,"%s",WEEK_NAME[st_data.week_day - 1]);
            OLED_ShowStr(0,1,str);

            //OLED第三行：时分秒
            sprintf(str, "%02d:%02d:%02d",
                    (int)st_data.hour,
                    (int)st_data.minute,
                    (int)st_data.second);

            OLED_ShowStr(0,2,str);
        }
        Delay_ms(50);     
    }
    
    
}
