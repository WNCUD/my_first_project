#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

#define KEY_UP  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define KEY0    GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)
#define KEY1    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)

void key_init(void);
int key_scan(void);


#endif
