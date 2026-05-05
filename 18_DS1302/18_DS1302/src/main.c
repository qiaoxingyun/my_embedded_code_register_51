#include "Com_util.h"
#include "Int_DS1302.h"
#include "Int_DS18B20.h"
#include "Int_OLED.h"
#include <STDIO.H>

char *WEEK_NAME[7] = { 
    "Mon",
    "Tue",
    "Wed",
    "Thu",
    "Fri",
    "Sat",
    "Sun"};

void main()
{
    char tempe,str[17];
    Struct_date st_date;
    st_date.year = 25;
    st_date.month = 9;
    st_date.day = 5;
    st_date.day_of_week = 4;
    st_date.hour = 13;
    st_date.minute = 0;
    st_date.second = 0;
    
    Int_OLED_Init();
    Int_OLED_Clean();

    Int_DS1302_Init();
    Int_DS1302_SetDate(&st_date);
    while (1)
    {
        Int_DS1302_GetDate(&st_date);
        tempe = Int_DS18B20_Get_Temperature();
        sprintf(str,"20%02d/%02d/%02d %s",(int)st_date.year,(int)st_date.month,(int)st_date.day,WEEK_NAME[st_date.day_of_week - 1]);
        Int_OLED_ShowStr(0,0,str);
        sprintf(str,"%02d:%02d:%02d tmp:%d",(int)st_date.hour,(int)st_date.minute,(int)st_date.second,(int)tempe);
        Int_OLED_ShowStr(0,1,str);
        Com_util_DelayMs(500);
    }
    
}