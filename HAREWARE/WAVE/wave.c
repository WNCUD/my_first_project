#include "wave.h"
#include "delay.h"
#include <stdio.h>
#include <math.h>

float Location[2];

void Tim2_Init(u32 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  Tim_WaveInit;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	Tim_WaveInit.TIM_ClockDivision = TIM_CKD_DIV1;
	Tim_WaveInit.TIM_CounterMode = TIM_CounterMode_Up;
	Tim_WaveInit.TIM_Period = arr - 1;
	Tim_WaveInit.TIM_Prescaler = psc - 1;
	TIM_TimeBaseInit(TIM2,&Tim_WaveInit);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//中断标志清除
}

void Wave_Init(void)
{
	GPIO_InitTypeDef  Gpio_WaveOutInit,Gpio_WaveInInit;//声明GPIO结构体变量

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

	
	Gpio_WaveOutInit.GPIO_Mode = GPIO_Mode_Out_PP;//通用输出模式
	Gpio_WaveOutInit.GPIO_Pin = GPIO_Pin_0;
	Gpio_WaveOutInit.GPIO_Speed = GPIO_Speed_50MHz;//配置成50M
	Gpio_WaveOutInit.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_13;//第3个管脚
	GPIO_Init(GPIOB, &Gpio_WaveOutInit);
	Gpio_WaveOutInit.GPIO_Pin = GPIO_Pin_6;//第3个管脚
	GPIO_Init(GPIOC, &Gpio_WaveOutInit);
	GPIO_ResetBits(GPIOB, GPIO_Pin_11|GPIO_Pin_13);
	GPIO_ResetBits(GPIOC, GPIO_Pin_6);


	Gpio_WaveInInit.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	Gpio_WaveInInit.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15;//第3个管脚
	GPIO_Init(GPIOB, &Gpio_WaveInInit);

}

int Wave1_Measure(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_11);
		delay_us(20);
	GPIO_ResetBits(GPIOB, GPIO_Pin_11);
	
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12) == 0);//等待echo的高电平到来	
		delay_us(20);

	TIM_SetCounter(TIM2,0); //清零计数器
	TIM_Cmd(TIM2, ENABLE);  //使能定时器5,开始计数

	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12) == 1);//等待echo的高电平结束

	TIM_Cmd(TIM2, DISABLE);	//失能定时器5,截止计数	
	
	return (TIM_GetCounter(TIM2));	//返回定时计数器的计数值
}

int Wave2_Measure(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
		delay_us(20);
	GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15) == 0);//等待echo的高电平到来	
		delay_us(20);

	TIM_SetCounter(TIM2,0); //清零计数器
	TIM_Cmd(TIM2, ENABLE);  //使能定时器5,开始计数

	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15) == 1);//等待echo的高电平结束

	TIM_Cmd(TIM2, DISABLE);	//失能定时器5,截止计数	
	
	return (TIM_GetCounter(TIM2));	//返回定时计数器的计数值
}

int Wave3_Measure(void)
{
	GPIO_SetBits(GPIOC, GPIO_Pin_6);
		delay_us(20);
	GPIO_ResetBits(GPIOC, GPIO_Pin_6);
	
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14) == 0);//等待echo的高电平到来	
		delay_us(20);

	TIM_SetCounter(TIM2,0); //清零计数器
	TIM_Cmd(TIM2, ENABLE);  //使能定时器5,开始计数
	
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14) == 1);//等待echo的高电平结束

	TIM_Cmd(TIM2, DISABLE);	//失能定时器5,截止计数	
	
	return (TIM_GetCounter(TIM2));	//返回定时计数器的计数值
}

//超声波1为中间模块，超声波2为左边模块，超声波3为右边模块（左右为小车前进方向的左右）
void Location_Funcation(void)
{
	char i = 0;
	float l1 = 0, l2 = 0, l3 = 0, x = 0, y = 0;
	
	for(i = 0;i < 20;i++)
	{
		l1 += Wave1_Measure()/58.0;
		l2 += Wave2_Measure()/58.0;
		l3 += Wave3_Measure()/58.0;
	}
	l1 /= 20;//中间
	l2 /= 20;//左边
	l3 /= 20;//右边
	
//	printf("l1 = %.2f,l2 = %.2f,l3 = %.2f\r\n",l1,l2,l3);
	
	y = (l3 * l3 - l2 * l2) / (4 * 5);
	x = sqrt(l1 * l1 - y * y);
	
	Location[0] = x;
	Location[1] = y;
//	printf("x = %.2f,y = %.2f\r\n",Location[0],Location[1]);
		
}
