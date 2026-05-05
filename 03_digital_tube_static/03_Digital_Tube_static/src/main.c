#include "Com_util.h"
#include <STC89C5xRC.H>

#define DIG P36
#define LED P34

static u8 s_codes[10] = {
     0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

/**
 * @brief 数码管任意位置显示一位数字
 * @param position 位选：显示的位置
 * @param num_code 段选：显示的内容
 */
void Digital_Tube_DisplaySingle(u8 position,u8 num_code)
{
    u8 i = 0;
    //1.位选：
    i = position - 1;
    i <<= 3;
    P1 &= 0xC7;
    P1 |= i;
    //2.段选：
    P0 = s_codes[num_code];

}

void main()
{
    DIG = 0;
    LED = 0;
    Digital_Tube_DisplaySingle(8,7);
    while (1)
    {  
    }
    
}