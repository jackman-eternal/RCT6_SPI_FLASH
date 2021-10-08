#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"

#define TimeConstant 1                  //滤波器时间常数
#define Ts           0.0001             //运算周期
//#define Factor  (1/((TimeConstant/Ts)+1)) //滤波系数
#define Factor       0.45


//extern   __IO uint32_t ADC_ConValue;
//extern   __IO uint16_t ADC_Value;  //转换的电压值通过DMA传到SRAM
extern   __IO uint16_t ADC_Value[3]; //多通道模式，在sram中定义两个变量

void ADC1_Init(void);        //单通道
void ADC1_Multi_Init(void);  //多通道
void ADC12_Reg_Init(void);   //双重ADC
#endif

//void conver(void);
/*
void conver(void)
{
	 ADC_PH_Temp1 = (float)ADC_Value[0]*3.3/4096;
	 ADC_TU_Temp2 = (float)ADC_Value[1]*3.3/4096;
	 PH = -5.7541*ADC_PH_Temp1+16.654;
	if(PH<=0.0)
      {
		  PH=0.0;
	  }
	if(PH>=14.0)
      {
	      PH=14.0;
	  }
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
printf("{\"zhuo\":%.2f,\"temperature\":%.2f,\"NH3\":%.2f,\"O2\":%.2f,\"pH\":%.2f}"
		,TU,tem/10,O2,PH);	
*/

