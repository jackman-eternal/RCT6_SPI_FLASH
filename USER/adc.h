#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"

#define TimeConstant 1                  //�˲���ʱ�䳣��
#define Ts           0.0001             //��������
//#define Factor  (1/((TimeConstant/Ts)+1)) //�˲�ϵ��
#define Factor       0.45


//extern   __IO uint32_t ADC_ConValue;
//extern   __IO uint16_t ADC_Value;  //ת���ĵ�ѹֵͨ��DMA����SRAM
extern   __IO uint16_t ADC_Value[3]; //��ͨ��ģʽ����sram�ж�����������

void ADC1_Init(void);        //��ͨ��
void ADC1_Multi_Init(void);  //��ͨ��
void ADC12_Reg_Init(void);   //˫��ADC
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
