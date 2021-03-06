#include "adc.h"

// __IO uint16_t ADC_Value;  //单通道模式，ADC数据寄存器使用低16位
  __IO uint16_t ADC_Value[3]; //多通道模式，在sram中定义两个变量
//__IO uint32_t ADC_ConValue;
/*  //单通道规则读取
void ADC1_Init(void)
{
	GPIO_InitTypeDef ADC1_GPIO;
	ADC_InitTypeDef  ADC1_Config;
	DMA_InitTypeDef  ADC1_DMA;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 |RCC_APB2Periph_GPIOA ,ENABLE );
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	ADC1_GPIO.GPIO_Mode = GPIO_Mode_AIN;
    ADC1_GPIO.GPIO_Pin = GPIO_Pin_1 ;
    GPIO_Init(GPIOA,&ADC1_GPIO);
		
	ADC1_DMA.DMA_BufferSize = 1;  
	ADC1_DMA.DMA_DIR = DMA_DIR_PeripheralSRC ; //外设为数据源
	ADC1_DMA.DMA_M2M = DMA_M2M_Disable;  
    ADC1_DMA.DMA_MemoryBaseAddr = (uint32_t)&ADC_Value;
	ADC1_DMA.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord ;//16位
	ADC1_DMA.DMA_MemoryInc  = DMA_MemoryInc_Disable ;    //内存地址固定（地址只有一个）
	ADC1_DMA.DMA_PeripheralBaseAddr = (uint32_t)(&(ADC1->DR)); 
	ADC1_DMA.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    ADC1_DMA.DMA_PeripheralInc = DMA_PeripheralInc_Disable ;  //外设地址固定（地址只有一个）
    ADC1_DMA.DMA_Priority = DMA_Priority_High ; 
    ADC1_DMA.DMA_Mode = DMA_Mode_Circular ;//循环传输	
	DMA_Init(DMA1_Channel1 ,&ADC1_DMA);
    DMA_Cmd(DMA1_Channel1,ENABLE);
	
	ADC1_Config.ADC_Mode = ADC_Mode_Independent ;
	ADC1_Config.ADC_ScanConvMode =DISABLE ;
	ADC1_Config.ADC_ContinuousConvMode  =ENABLE ;
	ADC1_Config.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ;
	ADC1_Config.ADC_DataAlign = ADC_DataAlign_Right ;
	ADC1_Config.ADC_NbrOfChannel =1;
	ADC_Init(ADC1 ,&ADC1_Config);
  
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_1 ,1,ADC_SampleTime_55Cycles5  );//55.5个采样周期
    ADC_DMACmd(ADC1 ,ENABLE );    //ADC提交DMA请求
    ADC_Cmd(ADC1 ,ENABLE );    	
     	 
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
	ADC_SoftwareStartConvCmd(ADC1,ENABLE); 	
}*/

  //多通道规则读取
void ADC1_Multi_Init(void)  //开启PA1和PA3   
{ 
	GPIO_InitTypeDef ADC1_GPIO;
	ADC_InitTypeDef  ADC1_Config;
	DMA_InitTypeDef  ADC1_DMA;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 |RCC_APB2Periph_GPIOA ,ENABLE );
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	ADC1_GPIO.GPIO_Mode = GPIO_Mode_AIN;
    ADC1_GPIO.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_3|GPIO_Pin_2  ;
    GPIO_Init(GPIOA,&ADC1_GPIO);
	
	ADC1_DMA.DMA_BufferSize = 3;  
	ADC1_DMA.DMA_DIR = DMA_DIR_PeripheralSRC ; //外设为数据源
	ADC1_DMA.DMA_M2M = DMA_M2M_Disable;  
    ADC1_DMA.DMA_MemoryBaseAddr =(uint32_t)ADC_Value ;//(uint32_t)&ADC_Value;
	ADC1_DMA.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord ;//16位
	ADC1_DMA.DMA_MemoryInc  = DMA_MemoryInc_Enable ;    //内存地址自增
	ADC1_DMA.DMA_PeripheralBaseAddr = (uint32_t)(&(ADC1->DR)); 
	ADC1_DMA.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    ADC1_DMA.DMA_PeripheralInc = DMA_PeripheralInc_Disable ;  //外设地址固定（地址只有一个）
    ADC1_DMA.DMA_Priority = DMA_Priority_High ; 
    ADC1_DMA.DMA_Mode = DMA_Mode_Circular ;//循环传输	
	DMA_Init(DMA1_Channel1 ,&ADC1_DMA);
    DMA_Cmd(DMA1_Channel1,ENABLE);
	
	ADC1_Config.ADC_Mode = ADC_Mode_Independent ;
	ADC1_Config.ADC_ScanConvMode =ENABLE ;//DISABLE ;多通道使能
	ADC1_Config.ADC_ContinuousConvMode  =ENABLE ;
	ADC1_Config.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ;
	ADC1_Config.ADC_DataAlign = ADC_DataAlign_Right ;
	ADC1_Config.ADC_NbrOfChannel =3;
	ADC_Init(ADC1,&ADC1_Config);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	//每一个通道都要设置采样顺序和时间
    ADC_RegularChannelConfig(ADC1,ADC_Channel_1 ,1,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2 ,2,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3 ,3,ADC_SampleTime_55Cycles5);
    ADC_DMACmd(ADC1 ,ENABLE );    //ADC提交DMA请求
    ADC_Cmd(ADC1 ,ENABLE );  
     
  	ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));	 
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

/*
void ADC12_Reg_Init(void)  //adc1-pa1-channel1  adc2-pa3-channel3
{
	GPIO_InitTypeDef ADC1_GPIO;
	DMA_InitTypeDef  ADC1_DMA;
	ADC_InitTypeDef  ADC1_Config;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2|RCC_APB2Periph_ADC1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	ADC1_GPIO.GPIO_Mode = GPIO_Mode_AIN;
    ADC1_GPIO.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_4 ;
    GPIO_Init(GPIOA,&ADC1_GPIO); 
	
	ADC1_DMA.DMA_BufferSize = 1;               //每个ADC用的是一个通道
	ADC1_DMA.DMA_DIR = DMA_DIR_PeripheralSRC ; //外设为数据源
	ADC1_DMA.DMA_M2M = DMA_M2M_Disable;  
    ADC1_DMA.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConValue;
	ADC1_DMA.DMA_MemoryDataSize = DMA_MemoryDataSize_Word  ;//32位
	ADC1_DMA.DMA_MemoryInc  = DMA_MemoryInc_Disable ;    //内存地址固定（地址只有一个）
	ADC1_DMA.DMA_PeripheralBaseAddr = (uint32_t)(&(ADC1->DR)); 
	ADC1_DMA.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word ;
    ADC1_DMA.DMA_PeripheralInc = DMA_PeripheralInc_Disable ;  //外设地址固定（地址只有一个）
    ADC1_DMA.DMA_Priority = DMA_Priority_High ; 
    ADC1_DMA.DMA_Mode = DMA_Mode_Circular ;//循环传输	
	DMA_Init(DMA1_Channel1 ,&ADC1_DMA);
    DMA_Cmd(DMA1_Channel1,ENABLE);
	//初始化2个ADC
	ADC1_Config.ADC_Mode = ADC_Mode_RegSimult;
	ADC1_Config.ADC_ScanConvMode =DISABLE ;//ADC多通道使能
	ADC1_Config.ADC_ContinuousConvMode =ENABLE ;
	ADC1_Config.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ;
	ADC1_Config.ADC_DataAlign = ADC_DataAlign_Right ;
	ADC1_Config.ADC_NbrOfChannel =1;
	ADC_Init(ADC1,&ADC1_Config);
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	ADC_RegularChannelConfig(ADC1 ,ADC_Channel_1,1,ADC_SampleTime_55Cycles5); 
	ADC_DMACmd(ADC1,ENABLE);
     
    //ADC2
    ADC1_Config.ADC_Mode = ADC_Mode_RegSimult; //同步规则
	ADC1_Config.ADC_ScanConvMode =DISABLE ;//关闭扫描模式
	ADC1_Config.ADC_ContinuousConvMode =ENABLE ;//连续转换模式
	ADC1_Config.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ;
	ADC1_Config.ADC_DataAlign = ADC_DataAlign_Right ;
	ADC1_Config.ADC_NbrOfChannel =1;
	ADC_Init(ADC2,&ADC1_Config);
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);	

    ADC_RegularChannelConfig(ADC2,ADC_Channel_4,1,ADC_SampleTime_55Cycles5);
    
    //adc_calibration
    ADC_Cmd(ADC1,ENABLE);
	
	ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));	
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
    ADC_Cmd(ADC2,ENABLE);
	ADC_ResetCalibration(ADC2);
    while(ADC_GetResetCalibrationStatus(ADC2));	
    ADC_StartCalibration(ADC2);
    while(ADC_GetCalibrationStatus(ADC2));
    
 	ADC_SoftwareStartConvCmd(ADC1,ENABLE); //ADC1是主(由软件触发)，ADC2是从（adc的多路复用触发器来）     	
	ADC_ExternalTrigConvCmd(ADC2,ENABLE ); 
}
//	   Value1 = (ADC_ConValue&0xffff0000)>>16;//取出高16位
//     Value2 = (ADC_ConValue&0x0000ffff);	  //取出低16位
//	   ADC_Value_Temp1 = (float)Value1*3.3/4096;
//	   ADC_Value_Temp2 = (float)Value2*3.3/4096;
*/
