#ifndef  __WAVE_H
#define  __WAVE_H

#include "stm32f10x.h"

extern float Location[2];

void Tim2_Init(u32 arr,u16 psc);
void Wave_Init(void);

int Wave1_Measure(void);//ÖÐ¼ä³¬Éù²¨
int Wave2_Measure(void);//×ó±ß³¬Éù²¨
int Wave3_Measure(void);//ÓÒ±ß³¬Éù²¨
void Location_Funcation(void);

#endif



