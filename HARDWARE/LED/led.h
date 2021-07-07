#ifndef __LED_H
#define __LED_H	 
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2019/5/24
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

//LED�˿ڶ���
#define LED0(x)			GPIO_Pin_Set(GPIOB,PIN1,x)		// DS0
#define LED1(x)			GPIO_Pin_Set(GPIOB,PIN0,x)		// DS1 

#define WS2812_PORT			GPIOI
#define WS2812_PORT_PIN		PIN11

extern uint16_t t1,t2;

void LED_Init(void);	//��ʼ��		 	
void WS2812_Delay(uint16_t nns);
void set_t1_t2(uint8_t tt1,uint8_t tt2);
void WS2812_Set_1(void);
void WS2812_Set_0(void);
void WS2812_Reset(void);
void Set_RGB(uint8_t R_Color,uint8_t G_Color,uint8_t B_Color);
void WS2812_Handle(uint32_t R8G8B8);

#endif

















