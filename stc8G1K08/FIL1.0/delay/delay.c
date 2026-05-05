#include "delay.h"

//10毫秒延时
void Delay10ms(void)	//@24.000MHz
{
	unsigned char data i, j, k;

	i = 2;
	j = 56;
	k = 172;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
//200毫秒延时
void Delay200ms(void)	//@24.000MHz
{
	unsigned char data i, j, k;

	_nop_();
	_nop_();
	i = 25;
	j = 90;
	k = 176;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
