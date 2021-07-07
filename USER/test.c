#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h" 
#include "mpu.h"    
#include "lcd.h"   
#include "sdram.h"   
#include "key.h" 
#include "usmart.h" 
//ALIENTEK ������STM32H750/F750������ ʵ��16
//USMART���� ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾

uint32_t RGB_Buf[7]={0x00,0x00,0x00,0x00,0x00,0x00,0x00};



int main(void)
{   
 	u8 led0sta=1;
	u8 t=0,j=0;
	
	RGB_Buf[0]=0xFF0000;
	RGB_Buf[1]=0x00FF00;
	RGB_Buf[2]=0x0000FF;
	RGB_Buf[3]=0x00FFFF;
	RGB_Buf[4]=0xFFFF00;
	RGB_Buf[5]=0xFF00FF;
	RGB_Buf[6]=0xFFFFFF;
	
	Stm32_Clock_Init(432,25,2,9);//����ʱ��,216Mhz
    delay_init(216);			//��ʱ��ʼ��  
	uart_init(108,115200);		//��ʼ�����ڲ�����Ϊ115200
	usmart_dev.init(108); 		//��ʼ��USMART	
	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	MPU_Memory_Protection();	//������ش洢����
	SDRAM_Init();				//��ʼ��SDRAM 
	LCD_Init();					//��ʼ��LCD
	POINT_COLOR=RED;			//��ɫ����
	LCD_ShowString(30,50,200,16,16,"POLARIS STM32"); 
	LCD_ShowString(30,70,200,16,16,"USMART TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2019/5/24");	
	
	WS2812_Reset();	
  	while(1) 
	{
		LED0(led0sta^=1);		//LED0��˸

		for(j=0;j<4;j++)
		{
			WS2812_Handle(RGB_Buf[t++%7]);
		}

		t-=3;
		delay_ms(150);	
//		WS2812_PORT->BSRR = WS2812_PORT_PIN;
//		WS2812_Delay(t2);	
//		WS2812_PORT->BSRR = WS2812_PORT_PIN<<16;
//		WS2812_Delay(t1);
	} 
}











