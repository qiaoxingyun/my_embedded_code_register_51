#ifndef __SS1314_H__
#define __SS1314_H__

/* SS1314：写入需要先写控制字节再写数据字节
            控制字节：（只有高两位有效其余为0）bit7-声明后续字节是否连续:0-连续，1-不连续  
                                             bit6-声明后续字节是命令还是数据：0-命令，1-数据
            数据字节：经过控制字节的声明来发送具体的命令或数据
*/

#include "iic.h"

#define OLED_ADDR_WRITE 0x78        //设备地址
#define CONTINUOUS_CMD_MODE 0x00    //发送连续命令的控制命令
#define CONTINUOUS_DATA_MODE 0x40   //发送连续数据的控制命令

void OLED_Init(void);

void OLED_Clear(void);

void OLED_ShowStr(uint8_t x,uint8_t y,uint8_t *str);

void OLED_ShowNum(uint8_t x,uint8_t y,long num);


#endif /* __SS1314_H__ */