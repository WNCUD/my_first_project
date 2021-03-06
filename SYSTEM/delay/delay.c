/*
SysTick->VAL     //计数器寄存器
SysTick->CTRL    //控制及状态寄存器
SysTick->LOAD    //重新加载数值寄存器
SysTick->CALIB   //校准数值寄存器
*/
#include "delay.h"
#include "led.h"

float num_us;
float num_ms;

/**********************************************************************************************************
* 函数名    ：delay_init
* 功能描述  ：延时函数初始化
* 作者      ：王忠盛
* 参数说明  ：num：使用芯片主频   
* 返回值说明：
* 修改记录  ：
* 其他      ：
**********************************************************************************************************/
void delay_init(int num)
{
	
	SysTick->CTRL &= ~( 0x1 << 2 );//选择M4内核的外部时钟源(STM32的内部)
	SysTick->VAL = 0;//控制寄存器清零
	
	num_us = num / 8.0;//计算得出1us所需计数值
	num_ms = num_us * 1000;//计算得出1ms所需计数值
}

/**********************************************************************************************************
* 函数名    ：delay_us
* 功能描述  ：微秒级延时函数
* 作者      ：王忠盛
* 参数说明  ：us：需要延时的微秒数    
* 返回值说明：
* 修改记录  ：
* 其他      ：
**********************************************************************************************************/
void delay_us(int us)
{
	SysTick->CTRL = 0;//控制寄存器清零
	SysTick->LOAD = us * num_us;//将需要计算的数据写入重装载计数器
	SysTick->VAL = 0;//清空计数器
	SysTick->CTRL |= 1 << 0;//使能systick定时器
	
	while( !( SysTick->CTRL & 1 << 16 ) );//等待计数时间到达
	
	SysTick->CTRL &= ~( 1 << 0);//关闭计时器
	SysTick->VAL = 0;//清零计数寄存器
	
}

/**********************************************************************************************************
* 函数名    ：delay_ms
* 功能描述  ：毫秒级延时函数
* 作者      ：王忠盛
* 参数说明  ：ms：需要延时的时间    
* 返回值说明：
* 修改记录  ：
* 其他      ：
**********************************************************************************************************/
void delay_ms_init(int ms)
{
	SysTick->CTRL = 0;//控制寄存器清零
	SysTick->LOAD = num_ms * ms;//将需要计算的数据写入重装载计数器
	SysTick->VAL = 0;//清空计数器
	SysTick->CTRL |= 1 << 0;//使能systick定时器

	while( !( SysTick->CTRL & 1 << 16 ) );//等待计数时间到达
	SysTick->CTRL &= ~( 1 << 0);//关闭计时器
	SysTick->VAL = 0;//清零计数寄存器
}


/**********************************************************************************************************
* 函数名    ：delay_ms
* 功能描述  ：毫秒级延时函数
* 作者      ：王忠盛
* 参数说明  ：ms：需要延时的时间    
* 返回值说明：
* 修改记录  ：
* 其他      ：
**********************************************************************************************************/
void delay_ms(int ms)
{
	int num = ms / 540, i = 0;
	int remain = ms % 540;
	
	for(i = 0; i < num; i++)
		delay_ms_init(540);
	
	if(remain != 0)
		delay_ms_init(remain);
	
}



