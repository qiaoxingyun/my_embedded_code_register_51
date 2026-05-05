#include "Dri_DigitalTube_Matrix.h"
#include "Com_util.h"
#include <STC89C5xRC.H>

//数字0~9的编码
static u8 codes[10]={
	0x3F,//0
	0x06,//1
	0x5B,//2
	0x4F,//3
	0x66,//4
	0x6D,//5
	0x7D,//6
	0x07,//7
	0x7F,//8
	0x6F,//9
};

//显存数组
u8 buffer[8];

void Dri_DigitalTube_DisplaySingle(u8 position,u8 num_code)
{
	P0 = 0x00;
	//位选：P15,P14,P13
	position <<= 3; //将十进制对应的位选转换二进制其中低三位左移与P1的P15,P14,P13相对应
	P1 &= 0xc7; //将P1八位的中间三位P15,P14,P13转成0
	P1 |= position; //将左移后的低三位与对应的P15,P14,P13进行覆盖
	//段选：P0
	P0 = num_code;
}

void Dri_DigitalTube_Displaynum(u32 num)
{
	u8 i;
	for ( i = 0; i < 8; i++)
	{
		buffer[i] = 0x00;
	}
    	i = 7;
	while (num > 0)
	{
		buffer[i--] = codes[num % 10];
		num /= 10;
	}
}

void Dri_DigitalTube_Refresh()
{
	u8 i;
	for ( i = 0; i < 8; i++)
	{
		Dri_DigitalTube_DisplaySingle(i,buffer[i]);
		Com_util_DelayMs(1);
	}
	
}