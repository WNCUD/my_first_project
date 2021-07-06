/**********************************************************************************************************  
名称	接口   	gpio口	空闲状态   	工作状态
WK_UP 	WK_UP  	PA0    	低电平     	高电平
KEY0   	KEY0   	PC5    	高电平		低电平
KEY1   	KEY1   	PA15    高电平     	低电平
**********************************************************************************************************/

#include "key.h"
#include "sys.h"
#include "delay.h"
#include <stdio.h>

/**********************************************************************************************************
* 函数名    ：key_init
* 功能描述  ：按键key0/1/2和key_up的初始化
* 作者      ：王忠盛  
* 参数说明  ：      
* 返回值说明：
* 修改记录  ：
* 其他      ：
**********************************************************************************************************/
void key_init(void)
{
	GPIO_InitTypeDef key_up, key;
	
	//PA/PE口时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	//配置结构体
	key_up.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_15;
    key_up.GPIO_Mode  = GPIO_Mode_IPD;
    key_up.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&key_up);
	
	//配置结构体
	key.GPIO_Pin   = GPIO_Pin_5;
    key.GPIO_Mode  = GPIO_Mode_IPU;
    key.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC,&key);
}

/**********************************************************************************************************
* 函数名    ：key_scan
* 功能描述  ：key的按键扫描函数（一次按键有效）
* 作者      ：王忠盛  
* 参数说明  ：      
* 返回值说明：
* 修改记录  ：
* 其他      ：
**********************************************************************************************************/
int key_scan(void)
{
	static char flag_key = 0;
	
	if(flag_key == 0 && (KEY_UP ==1 || KEY0 == 0 || KEY1 == 0))
	{
		flag_key = 1;
		delay_us(1000);
		if(KEY_UP == 1) return 1;
		else if( KEY0 == 0) return 2;
		else if( KEY1 == 0) return 3;
	}
	
	if(KEY_UP == 0 && KEY0 == 1 && KEY1 == 1)
		flag_key = 0;
	
	return 0;
}
