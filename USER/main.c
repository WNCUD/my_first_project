#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "usart2.h"
#include <stdio.h>
#include <string.h>
#include "key.h"
#include "wave.h"
#include "motor.h" 
#include "sys.h"


int main(void)
{	
	int i = 0;
	delay_init(72);
	uart_init(115200);
	printf("%d,%s\r\n",__LINE__,__FILE__);

	Tim2_Init(0xffff,72);
	Wave_Init();
	printf("%d,%s\r\n",__LINE__,__FILE__);

	
//	Motor_Init();

	while(1)
	{
		Location_Funcation();
		
//		i = Wave1_Measure();
		
		printf("x = %.2fcm,y = %.2fcm\r\n",Location[0],Location[1]);
		delay_ms(1000);
//		PBout(6) = 0;
//		PBout(9) = 1;
//		
//		/*电机C*/
//		PBout(5) = 1;
//		PBout(4) = 0;
//		
//		/*电机B*/
//		PCout(13) = 1;
//		PCout(14) = 0;
//		
//		/*电机A*/
//		PCout(0) = 1;
//		PCout(15) = 0;
//		BlueTooth_Ctrl();//蓝牙通信函数

//		switch(mode_flag)
//		{
//			case 1:			//Power_start
//			{
//				mode_flag = 0;
//				
//				while(1)
//				{
//					Location_Funcation();
//					Keep_Away();
//					
//					Motor_Ctrl(Go_Straight);
//					delay_ms(3000);
//					Motor_Ctrl(Stop);
//					
//					BlueTooth_Ctrl();
//					
//					if(mode_flag == 2)
//					{
//						mode_flag = 0;
//						Motor_Ctrl(Stop);
//						break;
//					}
//				}
//			}
//			case 2:Motor_Ctrl(Stop);		mode_flag = 0;break;//Power_end
//			case 3:Motor_Ctrl(Go_Straight);	mode_flag = 0;break;//Go_straight
//			case 4:Motor_Ctrl(Go_Back);		mode_flag = 0;break;//Go_back
//			case 5:Motor_Ctrl(Turn_Right);	mode_flag = 0;break;//Turn_right
//			case 6:Motor_Ctrl(Turn_Left);	mode_flag = 0;break;//Turn_left
//			case 7:KeepAway_Right();		mode_flag = 0;Motor_Ctrl(Stop);break;
//			case 8:KeepAway_Left();			mode_flag = 0;Motor_Ctrl(Stop);break;
//		}
//		delay_ms(1000);
	}/*while结尾*/
}/*main结尾*/



