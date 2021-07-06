#include "motor.h"
#include "delay.h"
#include "wave.h"

void Motor_Init(void)
{
	GPIO_InitTypeDef Gpio_Motor;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

	
	Gpio_Motor.GPIO_Mode  = GPIO_Mode_Out_PP;
	Gpio_Motor.GPIO_Pin   = GPIO_Pin_6|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_9;
	Gpio_Motor.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&Gpio_Motor);
	GPIO_ResetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_9);
	
	Gpio_Motor.GPIO_Mode  = GPIO_Mode_Out_PP;
	Gpio_Motor.GPIO_Pin   = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_0;
	Gpio_Motor.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC,&Gpio_Motor);
	GPIO_ResetBits(GPIOC,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_0);
}

void Motor_Ctrl(u8 cmd)
{
	u8 i = 0, data[8] = {0};
	
	for(i = 0;i < 8;i++)
	{
		if(cmd & 0x80)
			data[7 - i] = 1;
			
		else
			data[7 - i] = 0;
		cmd <<= 1;
	}
	
	/*电机D*/
	PBout(6) = data[0];
	PBout(9) = data[1];
	
	/*电机C*/
	PBout(5) = data[2];
	PBout(4) = data[3];
	
	/*电机B*/
	PCout(13) = data[4];
	PCout(14) = data[5];
	
	/*电机A*/
	PCout(0) = data[6];
	PCout(15) = data[7];
}


void KeepAway_Right(void)
{
	int time_stop = 200,time_turn = 350;
	
	Motor_Ctrl(Turn_Right);//右转
	delay_ms(time_turn);
	
	Motor_Ctrl(Go_Straight);//前进
	delay_ms(500);
	
	Motor_Ctrl(Turn_Left);//左转
	delay_ms(time_turn);
	
	Motor_Ctrl(Go_Straight);//前进
	delay_ms(500);
	
	Motor_Ctrl(Turn_Left);//左转
	delay_ms(time_turn);
	
	Motor_Ctrl(Go_Straight);//前进
	delay_ms(500);
	
	Motor_Ctrl(Turn_Right);//右转
	delay_ms(time_turn);
	
	Motor_Ctrl(Go_Straight);//最后改为直行
}


void KeepAway_Left(void)
{
	int time_stop = 500,time_turn = 350;
	
	Motor_Ctrl(Turn_Left);//左转
	delay_ms(time_turn);
	
	Motor_Ctrl(Go_Straight);//前进
	delay_ms(500);
	
	Motor_Ctrl(Turn_Right);//右转
	delay_ms(time_turn);

	Motor_Ctrl(Go_Straight);//前进
	delay_ms(500);
	
	Motor_Ctrl(Turn_Right);//右转
	delay_ms(time_turn);
	
	Motor_Ctrl(Go_Straight);//前进
	delay_ms(500);
	
	Motor_Ctrl(Turn_Left);//左转
	delay_ms(time_turn);
	
	Motor_Ctrl(Go_Straight);//最后改为直行
}

void Keep_Away(void)
{
	if(Location[0] < 30)
	{
		if(Location[1] == 1)
			KeepAway_Left();
		else
			KeepAway_Right();
	}
}



