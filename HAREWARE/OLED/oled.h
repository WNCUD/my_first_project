#ifndef __OLED_H
#define __OLED_H 

#include "sys.h"
#include "stdlib.h"	

//-----------------����LED�˿ڶ���---------------- 

#define LED_ON GPIO_ResetBits(GPIOD,GPIO_Pin_2)
#define LED_OFF GPIO_SetBits(GPIOD,GPIO_Pin_2)

//-----------------OLED�˿ڶ���---------------- 
//OLED�ĳ�ʼ��
//              D0   PA5��SCL��	SCL		PC8
//              D1   PA7��SDA��	SDA		PC9
//              RES  PD2		RES		PC10
//              DC   PB5		DC		PB7		��1:д����;��0:д����
//              CS   PA4  		CS		PB8		��1��Ϊѡ�и���λ��
#define OLED_SCL_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_8)//SCL
#define OLED_SCL_Set() GPIO_SetBits(GPIOC,GPIO_Pin_8)

#define OLED_SDA_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_9)//SDA
#define OLED_SDA_Set() GPIO_SetBits(GPIOC,GPIO_Pin_9)

#define OLED_RES_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_10)//RES
#define OLED_RES_Set() GPIO_SetBits(GPIOC,GPIO_Pin_10)

#define OLED_DC_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_7)//DC
#define OLED_DC_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_7)

#define OLED_CS_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_8)//CS
#define OLED_CS_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_8)


#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

void OLED_ClearPoint(u8 x,u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void OLED_WR_Byte(u8 dat,u8 mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode);
void OLED_ShowChar6x8(u8 x,u8 y,u8 chr,u8 mode);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);
void OLED_ScrollDisplay(u8 num,u8 space,u8 mode);
void OLED_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode);
void OLED_Init(void);

#endif

