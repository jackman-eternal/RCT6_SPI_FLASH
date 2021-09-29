#ifndef __SPI_H
#define __SPI_H

#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"



#define DUMMY   0x00   
#define Read_id 0x9F



/*等待超时时间*/
#define SPIT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define SPIT_LONG_TIMEOUT         ((uint32_t)(10 * SPIT_FLAG_TIMEOUT))
#define FLASH_ERROR(fmt,arg...)   printf("<<-FLASH-ERROR->> "fmt"\n",##arg)

#define FLASH_CS_LOW   GPIO_ResetBits(GPIOA,GPIO_Pin_2) 
#define FLASH_CS_HIGH    GPIO_SetBits(GPIOA, GPIO_Pin_2)
void SPI1_Init(void);

uint32_t SPI_Read_ID(void);
uint8_t SPI1_Send_Byte(uint8_t data);
uint8_t SPI1_Read_Byte(void);


#endif

