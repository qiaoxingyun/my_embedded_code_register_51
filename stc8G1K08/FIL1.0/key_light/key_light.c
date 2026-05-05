#include "key_light.h"

void Light_Init(void)
{
    //配置P10为双向口
    P1M0 &= 0xFE;
    P1M1 &= 0xFE;
    P1PU |= 0x01;	//使能内部上拉电阻，避免误触
    P1NCS &= 0xFE;	//使能端口施密特触发
}
