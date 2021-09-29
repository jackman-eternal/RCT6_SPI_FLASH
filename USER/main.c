#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "spi.h"


 int main(void)
 {	
	uint32_t  The_Id;
	delay_init();	    	 //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	uart_init(9600);
	SPI1_Init();
	 
   
	 
	while(1)
	{
    The_Id = SPI_Read_ID(); 
    delay_us(10); 	 
	printf("Id = %#x \r\n ",The_Id); 
	
//		LED0=0;
//		LED1=1;
//		delay_ms(300);	 //��ʱ300ms
//		LED0=1;
//		LED1=0;
		delay_ms(300);	//��ʱ300ms      
		
	}
 }

