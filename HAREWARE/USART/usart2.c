#include "usart2.h"
#include <string.h>
#include <stdio.h>
#include "motor.h"
#include "delay.h"
#include "wave.h"

USART2_type_init Usart2;
char mode_flag;

void Usart2_Init(int bps)
{
	GPIO_InitTypeDef  Gpio_Usart2;
	USART_InitTypeDef Usart2_Init;
	NVIC_InitTypeDef  Nvic_Usart2;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);//使能GPIOA口

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART1时钟
	
	Gpio_Usart2.GPIO_Pin   = GPIO_Pin_2;
	Gpio_Usart2.GPIO_Mode  = GPIO_Mode_AF_PP;
	Gpio_Usart2.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&Gpio_Usart2);
	
	Gpio_Usart2.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	Gpio_Usart2.GPIO_Pin   = GPIO_Pin_3;
	Gpio_Usart2.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&Gpio_Usart2);
	
	//设置串口初始化结构体
	Usart2_Init.USART_BaudRate            = bps;
	Usart2_Init.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
	Usart2_Init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	Usart2_Init.USART_Parity              = USART_Parity_No;
	Usart2_Init.USART_StopBits            = USART_StopBits_1;
	Usart2_Init.USART_WordLength          = USART_WordLength_8b;
	
	USART_Init(USART2,&Usart2_Init);
	
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);
	
	Nvic_Usart2.NVIC_IRQChannel                   = USART2_IRQn;
	Nvic_Usart2.NVIC_IRQChannelCmd                = ENABLE;
	Nvic_Usart2.NVIC_IRQChannelPreemptionPriority = 1;
	Nvic_Usart2.NVIC_IRQChannelSubPriority        = 3;
	NVIC_Init(&Nvic_Usart2);
	
	//使能USART1
	USART_Cmd(USART2,ENABLE);
}

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE) == SET)
	{
		Usart2.buffer[Usart2.num] = USART_ReceiveData(USART2);
		printf("%c",Usart2.buffer[Usart2.num]);
		Usart2.num++;
	}
	
	else if(USART_GetITStatus(USART2,USART_IT_IDLE) == SET)
	{
		Usart2.buffer[Usart2.num] = '\0';
		USART_ReceiveData(USART2);
	}
}

void BlueTooth_Ctrl(void)
{
	int test_time_num = 0;
	
	if(strstr(Usart2.buffer,"Power_start"))
		mode_flag = 1;
	else if(strstr(Usart2.buffer,"Power_end"))
		mode_flag = 2;
	else if(strstr(Usart2.buffer,"Go_straight"))
		mode_flag = 3;
	else if(strstr(Usart2.buffer,"Go_back"))
		mode_flag = 4;
	else if(strstr(Usart2.buffer,"Turn_right"))
		mode_flag = 5;
	else if(strstr(Usart2.buffer,"Turn_left"))
		mode_flag = 6;
	else if(strstr(Usart2.buffer,"KeepAway_Right"))
		mode_flag = 7;
	else if(strstr(Usart2.buffer,"KeepAway_Left"))
		mode_flag = 8;
	
	/*蓝牙控制测试*/
	else if(strstr(Usart2.buffer,"num_"))
	{
		mode_flag = 9;
		test_time_num = Usart2.buffer[4];
	}
	
	memset(Usart2.buffer,0,sizeof(Usart2.buffer));
	Usart2.num = 0;
		
		/*蓝牙控制测试*/
		if(mode_flag == 9)
		{
			Motor_Ctrl(Stop);
			mode_flag = 0;
		}
}



