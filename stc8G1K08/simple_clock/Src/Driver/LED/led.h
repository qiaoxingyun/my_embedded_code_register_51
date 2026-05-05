#ifndef __LED_H__
#define __LED_H__

#include "com.h"

#define LED P35

void LED_Init(void);

void LED_ON(void);
void LED_OFF(void);

void LED_BLink_ms(uint8_t ms);

#endif /* __LED_H__ */