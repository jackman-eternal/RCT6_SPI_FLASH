/*
SPI1 CS   PA2 ����
     SCK  PA5 ����
	 MOSI PA7 ����
	 MISO PA6 ����
 
*/
#include "spi.h"


static __IO uint32_t  SPITimeout = SPIT_LONG_TIMEOUT;    
static uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);//��ʱ���

/*

���ܣ�
���룺
�����
*/

/*
void SPI1_Init(void);
���ܣ�SPI1��ʼ������
���룺
�����
*/
void SPI1_Init(void)
{
	GPIO_InitTypeDef SPI1_GPIO;
	SPI_InitTypeDef  SPI1_Config;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1 ,ENABLE); 
	//CS
	SPI1_GPIO.GPIO_Mode = GPIO_Mode_Out_PP ;
	SPI1_GPIO.GPIO_Pin  = GPIO_Pin_2  ;
	SPI1_GPIO.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA,&SPI1_GPIO);
	GPIO_SetBits(GPIOA,GPIO_Pin_4); 
    //MOSI SCK
	SPI1_GPIO.GPIO_Mode = GPIO_Mode_AF_PP ;
	SPI1_GPIO.GPIO_Pin  = GPIO_Pin_5 | GPIO_Pin_7;
	SPI1_GPIO.GPIO_Speed  = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&SPI1_GPIO);
	//MISO
	SPI1_GPIO.GPIO_Mode  = GPIO_Mode_IN_FLOATING ;
	SPI1_GPIO.GPIO_Pin  = GPIO_Pin_6 ;
	GPIO_Init(GPIOA,&SPI1_GPIO);
	
	SPI1_Config.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2 ;//2��Ƶ
	SPI1_Config.SPI_CPHA = SPI_CPHA_2Edge ;
	SPI1_Config.SPI_CPOL = SPI_CPOL_High  ;
	SPI1_Config.SPI_DataSize = SPI_DataSize_8b ;
	SPI1_Config.SPI_CRCPolynomial = 0;//��ʹ��
	SPI1_Config.SPI_Direction = SPI_Direction_2Lines_FullDuplex ;
	SPI1_Config.SPI_Mode = SPI_Mode_Master ;
	SPI1_Config.SPI_NSS = SPI_NSS_Soft ;
	SPI1_Config.SPI_FirstBit  = SPI_FirstBit_MSB ;
	
	SPI_Init(SPI1,&SPI1_Config);
    SPI_Cmd(SPI1,ENABLE);
}

/*
uint8_t SPI1_Send_Byte(uint8_t data);
���ܣ���ӻ�дһ���ֽ�
���룺һ���ֽڵ�����
�����һ���ֽڵ�����
*/
uint8_t SPI1_Send_Byte(uint8_t data)
{  
	 SPITimeout = SPIT_FLAG_TIMEOUT;
	//TXEΪ1ʱ(���ͻ������ѿ�)���ȵ��վͿ��Է����ݣ�����while
	while(SPI_I2S_GetFlagStatus(SPI1 ,SPI_I2S_FLAG_TXE ) == RESET);
	{
		if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(0);
		//��ʱ���
	}
	
	SPI_I2S_SendData(SPI1 ,data) ;//���ݼĴ���д������
	SPITimeout = SPIT_FLAG_TIMEOUT;
	//���ȷ�Ϸ������,�ȴ����ջ������ǿգ������ݷ�����ɣ���ʱ��ȡ���ݼĴ���
	while(SPI_I2S_GetFlagStatus(SPI1 ,SPI_I2S_FLAG_RXNE )==RESET  )
	{
		 if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(1);
	}
	return SPI_I2S_ReceiveData(SPI1 ); 
}

/*
uint8_t SPI1_Read_Byte(void);
���ܣ���ȡ��������������
���룺��
�����һ���ֽڵ�����
*/
uint8_t SPI1_Read_Byte(void)
{     
	//ע����������õò���
	return SPI1_Send_Byte(DUMMY); 
}

/*
uint32_t SPI_Read_ID(void);
���ܣ���оƬ��ID��
���룺��
���������3���ֽڵ�ID��
*/
uint32_t SPI_Read_ID(void)
{
	uint32_t Flash_ID;
    FLASH_CS_LOW ;  //Ƭѡʹ��
	SPI1_Send_Byte(Read_id);//�����������
	Flash_ID = SPI1_Send_Byte(DUMMY)<<16;
	Flash_ID |= SPI1_Send_Byte(DUMMY)<<8;
	Flash_ID |= SPI1_Send_Byte(DUMMY);
	FLASH_CS_HIGH ; //ֹͣ�ź�	
	
	return Flash_ID  ;
	
}

static  uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
  /* �ȴ���ʱ��Ĵ���,���������Ϣ */
  FLASH_ERROR("SPI �ȴ���ʱ!errorCode = %d",errorCode);
  return 0;
}

/*
void SPI_Erase_Sector(uint32_t addr);
���ܣ�����FLASH��ָ������(������д��ʱ��Ҫ�ڲ�ʱ���)
���룺3���ֽڵĵ�ַ
�������
*/
void SPI_Erase_Sector(uint32_t addr)
{
	FLASH_CS_LOW ; //Ƭѡʹ��
	
	SPI1_Send_Byte(ERASE_SECTOR);
	//���͵�ַ�Ӹ�λ����λ
	SPI1_Send_Byte((addr>>16)&0xff);
	SPI1_Send_Byte((addr>>8)&0xff);
	SPI1_Send_Byte(addr&0xff);
	
	FLASH_CS_HIGH ; //ֹͣ�ź�	
}
/*
void SPI_WaitForWriteEnd(void);
����:�ȴ���������д���ָ�����,busyΪ1����æµ
���룺��
�������
*/
void SPI_WaitForWriteEnd(void)
{
	uint8_t status_res =0;
	
	FLASH_CS_LOW ; //Ƭѡʹ��
	SPI1_Send_Byte(READ_STATUS);	
	do
	{
	 status_res = SPI1_Send_Byte(0x00);
     //Ϊ1 æµ
	}while((status_res & 0x01)==1);	
	FLASH_CS_HIGH ; //ֹͣ�ź�
}

