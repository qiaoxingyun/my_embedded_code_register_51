#ifndef __KEY_STATE_H__
#define __KEY_STATE_H__

#include <STC8G.h>
#include "delay.h"
#include "Timer2.h"

#define LED1 P32
#define LED2 P33
#define LED3 P34

#define KEY_STATE P37	//状态切换按键

//枚举状态定义：LED状态以此改变以此往复
enum state
{
	state_1 = 0,	//全灭
	state_2,	//全亮
	state_3,	//闪烁
	state_4,	//流水灯
	state_5		//呼吸灯
};

extern enum state state_LED;

void Reset_Init(void);

void State_Init(void);

void LED_ALLOFF(void);

void LED_ALLON(void);

void LED_Blink(void);

void WaterfulLED(void);

void ScanLED_State(void);

#endif /* __KEY_STATE_H__ */
