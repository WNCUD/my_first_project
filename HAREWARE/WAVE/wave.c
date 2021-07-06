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
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//�жϱ�־���
}

void Wave_Init(void)
{
	GPIO_InitTypeDef  Gpio_WaveOutInit,Gpio_WaveInInit;//����GPIO�ṹ�����

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

	
	Gpio_WaveOutInit.GPIO_Mode = GPIO_Mode_Out_PP;//ͨ�����ģʽ
	Gpio_WaveOutInit.GPIO_Pin = GPIO_Pin_0;
	Gpio_WaveOutInit.GPIO_Speed = GPIO_Speed_50MHz;//���ó�50M
	Gpio_WaveOutInit.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_13;//��3���ܽ�
	GPIO_Init(GPIOB, &Gpio_WaveOutInit);
	Gpio_WaveOutInit.GPIO_Pin = GPIO_Pin_6;//��3���ܽ�
	GPIO_Init(GPIOC, &Gpio_WaveOutInit);
	GPIO_ResetBits(GPIOB, GPIO_Pin_11|GPIO_Pin_13);
	GPIO_ResetBits(GPIOC, GPIO_Pin_6);


	Gpio_WaveInInit.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	Gpio_WaveInInit.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15;//��3���ܽ�
	GPIO_Init(GPIOB, &Gpio_WaveInInit);

}

int Wave1_Measure(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_11);
		delay_us(20);
	GPIO_ResetBits(GPIOB, GPIO_Pin_11);
	
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12) == 0);//�ȴ�echo�ĸߵ�ƽ����	
		delay_us(20);

	TIM_SetCounter(TIM2,0); //���������
	TIM_Cmd(TIM2, ENABLE);  //ʹ�ܶ�ʱ��5,��ʼ����

	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12) == 1);//�ȴ�echo�ĸߵ�ƽ����

	TIM_Cmd(TIM2, DISABLE);	//ʧ�ܶ�ʱ��5,��ֹ����	
	
	return (TIM_GetCounter(TIM2));	//���ض�ʱ�������ļ���ֵ
}

int Wave2_Measure(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
		delay_us(20);
	GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15) == 0);//�ȴ�echo�ĸߵ�ƽ����	
		delay_us(20);

	TIM_SetCounter(TIM2,0); //���������
	TIM_Cmd(TIM2, ENABLE);  //ʹ�ܶ�ʱ��5,��ʼ����

	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15) == 1);//�ȴ�echo�ĸߵ�ƽ����

	TIM_Cmd(TIM2, DISABLE);	//ʧ�ܶ�ʱ��5,��ֹ����	
	
	return (TIM_GetCounter(TIM2));	//���ض�ʱ�������ļ���ֵ
}

int Wave3_Measure(void)
{
	GPIO_SetBits(GPIOC, GPIO_Pin_6);
		delay_us(20);
	GPIO_ResetBits(GPIOC, GPIO_Pin_6);
	
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14) == 0);//�ȴ�echo�ĸߵ�ƽ����	
		delay_us(20);

	TIM_SetCounter(TIM2,0); //���������
	TIM_Cmd(TIM2, ENABLE);  //ʹ�ܶ�ʱ��5,��ʼ����
	
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14) == 1);//�ȴ�echo�ĸߵ�ƽ����

	TIM_Cmd(TIM2, DISABLE);	//ʧ�ܶ�ʱ��5,��ֹ����	
	
	return (TIM_GetCounter(TIM2));	//���ض�ʱ�������ļ���ֵ
}

//������1Ϊ�м�ģ�飬������2Ϊ���ģ�飬������3Ϊ�ұ�ģ�飨����ΪС��ǰ����������ң�
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
	l1 /= 20;//�м�
	l2 /= 20;//���
	l3 /= 20;//�ұ�
	
//	printf("l1 = %.2f,l2 = %.2f,l3 = %.2f\r\n",l1,l2,l3);
	
	y = (l3 * l3 - l2 * l2) / (4 * 5);
	x = sqrt(l1 * l1 - y * y);
	
	Location[0] = x;
	Location[1] = y;
//	printf("x = %.2f,y = %.2f\r\n",Location[0],Location[1]);
		
}
