#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "spi.h"


 int main(void)
 {	

	uint32_t  The_Id;
	delay_init();	    	 //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2 ); 
	uart_init(9600);
	SPI1_Init();
	 
    The_Id = SPI_Read_ID(); 
    delay_us(10); 	 
//	printf("Id = %#x \r\n ",The_Id); 

  
	
	while(1)
	{
		
//		LED0=0;
//		LED1=1;
//		delay_ms(300);	 //延时300ms
//		LED0=1;
//		LED1=0;
	delay_ms(500);	//延时300ms      
       
	}
  
 }

