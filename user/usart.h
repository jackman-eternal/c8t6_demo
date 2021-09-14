#ifndef __USART_H
#define __USART_H

#define THE_USARTx USART1

#include "stm32f10x.h"
#include<stdio.h>

extern u8  USART_RX_BUF[200]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
extern  int  distance;
void USART1_INIT(void);
void USART2_INIT(void);
void USART3_INIT(void);


#endif
/*
USART1_TX--PA9 ; USART1_RX--PA10
USART2_TX--PA2 ; USART2_RX--PA3
USART3_TX--PB10 ; USART3_RX--PB11
*/

