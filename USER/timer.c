#include "timer.h"

/*
TIM2 CH1--PA0 CH2--PA1  CH3--PA2  CH4--PA3  
     /REMAP->1--PA15  2--PB3  3--PB10  4--PB11
TIM3 CH1--PA6 CH2--PA7  CH3--PB0  CH4--PB1  
     /REMAP->1--PC6  2--PC7  3--PC8  4--PC9
TIM4 CH1--PB6 CH2--PB7  CH3--PB8  CH4--PB9  
     /REMAP->1--PD12  2--PD13  3--PD14   4--PD15
TIM5 CH1--PA0 CH2--PA1  CH3--PA2  CH4--PA3 
*/


void TIM3_INIT(void)
{
	GPIO_InitTypeDef        GPIO_TIM3;
	TIM_TimeBaseInitTypeDef TIM3_TIMEBASE;
	TIM_OCInitTypeDef       TIM3_OCINIT;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    
    GPIO_TIM3.GPIO_Mode =GPIO_Mode_AF_PP;
    GPIO_TIM3.GPIO_Pin =GPIO_Pin_6 |GPIO_Pin_7 ;
	GPIO_TIM3.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA ,&GPIO_TIM3);
    GPIO_TIM3.GPIO_Mode =GPIO_Mode_AF_PP;
    GPIO_TIM3.GPIO_Pin =GPIO_Pin_0 |GPIO_Pin_1 ;
    GPIO_Init(GPIOB,&GPIO_TIM3);	
	
	TIM3_TIMEBASE.TIM_ClockDivision =0;
	TIM3_TIMEBASE.TIM_CounterMode =TIM_CounterMode_Up ;
	TIM3_TIMEBASE.TIM_Period = 250-1;
	TIM3_TIMEBASE.TIM_Prescaler=7200-1;
	TIM_TimeBaseInit(TIM3,&TIM3_TIMEBASE);
	
	TIM3_OCINIT.TIM_OCMode = TIM_OCMode_PWM1;
	TIM3_OCINIT.TIM_OCPolarity =TIM_OCPolarity_High ;
	
	TIM3_OCINIT.TIM_Pulse = 125;
	TIM_OC1PreloadConfig(TIM3 ,TIM_OCPreload_Enable);
    TIM3_OCINIT.TIM_OutputState =ENABLE ;
    TIM_OC1Init(TIM3,&TIM3_OCINIT);
	
    TIM3_OCINIT.TIM_Pulse =80 ;
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable );
    TIM3_OCINIT.TIM_OutputState =ENABLE ;
    TIM_OC2Init(TIM3,&TIM3_OCINIT);

	TIM3_OCINIT.TIM_Pulse =80;
	TIM3_OCINIT.TIM_OutputState =ENABLE ;
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC3Init(TIM3,& TIM3_OCINIT);

	TIM3_OCINIT.TIM_Pulse =80;
	TIM3_OCINIT.TIM_OutputState=ENABLE ;
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable); 
	TIM_OC4Init(TIM3,& TIM3_OCINIT);
   
    TIM_Cmd(TIM3 ,ENABLE );   
}

void Encoder_Init_TIM2(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//ʹ�ܶ�ʱ��4��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��PB�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // Ԥ��Ƶ�� 
  TIM_TimeBaseStructure.TIM_Period = 65535; //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM���ϼ���  
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 10;
  TIM_ICInit(TIM2, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  //Reset counter
  TIM_SetCounter(TIM2,0);
  TIM_Cmd(TIM2, ENABLE); 
}


void Encoder_Init_TIM4(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//ʹ�ܶ�ʱ��4��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��PB�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // Ԥ��Ƶ�� 
  TIM_TimeBaseStructure.TIM_Period = 65535; //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM���ϼ���  
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 10;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
  //Reset counter
  TIM_SetCounter(TIM4,0);
  TIM_Cmd(TIM4, ENABLE); 
}

int Read_Encoder(u8 TIMX)
{
    int Encoder_TIM;    
   switch(TIMX)
	 {
	     case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;
		 case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;	
		 case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;	
		 default:  Encoder_TIM=0;
	 }
		return Encoder_TIM;
}


/**************************************************************************
�������ܣ�TIM4�жϷ�����
��ڲ�������
����  ֵ����
**************************************************************************/
void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM4->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM4->SR&=~(1<<0);//����жϱ�־λ 	    
}
/**************************************************************************
�������ܣ�TIM2�жϷ�����
��ڲ�������
����  ֵ����
**************************************************************************/
void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001)//����ж�
	{    				   				     	    	
	}				   
	TIM2->SR&=~(1<<0);//����жϱ�־λ 	    
}

void TIM5_Updata(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimBaseStructrue;
	NVIC_InitTypeDef        NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE );
    
    NVIC_InitStructure.NVIC_IRQChannel =TIM5_IRQn;     //����6�ж�        
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռʽ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//�ж�ʹ��
	NVIC_Init(&NVIC_InitStructure);//�жϳ�ʼ��
	
	TIM_TimBaseStructrue.TIM_Period=1000-1;//��ʱ���� �����ж�ʱ�䣺5ms�ж�һ��
	TIM_TimBaseStructrue.TIM_Prescaler=360-1;
	TIM_TimBaseStructrue.TIM_CounterMode=TIM_CounterMode_Up;  //���ϼ���
	TIM_TimBaseStructrue.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM5,&TIM_TimBaseStructrue);
	
	TIM_ClearFlag(TIM5,TIM_FLAG_Update);
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);
	TIM_ClearFlag(TIM5, TIM_FLAG_Update);
    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE); 	
	TIM_Cmd(TIM5, ENABLE);  	
}


/*
void TIM2_ENCODER(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM2_TIMEBASE;
	TIM_ICInitTypeDef  TIM2_ICINIT;
	GPIO_InitTypeDef TIM2_GPIO;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 ,ENABLE );
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE );

	TIM2_GPIO.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
	TIM2_GPIO.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 ;
	GPIO_Init(GPIOA ,&TIM2_GPIO);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
    TIM2_TIMEBASE.TIM_Prescaler =0;
	TIM2_TIMEBASE.TIM_Period =0xffff;
	TIM2_TIMEBASE.TIM_ClockDivision =TIM_CKD_DIV1 ;
	TIM2_TIMEBASE.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInit(TIM2,&TIM2_TIMEBASE);
    
    TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12 ,TIM_ICPolarity_BothEdge ,TIM_ICPolarity_BothEdge);

    TIM2_ICINIT.TIM_Channel = TIM_Channel_1  ;	
    TIM2_ICINIT.TIM_ICFilter = 0X06;
    TIM2_ICINIT.TIM_ICPolarity = TIM_ICPolarity_BothEdge ;
	TIM2_ICINIT.TIM_ICPrescaler = TIM_ICPSC_DIV1 ;
    TIM2_ICINIT.TIM_ICSelection = TIM_ICSelection_DirectTI ;
   	TIM_ICInit(TIM2 ,&TIM2_ICINIT);
	TIM_SetCounter(TIM2,0); 
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2,ENABLE ); 
}

void TIM4_ENCODER(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//ʹ�ܶ�ʱ��4��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��PB�˿�ʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
  NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
		
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // Ԥ��Ƶ�� 
  TIM_TimeBaseStructure.TIM_Period = 0xffff; //�趨�������Զ���װֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge);//ʹ�ñ�����ģʽ3
  
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 ;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge ;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI ;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 
  TIM_ICInitStructure.TIM_ICFilter = 0x06;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
  TIM_SetCounter(TIM4,0);
  TIM_Cmd(TIM4, ENABLE); 
}

//TIM3 CH1--PA6 CH2--PA7  CH3--PB0  CH4--PB1 
void TIM3_INIT(void)
{
	GPIO_InitTypeDef        GPIO_TIM3;
	TIM_TimeBaseInitTypeDef TIM3_TIMEBASE;
	TIM_OCInitTypeDef       TIM3_OCINIT;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    
    GPIO_TIM3.GPIO_Mode =GPIO_Mode_AF_PP;
    GPIO_TIM3.GPIO_Pin =GPIO_Pin_6 |GPIO_Pin_7 ;
	GPIO_TIM3.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA ,&GPIO_TIM3);
    GPIO_TIM3.GPIO_Mode =GPIO_Mode_AF_PP;
    GPIO_TIM3.GPIO_Pin =GPIO_Pin_0 |GPIO_Pin_1 ;
    GPIO_Init(GPIOB,&GPIO_TIM3);	
	
	TIM3_TIMEBASE.TIM_ClockDivision =0;
	TIM3_TIMEBASE.TIM_CounterMode =TIM_CounterMode_Up ;
	TIM3_TIMEBASE.TIM_Period = 250-1;
	TIM3_TIMEBASE.TIM_Prescaler=720-1;
	TIM_TimeBaseInit(TIM3,&TIM3_TIMEBASE);
	
	TIM3_OCINIT.TIM_OCMode = TIM_OCMode_PWM1;
	TIM3_OCINIT.TIM_OCPolarity =TIM_OCPolarity_High ;
	
	TIM3_OCINIT.TIM_Pulse = 125;
	TIM_OC1PreloadConfig(TIM3 ,TIM_OCPreload_Enable);
    TIM3_OCINIT.TIM_OutputState =ENABLE ;
    TIM_OC1Init(TIM3,&TIM3_OCINIT);
	
    TIM3_OCINIT.TIM_Pulse =80 ;
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable );
    TIM3_OCINIT.TIM_OutputState =ENABLE ;
    TIM_OC2Init(TIM3,&TIM3_OCINIT);

	TIM3_OCINIT.TIM_Pulse =80;
	TIM3_OCINIT.TIM_OutputState =ENABLE ;
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC3Init(TIM3,& TIM3_OCINIT);

	TIM3_OCINIT.TIM_Pulse =80;
	TIM3_OCINIT.TIM_OutputState=ENABLE ;
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable); 
	TIM_OC4Init(TIM3,& TIM3_OCINIT);
   
    TIM_Cmd(TIM3 ,ENABLE );   
}

void TIM5_Updata(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimBaseStructrue;
	NVIC_InitTypeDef        NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE );
    
    NVIC_InitStructure.NVIC_IRQChannel =TIM6_IRQn;     //����6�ж�        
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռʽ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//�ж�ʹ��
	NVIC_Init(&NVIC_InitStructure);//�жϳ�ʼ��
	
	TIM_TimBaseStructrue.TIM_Period=1000-1;//��ʱ���� �����ж�ʱ�䣺5ms�ж�һ��
	TIM_TimBaseStructrue.TIM_Prescaler=360-1;
	TIM_TimBaseStructrue.TIM_CounterMode=TIM_CounterMode_Up;  //���ϼ���
	TIM_TimBaseStructrue.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM5,&TIM_TimBaseStructrue);
	
	TIM_ClearFlag(TIM5,TIM_FLAG_Update);
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);
	TIM_ClearFlag(TIM5, TIM_FLAG_Update);
    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE); 	
	TIM_Cmd(TIM5, ENABLE);  	
}

//����2���ж��Ǽ�������������ж� ���ڳ�ʼ�����������65535�� ������ÿ��5ms�Ͷ�ȡ��һ��CNT Ȼ���ֽ�������������
//�������������ж��ǲ��ᷢ���� ������ĵ����5ms���ܹ�����>=65535/4�����õ���˫���ؼ�⣩�����塣 
void TIM2_IRQHandler(void)
{
	if(TIM2->SR&0X0001)//����ж�
	{
	}
    TIM2->SR&=~(1<<0);//����жϱ�־λ
} 

void TIM4_IRQHandler(void)
{
	if(TIM4->SR&0X0001)//����ж�
	{
	}
    TIM4->SR&=~(1<<0);//����жϱ�־λ
} 
//shortȡֵ short��(2�ֽڣ�32λϵͳ��)����ΧΪ-32768-32767
int Read_Encoder(u8 TIMX)
{
    int Encoder_TIM;    
   switch(TIMX)
	 {
	     case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;
//		 case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;	
		 case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;	
		 default: Encoder_TIM=0;
	 }
		return Encoder_TIM;
}
 
void TIM5_IRQHandler(void)								//����ʱ�䲻��̫���������������˾ͻ��������
{	
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)  
	{     
 	   printf("TIM2=%f\r\n",(float)Read_Encoder(2));//��ӡ�����1��·��	
	}	   
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
}

*/



//int velocity(int encoder_left,int encoder_right)
//{  
//      static float Velocity,Encoder_Least,Encoder,Movement;
//	  static float Encoder_Integral;
//   //=============�ٶ�PI������=======================//	
//		Encoder_Least =(Encoder_Left+Encoder_Right)-0;                    //===��ȡ�����ٶ�ƫ��==�����ٶȣ����ұ�����֮�ͣ�-Ŀ���ٶȣ��˴�Ϊ�㣩 
//		Encoder *= 0.8;		                                                //===һ�׵�ͨ�˲���       
//		Encoder += Encoder_Least*0.2;	                                    //===һ�׵�ͨ�˲���    
//		Encoder_Integral +=Encoder;                                       //===���ֳ�λ�� ����ʱ�䣺10ms
//		Encoder_Integral=Encoder_Integral-Movement;                       //===����ң�������ݣ�����ǰ������
//		if(Encoder_Integral>10000)  	Encoder_Integral=10000;             //===�����޷�
//		if(Encoder_Integral<-10000)  	Encoder_Integral=-10000;              //===�����޷�	
//		Velocity=Encoder*Velocity_Kp+Encoder_Integral*Velocity_Ki;                          //===�ٶȿ���	
////		if(Turn_Off(Angle_Balance,Voltage)==1||Flag_Stop==1)   Encoder_Integral=0;      //===����رպ��������
//	    return Velocity;
//}


//void TIM5_IRQHandler(void)						
//{	
//	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)  
//	{    
//       Encoder_Left = Read_Encoder(2);	
//	   printf("TIM2 = %d \r\n ",Encoder_Left) ;
//	}	   
//	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
//}
