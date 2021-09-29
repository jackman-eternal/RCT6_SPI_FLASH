/*
SPI1 NSS  PA4 推挽
     SCK  PA5 复用
	 MOSI PA7 复用
	 MISO PA6 浮空
 
*/
#include "spi.h"
////超时检测
//static __IO uint32_t SPITimeout = SPIT_FLAG_TIMEOUT;
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
	
	SPI1_Config.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2 ;//2分频
	SPI1_Config.SPI_CPHA = SPI_CPHA_2Edge ;
	SPI1_Config.SPI_CPOL = SPI_CPOL_High  ;
	SPI1_Config.SPI_DataSize = SPI_DataSize_8b ;
	SPI1_Config.SPI_CRCPolynomial = 0;//不使用
	SPI1_Config.SPI_Direction = SPI_Direction_2Lines_FullDuplex ;
	SPI1_Config.SPI_Mode = SPI_Mode_Master ;
	SPI1_Config.SPI_NSS = SPI_NSS_Soft ;
	SPI1_Config.SPI_FirstBit  = SPI_FirstBit_MSB ;
	
	SPI_Init(SPI1,&SPI1_Config);
    SPI_Cmd(SPI1,ENABLE);
 	
	
}

//发送一个字节
uint8_t SPI1_Send_Byte(uint8_t data)
{  
	//TXE为1时(发送缓存器已空)，等到空就可以发数据，跳过while
	while(SPI_I2S_GetFlagStatus(SPI1 ,SPI_I2S_FLAG_TXE ) ==RESET );
//	{
//		//防止卡死，进行超时检测
//		 SPITimeout--
//		if(SPITimeout == 0)
//		{
//		  return SPI_TIMEOUT_UserCallback(0);
//		}
//	}
//	
	SPI_I2S_SendData(SPI1 ,data) ;//数据寄存器写入数据
	//如何确认发送完毕,等待接收缓存器非空，则数据发送完成，此时读取数据寄存器
	while(SPI_I2S_GetFlagStatus(SPI1 ,SPI_I2S_FLAG_RXNE )==RESET  );
	return SPI_I2S_ReceiveData(SPI1 ); 
}

//static uint32_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
//{
//	FLASH_ER
//}

uint8_t SPI1_Read_Byte(void)
{     
	return SPI1_Send_Byte(DUMMY); 
}
/*
函数：读芯片的ID号
从机返回3个字节，定义为32位的变量
*/


uint32_t SPI_Read_ID(void)
{
	uint32_t Flash_ID;
    FLASH_CS_LOW ;//片选使能
	SPI1_Send_Byte(Read_id);//发送命令代码
	Flash_ID = SPI1_Send_Byte(DUMMY)<<16;
	Flash_ID |= SPI1_Send_Byte(DUMMY)<<8;
	Flash_ID |= SPI1_Send_Byte(DUMMY);
	
	FLASH_CS_HIGH ;	
	return Flash_ID  ;
}



