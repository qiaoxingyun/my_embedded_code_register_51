#ifndef __DRI_UART_H__
#define __DRI_UART_H__

void Dri_Uart_Init();

void Dri_Uart_SendChar(char c);

void Dri_Uart_SendStr(char *str);

bit Dri_Uart_RecevieChar(char *c);
#endif /*__DRI_UART_H__*/