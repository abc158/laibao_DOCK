/********************************************************************************************************//**
 * @file    ckcu.h	
 * @brief   The header file of the Clock Control Unit library.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/

#ifndef _CKCU_H
#define _CKCU_H

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "AM8813.h"

typedef enum
{
  CKCU_LCDSRC_LSI = 0,
  CKCU_LCDSRC_LSE
} CKCU_LCDSRC_TypeDef;


/* Definitions of APB peripheral clock control */
#define CKCU_APBEN0_SPI0        ((u32)0x1 << 4)
#define CKCU_APBEN0_SPI1        ((u32)0x1 << 6)
#define CKCU_APBEN0_AFIO        ((u32)0x1 << 14)
#define CKCU_APBEN0_EXTI        ((u32)0x1 << 15)
#define CKCU_APBEN0_ADC         ((u32)0x1 << 24)
#define CKCU_APBEN0_USART0			((u32)0x1 << 8)
#define CKCU_APBEN0_USART2			((u32)0x1 << 10)
#define CKCU_APBEN0_USART4			((u32)0x1 << 12)
#define CKCU_APBEN0_USART5			((u32)0x1 << 13)
#define CKCU_APBEN0_LCD		    	((u32)0x1 << 26)

#define CKCU_APBEN1_I2C	        ((u32)0x1 << 0)
#define CKCU_APBEN1_WDT	        ((u32)0x1 << 4)
#define CKCU_APBEN1_RTC	        ((u32)0x1 << 6)
#define CKCU_APBEN1_GPTM0       ((u32)0x1 << 8)
#define CKCU_APBEN1_GPTM1       ((u32)0x1 << 9)
#define CKCU_APBEN1_GPTM2       ((u32)0x1 << 10)
#define CKCU_APBEN1_GPTM3       ((u32)0x1 << 11)
#define CKCU_APBEN1_COMP        ((u32)0x1 << 12)
#define CKCU_APBEN1_USART1			((u32)0x1 << 2)
#define CKCU_APBEN1_USART3			((u32)0x1 << 3)

#define CKCU_AHBEN_FMC          ((u16)0x1 << 0)
#define CKCU_AHBEN_PDMA         ((u16)0x1 << 4)
#define CKCU_AHBEN_CRC          ((u16)0x1 << 13)
#define CKCU_AHBEN_PA           ((u16)0x1 << 16)
#define CKCU_AHBEN_PB           ((u16)0x1 << 17)
#define CKCU_AHBEN_PC           ((u16)0x1 << 18)
#define CKCU_AHBEN_PD           ((u16)0x1 << 19)
#define CKCU_AHBEN_PE           ((u16)0x1 << 20)
#define CKCU_AHBEN_CAN          ((u16)0x1 << 15)
#define CKCU_AHBEN_CAN1         ((u16)0x1 << 14)

void CKCU_APBPerip0ClockConfig(u32 CKCU_APBP, ControlStatus Cmd);
void CKCU_APBPerip1ClockConfig(u32 CKCU_APBP, ControlStatus Cmd);
void CKCU_AHBPeripClockConfig(u32 CKCU_CLK, ControlStatus Cmd);
void CKCU_AdcClockDivConfig(u8 Div);
void CKCU_LcdClockDivConfig(u8 Div);
void CKCU_LCDSrcSel(u8 src);
u32 CKCU_GetUSARTClockFreq(void);
void Set_sys_Frequency(int Frequency);

void Set_sys_Frequency_LSE(int Frequency);
void Convert_HSI_to_HSE(void);
void NMI_Handler_IRQ(void);
void CKRDY_IRQHandler_IRQ(void);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
	
#ifdef __cplusplus
}
#endif

#endif 
