#ifndef  __MOTOR_H
#define  __MOTOR_H

#include "stm32f10x.h"
#include "sys.h"

#define Turn_Right  0xe2
#define Turn_Left   0xab
#define Go_Straight 0xaa
#define Go_Back     0x69
#define Stop        0xff 
#define Run         0xaa


void Motor_Init(void);
void Left_Adence(void);
void Left_Retreat(void);
void Rihgt_Adence(void);
void Right_Retreat(void);
void ClearMotor_Open(void);
void ClearMotor_Close(void);
void Motor_Ctrl(u8 cmd);

void KeepAway_Right(void);
void KeepAway_Left(void);
void ThePlanWay(int time,int turn_time);
void Keep_Away(void);

#endif
