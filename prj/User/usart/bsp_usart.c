/********************************************************************************************************//**
 * @file    bsp_usart.c
 * @brief   Usart Driver
 * @author  Amicro
 * @version V1.00
 * @date:   2017-3-21
 * @note		USARTx_Config();
 *					Usart_SendByte(AM_UARTx,y); ... x can be 0-5 ... y can be a 8bit uint8 ...
 *					Usart_SendHalfWord(AM_UARTx,y); ... x can be 0-5 ... y can be a 16bit uint16 ...
 *					Usart_SendString(AM_UARTx,y); ... x can be 0-5 ... y can be a data array ...
 *					Printf(x); ... x can be a data array with variable,which can be several parameters alone with x ...
 * @Pin
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
#include "bsp_usart.h"

static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
#if defined (BSP_USART0_BAUDRATE) 
	NVIC_InitStructure.NVIC_IRQChannel = UART0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
#endif

#if defined (BSP_USART1_BAUDRATE) 
	NVIC_InitStructure.NVIC_IRQChannel = UART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
#endif	

#if defined (BSP_USART2_BAUDRATE) 
	NVIC_InitStructure.NVIC_IRQChannel = UART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
#endif	

#if defined (BSP_USART3_BAUDRATE) 
	NVIC_InitStructure.NVIC_IRQChannel = UART3_IRQn;  //USART3_1 禁止使用，该IO用于JTAG之SWD调试接口
	NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
	NVIC_Init(&NVIC_InitStructure);
#endif

#if defined (BSP_USART4_BAUDRATE) 
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
	NVIC_Init(&NVIC_InitStructure);
#endif

#if defined (BSP_USART5_BAUDRATE) 
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
	NVIC_Init(&NVIC_InitStructure);
#endif

}

void USARTx_Config(void)
{
	USART_InitTypeDef USART_InitStructure;
#if defined (BSP_USART0_BAUDRATE) 
	USART_DeInit(AM_UART0);
//AFIO_GPAConfig(AFIO_PIN_13,AFIO_MODE_4);
//AFIO_GPAConfig(AFIO_PIN_14,AFIO_MODE_4); //USARTO_1
	AFIO_GPCConfig(AFIO_PIN_8 ,AFIO_MODE_4);
	AFIO_GPCConfig(AFIO_PIN_9 ,AFIO_MODE_4); //USARTO_2
//AFIO_GPCConfig(AFIO_PIN_12,AFIO_MODE_4);
//AFIO_GPCConfig(AFIO_PIN_13,AFIO_MODE_4); //USARTO_3
	USART_InitStructure.USART_WordLength=BSP_USART0_WordLength;
	USART_InitStructure.USART_Mode=BSP_USART0_Mode;
	USART_InitStructure.USART_Parity=BSP_USART0_Parity;
	USART_InitStructure.USART_StopBits=BSP_USART0_StopBits;
	USART_InitStructure.USART_BaudRate=BSP_USART0_BAUDRATE;
	USART_Init(AM_UART0,&USART_InitStructure);
	
	USART_IntConfig(AM_UART0,USART_IER_RDAIE,ENABLE);
	USART_TxCmd(AM_UART0,ENABLE);
	USART_RxCmd(AM_UART0,ENABLE);
#endif
#if defined (BSP_USART1_BAUDRATE) 
	USART_DeInit(AM_UART1);
	AFIO_GPDConfig(AFIO_PIN_6 ,AFIO_MODE_4);
	AFIO_GPDConfig(AFIO_PIN_7 ,AFIO_MODE_4); //USART1_1
	USART_InitStructure.USART_WordLength=BSP_USART1_WordLength;
	USART_InitStructure.USART_Mode=BSP_USART1_Mode;
	USART_InitStructure.USART_Parity=BSP_USART1_Parity;
	USART_InitStructure.USART_StopBits=BSP_USART1_StopBits;
	USART_InitStructure.USART_BaudRate=BSP_USART1_BAUDRATE;
	USART_Init(AM_UART1,&USART_InitStructure);
	
	USART_IntConfig(AM_UART1,USART_IER_RDAIE,ENABLE);
	USART_TxCmd(AM_UART1,ENABLE);
	USART_RxCmd(AM_UART1,ENABLE);
#endif
#if defined (BSP_USART2_BAUDRATE) 
	USART_DeInit(AM_UART2);
	AFIO_GPAConfig(AFIO_PIN_3 ,AFIO_MODE_4);
	AFIO_GPAConfig(AFIO_PIN_2 ,AFIO_MODE_4); //USART2_1
//AFIO_GPAConfig(AFIO_PIN_5 ,AFIO_MODE_4);
//AFIO_GPAConfig(AFIO_PIN_4 ,AFIO_MODE_4); //USART2_2
	USART_InitStructure.USART_WordLength=BSP_USART2_WordLength;
	USART_InitStructure.USART_Mode=BSP_USART2_Mode;
	USART_InitStructure.USART_Parity=BSP_USART2_Parity;
	USART_InitStructure.USART_StopBits=BSP_USART2_StopBits;
	USART_InitStructure.USART_BaudRate=BSP_USART2_BAUDRATE;
	USART_Init(AM_UART2,&USART_InitStructure);
	
	USART_IntConfig(AM_UART2,USART_IER_RDAIE,ENABLE);
	USART_TxCmd(AM_UART2,ENABLE);
	USART_RxCmd(AM_UART2,ENABLE);
#endif
#if defined (BSP_USART3_BAUDRATE) 
	USART_DeInit(AM_UART3);//USART3_1 禁止使用，该IO用于JTAG之SWD调试接口
	AFIO_GPBConfig(AFIO_PIN_15,AFIO_MODE_4);
	AFIO_GPBConfig(AFIO_PIN_13,AFIO_MODE_4); //USART3_1 禁止使用，该IO用于JTAG之SWD调试接口
	USART_InitStructure.USART_WordLength=BSP_USART3_WordLength;
	USART_InitStructure.USART_Mode=BSP_USART3_Mode;
	USART_InitStructure.USART_Parity=BSP_USART3_Parity;
	USART_InitStructure.USART_StopBits=BSP_USART3_StopBits;
	USART_InitStructure.USART_BaudRate=BSP_USART3_BAUDRATE;
	USART_Init(AM_UART3,&USART_InitStructure);
	
	USART_IntConfig(AM_UART3,USART_IER_RDAIE,ENABLE);
	USART_TxCmd(AM_UART3,ENABLE);
	USART_RxCmd(AM_UART3,ENABLE);
#endif
#if defined (BSP_USART4_BAUDRATE) 
	USART_DeInit(AM_UART4);
	AFIO_GPCConfig(AFIO_PIN_6 ,AFIO_MODE_4);
	AFIO_GPCConfig(AFIO_PIN_7 ,AFIO_MODE_4); //USART4_1
	USART_InitStructure.USART_WordLength=BSP_USART4_WordLength;
	USART_InitStructure.USART_Mode=BSP_USART4_Mode;
	USART_InitStructure.USART_Parity=BSP_USART4_Parity;
	USART_InitStructure.USART_StopBits=BSP_USART4_StopBits;
	USART_InitStructure.USART_BaudRate=BSP_USART4_BAUDRATE;
	USART_Init(AM_UART4,&USART_InitStructure);
	
	USART_IntConfig(AM_UART4,USART_IER_RDAIE,ENABLE);
	USART_TxCmd(AM_UART4,ENABLE);
	USART_RxCmd(AM_UART4,ENABLE);
#endif
#if defined (BSP_USART5_BAUDRATE) 
	USART_DeInit(AM_UART5);
	AFIO_GPDConfig(AFIO_PIN_3 ,AFIO_MODE_4);
	AFIO_GPDConfig(AFIO_PIN_4 ,AFIO_MODE_4); //USART5_1
	USART_InitStructure.USART_WordLength=BSP_USART5_WordLength;
	USART_InitStructure.USART_Mode=BSP_USART5_Mode;
	USART_InitStructure.USART_Parity=BSP_USART5_Parity;
	USART_InitStructure.USART_StopBits=BSP_USART5_StopBits;
	USART_InitStructure.USART_BaudRate=BSP_USART5_BAUDRATE;
	USART_Init(AM_UART5,&USART_InitStructure);
	
	USART_IntConfig(AM_UART5,USART_IER_RDAIE,ENABLE);
	USART_TxCmd(AM_UART5,ENABLE);
	USART_RxCmd(AM_UART5,ENABLE); 
#endif
	
	NVIC_Configuration();
}

/**
 * @brief  USARTx发送一个字符 Byte
 */
void Usart_SendByte( AM_USART_TypeDef * pBSP_USART, uint8_t ch)
{
	USART_SendData(pBSP_USART,ch);  //发送一个字节数据到USART
	while (USART_GetLineStatus(pBSP_USART, USART_LSR_TE) == RESET);  	//等待发送数据寄存器为空
}

/**
 * @brief  USARTx发送一个16位数,先发送高八位，再发送低八位
 */
void Usart_SendHalfWord( AM_USART_TypeDef * pBSP_USART, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	temp_h = (ch&0XFF00)>>8;  //取出高八位
	temp_l = ch&0XFF;  				//取出低八位

	USART_SendData(pBSP_USART,temp_h);	  //发送高八位
	while (USART_GetLineStatus(pBSP_USART, USART_LSR_TE) == RESET);  	//等待高八位发送完成

	USART_SendData(pBSP_USART,temp_l);	  //发送低八位
	while (USART_GetLineStatus(pBSP_USART, USART_LSR_TE) == RESET);		//等待低八位发送完成
}

/**
 * @brief  USARTx发送字符串
 */
void Usart_SendString( AM_USART_TypeDef * pBSP_USART, char *str)
{
	unsigned int k=0;
	do 
	{
		Usart_SendByte( pBSP_USART,*(str + k));
		k++;
	}while(*(str + k)!='\0');
	while (USART_GetLineStatus(pBSP_USART, USART_LSR_TE) == RESET);	  //等待发送完成
}

/**
 * @brief  重定向c库函数printf到串口，重定向后可使用printf函数
 */
int fputc(int ch, FILE *f)
{
	USART_SendData(USART_Debug, (uint8_t) ch);  //发送一个字节数据到串口
	while (USART_GetLineStatus(USART_Debug, USART_LSR_TE) == RESET);  //等待发送完毕
	return (ch);
}

/**
 * @brief  重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
 */
int fgetc(FILE *f)
{
		while (USART_GetLineStatus(USART_Debug, USART_LSR_RFDR) == RESET); //等待串口输入数据
		return (int)USART_ReceiveData(USART_Debug);
}


