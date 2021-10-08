/*
PA1 CHANNEL1  PH 
PA2 CHANNEL3  O2
PA3 CHANNEL2  TU
*/
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "spi.h"
#include "ds18b20.h"
#include "adc.h"

void conver(void);
uint8_t  readbuff[4096]; //放在堆栈溢出
uint8_t  writebuff[4096];
float  tem,ADC_PH_Temp1,ADC_TU_Temp2,ADC_O2_Temp3,PH,TU,O2;
float  TU_calibration = 0.0;
float  ADC_O2_Temp3_last = 0.0,ADC_O2_Temp3_Now = 0.0;
//float  Y_Value,X_Value; //Y一阶滤波上次输出值,X为本次输出

float FirstOrderFilter(float X_Value,float Y_Value);
float Get_O2_ADValue();
 int main(void)
 {	

//	uint32_t  The_Id;
	uint8_t check = 1; 
	
	delay_init();	    	 //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2 ); 
	uart_init(9600);
	ADC1_Multi_Init();
    DS18B20_Init();
//	if(check == 0)
//	{
//		printf("ok \r\n "); 
//	}
	/* 
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
	 
	 */
	 
	while(1)
	{
//	 conver();	
//   tem = DS18B20_Get_Temp();
     delay_ms(1000);  
 	 ADC_O2_Temp3_last = Get_O2_ADValue();
	 delay_us(10);
     ADC_O2_Temp3_Now  = Get_O2_ADValue();
     O2 =  FirstOrderFilter(ADC_O2_Temp3_Now,ADC_O2_Temp3_last) ;		
//     printf("tem =  %.2f \r\n ",tem/10);
//    printf("{\"zhuo\":%.2f,\"temperature\":%.2f,\"O2\":%.2f,\"pH\":%.2f}"
//		,TU,tem/10,O2,PH);		
//printf("ADC_TU_Temp2 = %f \r\n ,ADC_TU_Temp2 = %f\r\n ,ADC_O2_Temp3 = %f\r\n",
//		ADC_TU_Temp2,ADC_TU_Temp2,ADC_O2_Temp3) ;
	if(ADC_O2_Temp3_last!=ADC_O2_Temp3_Now)
		{
	       printf("ADC_O2_Temp3 = %f \r\n",O2); 
	    }
    
	}
  
 }

void conver(void)
{    
	 ADC_PH_Temp1 = (float)ADC_Value[0]*3.3/4096;
	 ADC_TU_Temp2 = (float)ADC_Value[1]*3.3/4096;
//	 ADC_O2_Temp3 = (float)ADC_Value[2]*3.3/4096;
	
	 PH = -5.7541*ADC_PH_Temp1+16.654;
	if(PH<=0.0)
      {
		  PH=0.0;
	  }
	if(PH>=14.0)
      {
	      PH=14.0;
	  }
	   TU_calibration=-0.0192*(tem/10-25)+ADC_TU_Temp2;
	   TU=-865.68*ADC_TU_Temp2+3291.3;
	  if(TU<=0)
      {
	      TU=0;
	  }
	  if(TU>=3000)
      {
		  TU=3000;
	  }
//	  O2 = ADC_O2_Temp3;
}

float FirstOrderFilter(float X_Value,float Y_Value)
{
	float NewValue;
	NewValue = Factor*X_Value +(1-Factor )*Y_Value ;
    return NewValue;	
}
