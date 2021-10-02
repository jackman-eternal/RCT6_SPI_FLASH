/*
SPI1 CS   PA2 推挽
     SCK  PA5 复用
	 MOSI PA7 复用
	 MISO PA6 浮空
 
*/
#include "spi.h"


static __IO uint32_t  SPITimeout = SPIT_LONG_TIMEOUT;    
static uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);//超时检测

/*

功能：
输入：
输出：
*/

/*
void SPI1_Init(void);
功能：SPI1初始化配置
输入：
输出：
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

/*
uint8_t SPI1_Send_Byte(uint8_t data);
功能：向从机写一个字节
输入：一个字节的数据
输出：一个字节的数据
*/
uint8_t SPI1_Send_Byte(uint8_t data)
{  
	 SPITimeout = SPIT_FLAG_TIMEOUT;
	//TXE为1时(发送缓存器已空)，等到空就可以发数据，跳过while
	while(SPI_I2S_GetFlagStatus(SPI1 ,SPI_I2S_FLAG_TXE ) == RESET);
	{
		if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(0);
		//超时检查
	}
	
	SPI_I2S_SendData(SPI1 ,data) ;//数据寄存器写入数据
	SPITimeout = SPIT_FLAG_TIMEOUT;
	//如何确认发送完毕,等待接收缓存器非空，则数据发送完成，此时读取数据寄存器
	while(SPI_I2S_GetFlagStatus(SPI1 ,SPI_I2S_FLAG_RXNE )==RESET  )
	{
		 if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(1);
	}
	return SPI_I2S_ReceiveData(SPI1 ); 
}

/*
uint8_t SPI1_Read_Byte(void);
功能：读取主机发来的数据
输入：无
输出：一个字节的数据
*/
uint8_t SPI1_Read_Byte(void)
{     
	//注：这个函数用得不多
	return SPI1_Send_Byte(DUMMY); 
}

/*
uint32_t SPI_Read_ID(void);
功能：读芯片的ID号
输入：无
输出：返回3个字节的ID号
*/
uint32_t SPI_Read_ID(void)
{
	uint32_t Flash_ID;
    FLASH_CS_LOW ;  //片选使能
	SPI1_Send_Byte(Read_id);//发送命令代码
	Flash_ID = SPI1_Send_Byte(DUMMY)<<16;
	Flash_ID |= SPI1_Send_Byte(DUMMY)<<8;
	Flash_ID |= SPI1_Send_Byte(DUMMY);
	FLASH_CS_HIGH ; //停止信号	
	
	return Flash_ID  ;
	
}

static  uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
  /* 等待超时后的处理,输出错误信息 */
  FLASH_ERROR("SPI 等待超时!errorCode = %d",errorCode);
  return 0;
}

/*
void SPI_Erase_Sector(uint32_t addr);
功能：擦除FLASH的指定扇区(擦除和写入时需要内部时间的)
输入：3个字节的地址
输出：无
*/
void SPI_Erase_Sector(uint32_t addr)
{
	FLASH_CS_LOW ; //片选使能
	
	SPI1_Send_Byte(ERASE_SECTOR);
	//发送地址从高位到低位
	SPI1_Send_Byte((addr>>16)&0xff);
	SPI1_Send_Byte((addr>>8)&0xff);
	SPI1_Send_Byte(addr&0xff);
	
	FLASH_CS_HIGH ; //停止信号	
}
/*
void SPI_WaitForWriteEnd(void);
功能:等待擦除或者写入的指令完成,busy为1代表忙碌
输入：无
输出：无
*/
void SPI_WaitForWriteEnd(void)
{
	uint8_t status_res =0;
	
	FLASH_CS_LOW ; //片选使能
	SPI1_Send_Byte(READ_STATUS);	
	do
	{
	 status_res = SPI1_Send_Byte(0x00);
     //为1 忙碌
	}while((status_res & 0x01)==1);	
	FLASH_CS_HIGH ; //停止信号
}

