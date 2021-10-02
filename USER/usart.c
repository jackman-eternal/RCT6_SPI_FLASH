#include "usart.h"	  

// uint8_t RxBuffer[8] = {0};  DMA����
// for(i=0;i<8;i++)
//	   {		
//		 printf("RxBuffer[%d] = %d \r\n",i,RxBuffer[i]);		 			 
//	   } 
  
void uart_init(u32 bound)
{
  //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
    //USART1_RX	  GPIOA.10��ʼ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  
  
	NVIC_InitStructure.NVIC_IRQChannel  = USART1_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
	NVIC_Init(&NVIC_InitStructure);
	
    //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    
	USART_ITConfig(USART1 ,USART_IT_RXNE,ENABLE ); 
    USART_Init(USART1, &USART_InitStructure);     //��ʼ������1
	USART_DMACmd(USART1 ,USART_DMAReq_Rx ,DISABLE ); 
	
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
}
/*
void DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE); //����DMAʱ��
	
	DMA_InitStructure.DMA_BufferSize = 8;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC   ;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable ;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte ;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RxBuffer;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable ;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal   ;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR); 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte ;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable ;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High ;
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  =2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority  =2;
	NVIC_Init(&NVIC_InitStructure) ;	
	
	DMA_Init(DMA1_Channel5 ,&DMA_InitStructure); 
	DMA_ITConfig(DMA1_Channel5,DMA_IT_TC,DISABLE ); 
	DMA_Cmd(DMA1_Channel5,ENABLE);
}
*/

int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {}	
   
    return ch;
}
int getc(FILE *f)
{
	/* �ȴ������������� */
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==RESET);
	/* ����ֵ����ǿ������ת�� */
	return (int)USART_ReceiveData(USART1);
}


//void DMA1_Channel5_IRQHandler(void)
//{
//	u8 i=0;
//	if(DMA_GetFlagStatus(DMA1_FLAG_TC4 )==SET )
//	{
//		for(i=0;i<8;i++)
//	   {
//		 if(RxBuffer[i]!=0)  
//		 {
//		 printf("RxBuffer[%d] = %d \r\n",i,RxBuffer[i]);
//		 }			 
//	   }
//	   DMA_ClearFlag(DMA1_FLAG_TC4); 	
//	}		
//}


void USART1_IRQHandler(void )
{
	uint8_t temp;
	if(USART_GetITStatus(USART1 ,USART_IT_RXNE )==SET  )
	{
		temp = USART_ReceiveData(USART1 );
		//printf("temp = %d \r\n ",temp);
		//USART_SendData(USART1,temp) ;
        USART_ClearITPendingBit(USART1 ,USART_IT_RXNE ); 		
	}
}



