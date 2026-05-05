#include "buzzer.h"

void Buzzer_Init(void)
{
    //P34推挽输出
    P3M0 |= 0x10;
    P3M1 &= 0xEF;
    //初始化
    BUZZER = 0;
}

void Buzzer_500Hz(void) reentrant
{
    uint8_t i = 30;
    while (i)
    {
        BUZZER = ~BUZZER;
        Delay_ms(1);
        --i;
    }
    BUZZER = 0;
}
