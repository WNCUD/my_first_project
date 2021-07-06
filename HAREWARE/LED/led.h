#ifndef __LED_H
#define __LED_H

#include "sys.h"

#define LED1_on   GPIO_ResetBits(GPIOA,GPIO_Pin_8)
#define LED1_off  GPIO_SetBits(GPIOA,GPIO_Pin_8)
#define LED2_on   GPIO_ResetBits(GPIOD,GPIO_Pin_2)
#define LED2_off  GPIO_SetBits(GPIOD,GPIO_Pin_2)

void Led_Init(void);

#endif


