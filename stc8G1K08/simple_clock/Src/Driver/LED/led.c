#include "led.h"

void LED_Init(void)
{
    P_SW2 |= 0x80;
    //≈‰÷√GPIO£∫P35Œ™Õ∆ÕÏ ‰≥ˆ
    P3M0 |= 0x20;
    P3M1 &= 0xDF;
}

void LED_ON(void)
{
    LED = 0;
}

void LED_OFF(void)
{
    LED = 1;
}

void LED_BLink_ms(uint8_t ms)
{
    LED = 1;
    Delay_ms(ms);
    LED = 0;
    Delay_ms(ms);
}
