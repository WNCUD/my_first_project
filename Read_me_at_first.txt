1.购买的蓝牙模块、超声波使用5V电压才能正常工作

2.蓝牙模块使用串口2外设与主控通信，波特率为9600
接线方式	蓝牙TXD--PA3       
	蓝牙RXD--PA2

3.本版本只能实现各个模块的基础控制，并完成一定程度的障碍检测算法、避障控制算法以及路径规划算法，只是障碍检测和避障控制算法没有结合使用。

4.此版本为未上系统的最后版本

IO口分配表：

外设器件		IO口
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

