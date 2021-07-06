/**********************************************************************************************************  
����	�ӿ�   	gpio��	����״̬   	����״̬
WK_UP 	WK_UP  	PA0    	�͵�ƽ     	�ߵ�ƽ
KEY0   	KEY0   	PC5    	�ߵ�ƽ		�͵�ƽ
KEY1   	KEY1   	PA15    �ߵ�ƽ     	�͵�ƽ
**********************************************************************************************************/

#include "key.h"
#include "sys.h"
#include "delay.h"
#include <stdio.h>

/**********************************************************************************************************
* ������    ��key_init
* ��������  ������key0/1/2��key_up�ĳ�ʼ��
* ����      ������ʢ  
* ����˵��  ��      
* ����ֵ˵����
* �޸ļ�¼  ��
* ����      ��
**********************************************************************************************************/
void key_init(void)
{
	GPIO_InitTypeDef key_up, key;
	
	//PA/PE��ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	//���ýṹ��
	key_up.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_15;
    key_up.GPIO_Mode  = GPIO_Mode_IPD;
    key_up.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&key_up);
	
	//���ýṹ��
	key.GPIO_Pin   = GPIO_Pin_5;
    key.GPIO_Mode  = GPIO_Mode_IPU;
    key.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC,&key);
}

/**********************************************************************************************************
* ������    ��key_scan
* ��������  ��key�İ���ɨ�躯����һ�ΰ�����Ч��
* ����      ������ʢ  
* ����˵��  ��      
* ����ֵ˵����
* �޸ļ�¼  ��
* ����      ��
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
