#ifndef __IIC_H__
#define __IIC_H__

/*100kbps的IIC：SCL高低电平持续时间 >= 5us*/

#include <com.h>

#define SCL P17
#define SDA P16

void IIC_Init(void);

void IIC_Start(void);
void IIC_Stop(void);

void IIC_SendByte(uint8_t byte);
uint8_t IIC_ReceiveByte(void);

void IIC_SendAck(bit ack);
bit IIC_ReceiveAck(void);

#endif /* __IIC_H__ */