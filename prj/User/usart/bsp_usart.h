/********************************************************************************************************//**
 * @file    bsp_usart.h	
 * @brief   The header file of the bsp_usart.
 * @author  Amicro
 * @version V1.00
 * @date:   2017-3-11
 * @note		
 ***************************
 *USARTx | RXD | TXD | AFx *
 ***************************
 *USART0 | PA13| PA14| AF4 *->USARTO_1
 *USART0 | PC8 | PC9 | AF4 *->USARTO_2
 *USART0 | PC12| PC13| AF4 *->USARTO_3
 ***************************
 *USART1 | PD6 | PD7 | AF4 *->USART1_1
 ***************************
 *USART2 | PA3 | PA2 | AF4 *->USART2_1
 *USART2 | PA5 | PA4 | AF4 *->USART2_2
 ***************************
 *USART3 | PB15| PB13| AF4 *->USART3_1 //USART3_1 禁止使用，该IO用于JTAG之SWD调试接口
 ***************************
 *USART4 | PC6 | PC7 | AF4 *->USART4_1
 ***************************
 *USART5 | PD3 | PD4 | AF4 *->USART5_1
 ***************************
 * Copyright (C) 2017 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
#ifndef __BSP_USART_H
#define __BSP_USART_H
#include "AM8813.h"
#include "usart.h"
#include "AM8813_misc.h"
#include "gpio.h"
#include "stdio.h"

#define USART_Debug							AM_UART4
//#define BSP_USART0_BAUDRATE		9600  	//串口波特率
//#define BSP_USART1_BAUDRATE		9600  	//串口波特率
//#define BSP_USART2_BAUDRATE		9600  	//串口波特率
//#define BSP_USART3_BAUDRATE		9600  	//串口波特率  //USART3_1 禁止使用，该IO用于JTAG之SWD调试接口
#define BSP_USART4_BAUDRATE			115200  //串口波特率
//#define BSP_USART5_BAUDRATE		9600  	//串口波特率

#if defined (BSP_USART0_BAUDRATE) 
	#define BSP_USART0_WordLength		USART_WORDLENGTH_8B
	#define BSP_USART0_Mode					USART_MODE_NORMAL
	#define BSP_USART0_Parity				USART_PARITY_NO
	#define BSP_USART0_StopBits			USART_STOPBITS_1
#endif

#if defined (BSP_USART1_BAUDRATE) 
	#define BSP_USART1_WordLength		USART_WORDLENGTH_8B
	#define BSP_USART1_Mode					USART_MODE_NORMAL
	#define BSP_USART1_Parity				USART_PARITY_NO
	#define BSP_USART1_StopBits			USART_STOPBITS_1
#endif

#if defined (BSP_USART2_BAUDRATE) 
	#define BSP_USART2_WordLength		USART_WORDLENGTH_8B
	#define BSP_USART2_Mode					USART_MODE_NORMAL
	#define BSP_USART2_Parity				USART_PARITY_NO
	#define BSP_USART2_StopBits			USART_STOPBITS_1
#endif

#if defined (BSP_USART3_BAUDRATE) 
	#define BSP_USART3_WordLength		USART_WORDLENGTH_8B
	#define BSP_USART3_Mode					USART_MODE_NORMAL
	#define BSP_USART3_Parity				USART_PARITY_NO
	#define BSP_USART3_StopBits			USART_STOPBITS_1
#endif

#if defined (BSP_USART4_BAUDRATE) 
	#define BSP_USART4_WordLength		USART_WORDLENGTH_8B
	#define BSP_USART4_Mode					USART_MODE_NORMAL
	#define BSP_USART4_Parity				USART_PARITY_NO
	#define BSP_USART4_StopBits			USART_STOPBITS_1
#endif

#if defined (BSP_USART5_BAUDRATE) 
	#define BSP_USART5_WordLength		USART_WORDLENGTH_8B
	#define BSP_USART5_Mode					USART_MODE_NORMAL
	#define BSP_USART5_Parity				USART_PARITY_NO
	#define BSP_USART5_StopBits			USART_STOPBITS_1
#endif

static void NVIC_Configuration(void);
void USARTx_Config(void);
void Usart_SendByte( AM_USART_TypeDef * pBSP_USART, uint8_t ch);
void Usart_SendHalfWord( AM_USART_TypeDef * pBSP_USART, uint16_t ch);
void Usart_SendString( AM_USART_TypeDef * pBSP_USART, char *str);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);

#endif /* __BSP_USART_H */
