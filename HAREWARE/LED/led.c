#include "led.h"
#include "stm32f10x.h"
/*********�ӿ������*************************
��������   	оƬ��������	ԭ��ͼ�ӿ�	GPIO��
DS0							LED0		PA8
DS1							LED1		PD2
*********************************************/
void Led_Init(void)
{
	GPIO_InitTypeDef Gpio_Led1Init,Gpio_Led2Init;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��gpiob��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);//ʹ��gpioe��ʱ��

	Gpio_Led1Init.GPIO_Mode  = GPIO_Mode_Out_PP;
	Gpio_Led1Init.GPIO_Pin   = GPIO_Pin_8;
	Gpio_Led1Init.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&Gpio_Led1Init);
	
	
	Gpio_Led2Init.GPIO_Mode  = GPIO_Mode_Out_PP;
	Gpio_Led2Init.GPIO_Pin   = GPIO_Pin_2;
	Gpio_Led2Init.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOD,&Gpio_Led2Init);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
	GPIO_SetBits(GPIOD,GPIO_Pin_2);
}

