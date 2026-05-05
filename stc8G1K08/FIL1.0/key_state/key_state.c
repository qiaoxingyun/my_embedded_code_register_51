#include "key_state.h"

U8 Timer2_Running = 0;

void Reset_Init(void)
{
    P_SW2 |= 0x80;	//开启扩展寄存器访问
	RSTCFG |= 0x50;	//使能P54作为低压复位
	RSTCFG &= 0xFC;	//使能低压检测门槛电压为2v

    
}

void State_Init(void)
{
    //GPIO初始化
		//配置P32，P33，P34为推挽输出
		P3M0 |= 0x1C;
		P3M1 &= 0xE3;
		P3SR &= 0xE3;	//P34,P33,P32的端口电平转换速度加快
		P3DR &= 0xE3;	//增强P34,P33,P32的端口输出驱动能力
        //配置P37为双向口
		P3M0 &= 0x7F;
		P3M1 &= 0x7F;
		P3PU |= 0x80;	//使能内部上拉电阻，避免误触
		P3NCS &= 0x7F; 	//使能端口施密特触发

    //中断相关配置
        INTCLKO |= 0x20;	//允许INT3中断
        P3INTE |= 0x80;		//使能P37中断
        IE |= 0x80;	//开启总使能EA
}

//全灭
void LED_ALLOFF(void)
{
	LED1 = 1;
	LED2 = 1;
	LED3 = 1;
}
//全亮
void LED_ALLON(void)
{
	LED1 = 0;
	LED2 = 0;
	LED3 = 0;
}
//闪烁
void LED_Blink(void)
{
	LED_ALLOFF();
	Delay200ms();
	LED1 = 0;
	LED2 = 0;
	LED3 = 0;
	Delay200ms();
}
//流水灯
void WaterfulLED(void)
{
    // 单个LED按PWM亮度亮起，其余强制熄灭，流水节奏不变
    LED1 = 0; LED2=1; LED3=1;
    Delay200ms();
    LED2 = 0; LED1=1; LED3=1;
    Delay200ms();
    LED3 = 0; LED1=1; LED2=1;
    Delay200ms();
}


void ScanLED_State(void)
{
    switch (state_LED)
		{
		case state_1:
			if (Timer2_Running)
			{
				Timer2_Stop();
				Timer2_Running = 0;
			}
			LED_ALLOFF();
			break;
		case state_2:
			if (Timer2_Running)
			{
				Timer2_Stop();
				Timer2_Running = 0;
			}
			LED_ALLON(); 
			break;
		case state_3:
			if (Timer2_Running)
			{
				Timer2_Stop();
				Timer2_Running = 0;
			}
			LED_Blink();
			break;
		case state_4:
			if (Timer2_Running)
			{
				Timer2_Stop();
				Timer2_Running = 0;
			}
			WaterfulLED();
			break;
		case state_5:
			if (Timer2_Running == 0)
			{
				Timer2_Init();
				Timer2_Running = 1;
			}
			break;
		default:
			if (Timer2_Running)
			{
				Timer2_Stop();
				Timer2_Running = 0;
			}
			LED_ALLOFF();
			state_LED = state_1;
			break;
		}
}

void INT3_ISR(void) interrupt 11
{
	Delay10ms();	//跳过前沿抖动
	if (KEY_STATE == 0)	//再次检测到低电平
	{
		while (KEY_STATE == 0)	//低电平卡住直到抬起时再执行操作，跳过后沿抖动
		{	}
		state_LED ++;
		if (state_LED > state_5)
		{
			state_LED = 0;
		}
	}
	P3INTF &= 0x7F;	//清除P37端口中断标志
}
