#include "led.h"
#include "stm32f10x.h"
/*********接口详情表*************************
板上名称   	芯片引脚名称	原理图接口	GPIO口
DS0							LED0		PA8
DS1							LED1		PD2
*********************************************/
void Led_Init(void)
{
	GPIO_InitTypeDef Gpio_Led1Init,Gpio_Led2Init;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能gpiob口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);//使能gpioe口时钟

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

