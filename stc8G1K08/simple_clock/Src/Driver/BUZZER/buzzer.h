#ifndef __BUZZER_H__
#define __BUZZER_H__

#include "com.h"

#define BUZZER P34

void Buzzer_Init(void);

void Buzzer_500Hz(void) reentrant;

#endif /* __BUZZER_H__ */