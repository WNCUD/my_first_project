# My_Graduation_Project

本项目是本人毕业设计，这是一个基于STM32的扫地机器人的项目。

本项目只包含了毕业设计的代码部分。

项目代码使用KEIL开发，KEIL开启的工程文件位置为：“./user/Template.uvprojx”

本项目使用的蓝牙模块、超声波需使用5V电压才能正常工作。

蓝牙模块使用串口2外设与主控通信，波特率为9600
接线方式	蓝牙TXD--PA3       
	蓝牙RXD--PA2

本项目能实现各个模块的基础控制；可检测障碍物与扫地机器人之间的相对位置；可单独执行避障程序，但无法和障碍物检测函数结合，综合运行。

IO口分配表：

外设器件	IO口
LED1		PA8
LED2		PD2
WK_UP		PA0
KEY1		PC5
KEY2		PA15

OLED
SCL		PC8
SDA		PC9		
RES		PC10
DC		PB7
CS		PB8

USART2_TX	PA3
USART2_RX	PA2

MOTOR
A1		PC15
A2		PC0
B1		PC13
B2		PC14
C1		PB5
C2		PB4

D1		PB9
D2		PB6

