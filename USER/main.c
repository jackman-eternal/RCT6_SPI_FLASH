#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "spi.h"

uint8_t  readbuff[4096]; //放在堆栈溢出
uint8_t  writebuff[4096];
 int main(void)
 {	

	uint32_t  The_Id;
	uint16_t i=0;
	
	delay_init();	    	 //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2 ); 
	uart_init(9600);
	SPI1_Init();
	 
    The_Id = SPI_Read_ID(); 
    delay_us(10); 	 
//printf("Id = %#x \r\n ",The_Id); 
    SPI_Erase_Sector(0);
    
	  for(i=0;i<4096;i++)
	 {
		writebuff[i] = i ; 
	 }
	SPI_Write_Data(0,writebuff,4096); 
	 
    SPI_Read_Data(0,readbuff,4096);
	 for(i=0;i<4096;i++)
	 {
		 printf("%#x ",readbuff[i]); 
		 if(i%10 == 0)
		 printf("\n"); 
	 }
	 
	 
	while(1)
	{
		
//		LED0=0;
//		LED1=1;
//		delay_ms(300);	 //延时300ms
//		LED0=1;
//		LED1=0;
//	    delay_ms(500);	//延时300ms      
	}
  
 }

