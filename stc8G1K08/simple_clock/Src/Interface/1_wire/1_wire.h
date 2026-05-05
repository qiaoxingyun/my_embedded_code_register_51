#ifndef __1_WIRE_H__
#define __1_WIRE_H__

#include "com.h"

#define DQ P37

void One_Wire_GPIOInit(void);

//返回复位脉冲：0-存在，1-不存在
bit One_Wire_ResetSignal(void);

void One_Wire_SendByte(uint8_t byte);

uint8_t One_Wire_ReceiveByte(void);

#endif /* __1_WIRE_H__ */