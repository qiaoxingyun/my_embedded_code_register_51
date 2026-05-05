#include "Com_util.h"
#include <INTRINS.H>
#include <STC89C5xRC.H>

/**
 * @brief 动态延时函数，支持传参控制毫秒数
 * @param ms 要延时的毫秒数（范围：1~255，受 u8 类型限制）
 */
void Com_util_DelayMs(u16 ms)  // 若需更大范围，可改为 u16 ms
{
    unsigned char data i, j;
    for (; ms > 0; ms--)  // 循环 ms 次，每次延时 1ms
    {
        _nop_();
        i = 2;
        j = 199;
        do
        {
            while (--j);
        } while (--i);
    }
}

void Com_Delay480us(void)	//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	i = 218;
	while (--i);
}

void Com_Delay60us(void)	//@11.0592MHz
{
	unsigned char data i;

	i = 25;
	while (--i);
}

void Com_Delay420us(void)	//@11.0592MHz
{
	unsigned char data i;

	i = 191;
	while (--i);
}

void Com_Delay10us(void)	//@11.0592MHz
{
	unsigned char data i;

	i = 2;
	while (--i);
}

void Com_Delay50us(void)	//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	i = 20;
	while (--i);
}

