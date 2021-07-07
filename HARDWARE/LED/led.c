#include "led.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2019/5/24
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

//初始化PB0和PB1为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{    	 
	RCC->AHB1ENR|=1<<1;	//使能PORTB时钟 
	RCC->AHB1ENR|=1<<8;	//使能PORTI时钟
	
	GPIO_Set(GPIOB,PIN0|PIN1,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_LOW,GPIO_PUPD_PU); //PB0,PB1设置
	GPIO_Set(GPIOI,PIN11,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_LOW,GPIO_PUPD_PU); //PI11设置
	LED0(1);			//关闭DS0
	LED1(1);			//关闭DS1
	
	GPIO_Pin_Set(GPIOI,PIN11,1);
}



/***************************************************************
函数名：WS2812_Delay
功  能：WS2812延时函数
参  数：无
返回值：无
***************************************************************/
void WS2812_Delay(uint16_t nns)
{
	uint16_t i;
	i = nns;
	do
	{
		;
	}while(--i);
}

uint16_t t1 = 58,t2 = 20;
//17 350ns
//35 600ns
//42 700ns
//50 800ns
//3600 50us

void set_t1_t2(uint8_t tt1,uint8_t tt2)
{
	t1 = tt1;
	t2 = tt2;
}

/***************************************************************
函数名：WS2812_Set_1
功  能：WS2812输出“1码”
参  数：无
返回值：无
注：“1码”的表示方法为850ns±150ns高电平,400ns±150ns低电平
	一定要使用寄存器操作,否则IO速度不够
***************************************************************/
void WS2812_Set_1(void)
{
	WS2812_PORT->BSRR = WS2812_PORT_PIN;
	WS2812_Delay(42);
	WS2812_PORT->BSRR = WS2812_PORT_PIN<<16;
	WS2812_Delay(35);
}

/***************************************************************
函数名：WS2812_Set_0
功  能：WS2812输出“0码”
参  数：无
返回值：无
注：“0码”的表示方法为850ns±150ns低电平,400ns±150ns高电平
	一定要使用寄存器操作,否则IO速度不够
***************************************************************/
void WS2812_Set_0(void)
{
	WS2812_PORT->BSRR = WS2812_PORT_PIN;
	WS2812_Delay(17);	
	WS2812_PORT->BSRR = WS2812_PORT_PIN<<16;
	WS2812_Delay(50);
}

/***************************************************************
函数名：WS2812_Reset
功  能：WS2812复位
参  数：无
返回值：无
***************************************************************/
void WS2812_Reset(void)
{
	WS2812_PORT->BSRR = WS2812_PORT_PIN;
	WS2812_Delay(3700);
}

/***************************************************************
函数名：WS2812_Handle
功  能：控制WS2812产生不同的颜色
参  数：R8G8B8,从高位到低位按顺序表示：红绿蓝
返回值：无
***************************************************************/
void Set_RGB(uint8_t R_Color,uint8_t G_Color,uint8_t B_Color)
{
	uint8_t tp = 0;
	uint8_t i = 0;
	uint8_t number = 8;
	uint32_t G8R8B8;
	uint32_t SetR = R_Color<<8;
	uint32_t SetG = G_Color<<16;
	uint32_t SetB = B_Color;	
	G8R8B8 = SetR+SetG+SetB;
	for(;number>0;number--)
	{
		for(i=23;i>0;i--)
		{
			tp = (G8R8B8 >> i) & 0x01;
			if(tp == 1)
			{
				WS2812_Set_1();
			}
			else
			{
				WS2812_Set_0();
			}
		}
	}
}
void WS2812_Handle(uint32_t R8G8B8)
{
	int8_t   i,tp;
	uint32_t G8R8B8;
	G8R8B8 = ((R8G8B8 & 0x00ff00) << 8) + ((R8G8B8 & 0xff0000) >> 8) + (R8G8B8 & 0x0000ff);
	
	for(i=23;i>=0;i--)
	{
		tp = (G8R8B8 >> i) & 0x01;
		if(tp == 1)
		{
			WS2812_Set_1();
		}
		else
		{
			WS2812_Set_0();
		}
	}
}
