#ifndef  __WAVE_H
#define  __WAVE_H

#include "stm32f10x.h"

extern float Location[2];

void Tim2_Init(u32 arr,u16 psc);
void Wave_Init(void);

int Wave1_Measure(void);//�м䳬����
int Wave2_Measure(void);//��߳�����
int Wave3_Measure(void);//�ұ߳�����
void Location_Funcation(void);

#endif



