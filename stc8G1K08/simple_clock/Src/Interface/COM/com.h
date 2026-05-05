#ifndef __COM_H__
#define __COM_H__

#include <INTRINS.H>
#include <STC8G.h>

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;

//usÑÓ³Ùº¯Êı
void Delay_us(uint16_t time);
//msÑÓ³Ùº¯Êı
void Delay_ms(uint16_t time);


#endif /* __COM_H__ */