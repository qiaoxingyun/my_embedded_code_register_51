#ifndef __INT_OLED_H__
#define __INT_OLED_H__
#include "Com_util.h"

void Int_OLED_WriteDate(u8 butes[],u8 length);

void Int_OLED_WriteCommand(u8 butes[],u8 length);

void Int_OLED_Init();

void Int_OLED_Clean();

/**
 * @brief 在指定位置(x,y显示字符串)
 * @param x 横坐标
 * @param y 纵坐标
 * @param str 待展示字符串
 */
void Int_OLED_ShowStr(u8 x,u8 y,u8 *str);

void Int_OLED_ShowNum(u8 x, u8 y, long int num);

#endif /*__INT_OLED_H__*/