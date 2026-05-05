#include <STC89C5xRC.H>
#include "com_Util.h"
#include <INTRINS.h>

#define DIG P36
#define LED P34

static u8 s_num[8]; //定义显存数组
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

void Delay1ms(void)	//@11.0592MHz
{
	unsigned char data i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}


/**
 * @brief 数码管任意位置显示一位数字
 * @param position 位选：显示的位置
 * @param num_code 段选：显示的内容
 */
void Digital_Tube_DisplaySingle(u8 position,u8 num_code)
{
    P0 = 0x00;
    //1.位选：
    position <<= 3;
    P1 &= 0xC7;
    P1 |= position;
    //2.段选：
    P0 = num_code;

}

/**
 * @brief 显存数组初始化，并填入要显示的内容
 */
void Digital_Tube_DisplayNum(u32 num)
{
    u8 i;
	for ( i = 0; i < 8; i++)
	{
		s_num[i] = 0x00;
	}
    i = 7;
    while (num > 0)
    {
        s_num[i--] = s_codes[num % 10];
        num /= 10;
    }
}

void Digital_Tube_Refresh()
{
    u8 j;
    for ( j = 0; j < 8; j++)
    {
        Digital_Tube_DisplaySingle(j,s_num[j]);
        Delay1ms();
    }
    
}

void main()
{
    DIG = 0;
    LED = 0;
    Digital_Tube_DisplayNum(12345670);
    while (1)
    {  
        Digital_Tube_Refresh();
    }
}