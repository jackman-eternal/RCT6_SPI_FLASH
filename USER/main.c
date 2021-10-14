/*
PA1 CHANNEL1  PH 
PA2 CHANNEL2  O2
PA3 CHANNEL3  TU
*/
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "spi.h"
#include "ds18b20.h"
#include "adc.h"
//#include "timer.h"
//void conver(void);
//float Get_Average();

typedef struct 
{
	float Value_PH;
	float Value_TUS;
	float Value_O2;
	float Value_Tem;
}Device;
float tem;
float Get_Value_O2(float tem,float Value_O);
//uint8_t  readbuff[4096]; //放在堆栈溢出
//uint8_t  writebuff[4096];
float  TU_calibration = 0.0;
void Calc(void);
Device Data;
 int main(void)
 {	
	
	delay_init();	    	 //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2 ); 
	uart_init(9600);
	ADC1_Multi_Init();
    DS18B20_Init();
	
	while(1)
	{
		 
    
     delay_ms(1000);  	
//     printf("{\"zhuo\":%.2f,\"temperature\":%.2f,\"O2\":%.2f,\"pH\":%.2f}"
//		,Data.Value_TUS,Data.Value_Tem/10,Data.Value_O2,Data.Value_PH);		
	    
	}
  
 }

 void Calc(void)
 {
	Data.Value_PH = (float)ADC_Value[0]*3.3/4096; 
	Data.Value_O2 = (float)ADC_Value[1]*3.3/4096;
	Data.Value_TUS = (float)ADC_Value[2]*3.3/4096;
	
	Data.Value_Tem  = DS18B20_Get_Temp(); 
	delay_ms(100); 
	Data.Value_PH = -5.7541*Data.Value_PH+16.654;
	 if(Data.Value_PH<=0.0)
      {
		  Data.Value_PH=0.0;
	  }
	if(Data.Value_PH>=14.0)
      {
	      Data.Value_PH=14.0;
	  }
	 Data.Value_TUS=-865.68*Data.Value_TUS+3291.3;
	  if( Data.Value_TUS<=0)
      {
	       Data.Value_TUS=0;
	  }
	  if( Data.Value_TUS>=3000)
      {
		   Data.Value_TUS=3000;
	  }
	  Data.Value_O2 = 0.2589*Data.Value_O2+0.7868;
	  Data.Value_O2 = Get_Value_O2(Data.Value_Tem,Data.Value_O2);
 }
 /*
void conver(void)
{    
	 ADC_PH_Temp1 = (float)ADC_Value[0]*3.3/4096;
	 ADC_TU_Temp2 = (float)ADC_Value[1]*3.3/4096;
	 ADC_O2_Temp3 = (float)ADC_Value[2]*3.3/4096;
     O2 = Get_Average();
	 O2 = 0.2589*O2+0.7868;
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
}
*/
//float Get_Average()
//{
//	u8 i;
//	float sum_O2 =0.0;
//	for(i=0;i<10;i++)
//	{
//		ADC_O2_Temp3 =(float)ADC_Value[2]*3.3/4096;
//		delay_us(20); 
//		sum_O2 = ADC_O2_Temp3 + sum_O2;
//	}
//	return 	sum_O2 = sum_O2/10.0;
//}


float Get_Value_O2(float tem,float Value_O)
{
	if(tem>=15&&tem<=35)
	{
		if(tem<20)
		{
			Value_O = 9.1-0.20*(tem-20.0);
		}
		else if(tem>=20&&tem<25)
		{
			Value_O = 8.3 - 0.16*(tem-25.0);
		}
		else if(tem>25&&tem<30)
		{
			Value_O = 8.3 - 0.14*(tem-25.0);
		}
		else 
		{
			Value_O = 7.6 - 0.12*(tem-30.0);
		}
		return Value_O;
	}
	else 
	{
		return 0.0;
	}
}
