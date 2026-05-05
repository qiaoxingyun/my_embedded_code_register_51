#ifndef __DS18B20_H__
#define __DS18B20_H__

#include "1_wire.h"
#include "uart.h"

//DS18B20初始化，高低温阈值及分辨率设置
void DS18B20_Init(void);

//获取当前温度
uint8_t DS18B20_GetTemperature(void);

#endif /* __DS18B20_H__ */