/********************************************************************************************************//**
 * @file    exception.c
 * @brief   This file provides exceptioon function relative to vector table.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
 
#include "exception.h"  
#include "AM8813.h"
#include "user.h"
#include "AM8813_misc.h"
#include "ui-ir.h"
#include "ckcu.h"

extern void SystemCoreClockUpdate(void);

void NMI_Handler(void)
{
  NMI_Handler_IRQ();
}

void HardFault_Handler(void)
{
  while (1);
}

void SVC_Handler(void)
{
	while (1);
}

void DebugMon_Handler(void)
{
	while (1);
}

void PendSV_Handler(void)
{
	while (1);
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	SystemCoreClockUpdate();
}

void CKRDY_IRQHandler(void)
{
	CKRDY_IRQHandler_IRQ();
}

void LVD_IRQHandler(void)
{
	while (1);
}

void WDT_IRQHandler(void)
{
	while (1);
}

void RTC_IRQHandler(void)
{
	while (1);
}

void FLASH_IRQHandler(void)
{
	while (1);
}

void EVWUP_IRQHandler(void)
{
	while (1);
}

void LPWUP_POR_IRQHandler(void)
{
	while (1);
}

void EXTI0_1_2_3_IRQHandler(void)
{
	while (1);
}

void EXTI4_5_6_7_IRQHandler(void)
{
	while (1);
}

void EXTI8_9_10_11_IRQHandler(void)
{
	while (1);
}

void EXTI12_13_14_15_IRQHandler(void)
{
	while (1);
}

void ADC_IRQHandler(void)
{
	while (1);
}

extern U8 ir_rec(IR_POSITION position);
extern void ir_rx_capture_4khz(void);
extern void ir_rx_decode(void);
void GPTM0_IRQHandler(void)
{
	if(GPTM_GetFlagStatus(AM_GPTM0, GPTM_FLAG_CH0CC)==SET)
	{
	//	if(GPIO_ReadInBit(AM_GPIOB,GPIO_PIN_5)==RESET)
//		if(!(ir_rec(AM_IO_IR_REC_MIDDLE)))
//	//	LED_Toggle(GREEN);
//	  LED2_GPIO_PORT->RR = LED2_PIN;   //DebugÖ¸Ê¾LEDµÆ
//		else
//		LED2_GPIO_PORT->SRR = LED2_PIN;
		ir_rx_capture_4khz();
		GPTM_ClearFlag(AM_GPTM0, GPTM_FLAG_CH0CC);
	}
}

void GPTM1_IRQHandler(void)
{
  if(GPTM_GetFlagStatus(AM_GPTM1, GPTM_FLAG_CH1CC)==SET)
	{
		ir_rx_decode();
		GPTM_ClearFlag(AM_GPTM1, GPTM_FLAG_CH1CC);
	}
}

void GPTM2_IRQHandler(void)
{
	while (1);
}

void GPTM3_IRQHandler(void)
{
	while (1);
}

void I2C0_IRQHandler(void)
{
	while (1);
}

void SPI0_SPI1_IRQHandler(void)
{
	while (1);
}

void UART0_IRQHandler(void)
{
	while (1);	
}

void UART1_IRQHandler(void)
{
	while (1);	
}

void UART2_IRQHandler(void)
{
	while (1);
}

void UART3_IRQHandler(void)
{
	while (1);
}

void UART4_IRQHandler(void)
{
//uint8_t ucTemp;
	if(USART_GetLineStatus(AM_UART4, USART_LSR_RFDR) != RESET)
	{
		USART_SendData(AM_UART4,USART_ReceiveData(AM_UART4));
		//if(ucTemp == 'A')
			//while (1);
	}
}

void UART5_IRQHandler(void)
{
	while (1);
}

void PDMA_CH0_IRQHandler(void)
{
	while (1);
}

void PDMA_CH1_IRQHandler(void)
{
	while (1);
}

void PDMA_CH2_IRQHandler(void)
{
	while (1);
}

void PDMA_CH3_IRQHandler(void)
{
	while (1);
}

void PDMA_CH4_CH5IRQHandler(void)
{
	while (1);
}

void PDMA_CH6_CH7_IRQHandler(void)
{
	while (1);
}

void COMP_IRQHandler(void)
{
	while (1);
}

void CAN_IRQHandler(void)
{
	while (1);
}

