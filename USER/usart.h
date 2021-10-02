#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include "delay.h"
#include<stdio.h>
	  	
void uart_init(u32 bound);
void DMA_Config(void);
//extern uint8_t RxBuffer[8];



#endif


