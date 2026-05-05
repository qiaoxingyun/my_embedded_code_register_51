#include "key_state.h"
#include "Timer2.h"
#include "delay.h"

enum state state_LED = state_1;  	//初始全灭

void main()
{
	Reset_Init();
	State_Init();
	
	while(1)
	{
		ScanLED_State();
	}
}
