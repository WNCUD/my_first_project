#ifndef  __USART2_H
#define  __USART2_H

#include "stm32f10x.h"

typedef struct 
{
	char buffer[256];
	u8 num;
	u8 res_flag;
}USART2_type_init;

extern USART2_type_init Usart2;
extern char mode_flag;

void Usart2_Init(int bps);
void BlueTooth_Ctrl(void);

#endif
