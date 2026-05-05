#include "com.h"

void Delay_us(uint16_t time)
{
    uint16_t i;
    uint8_t j;
    for (i = 0; i < time; i++)
    {
        for (j = 0; j < 24; j++)
        {
            _nop_();
        }
    }
}

void Delay_ms(uint16_t time)
{
    uint16_t i,j;
    uint8_t k;
    for ( i = 0; i < time; i++)
    {
       for ( j = 0; j < 1000; j++)
       {
            for ( k = 0; k < 24; k++)
            {
                _nop_();
            }
        }
    }
}
