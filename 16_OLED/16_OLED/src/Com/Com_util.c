#include "Com_util.h"
#include <INTRINS.H>
#include <STC89C5xRC.H>

/**
 * @brief 动态延时函数，支持传参控制毫秒数
 * @param ms 要延时的毫秒数（范围：1~255，受 u8 类型限制）
 */
void Com_util_DelayMs(u8 ms)  // 若需更大范围，可改为 u16 ms
{
    unsigned char data i, j;
    for (; ms > 0; ms--)  // 循环 ms 次，每次延时 1ms
    {
        _nop_();
        i = 2;
        j = 199;
        do
        {
            while (--j);
        } while (--i);
    }
}