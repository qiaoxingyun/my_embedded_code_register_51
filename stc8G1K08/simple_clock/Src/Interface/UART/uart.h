#ifndef __UART_H__
#define __UART_H__

/*串口打印调试：波特率：9600bps*/

#include <STC8G.h>
#include "com.h"

void Uart1_Init(void);

void Uart1_Transmit_String(uint8_t * str);

#endif /* __UART_H__ */