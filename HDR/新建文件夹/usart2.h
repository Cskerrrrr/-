#ifndef __USART2_H
#define __USART2_H

#include "stm32f10x.h"
    

extern u16  USART_RX_STA;  

void USART2_Init(u32 bound);

void USART2_SendData(u8 data);

void USART2_SendString(u8 *DAT,u8 len);



#define USART_REC_LEN       200   
#define EN_USART1_RX         1      
#endif

