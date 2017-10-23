/********************************************************************************************************//**
 * @file    exception.h
 * @brief   The header file of exceptioon function.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/


void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void CKRDY_IRQHandler(void);
void LVD_IRQHandler(void);
void WDT_IRQHandler(void);
void RTC_IRQHandler(void);
void FLASH_IRQHandler(void);
void EVWUP_IRQHandler(void);
void LPWUP_POR_IRQHandler(void);
void EXTI0_1_2_3_IRQHandler(void);
void EXTI4_5_6_7_IRQHandler(void);
void EXTI8_9_10_11_IRQHandler(void);
void EXTI12_13_14_15_IRQHandler(void);
void ADC_IRQHandler(void);
void GPTM0_IRQHandler(void);
void GPTM1_IRQHandler(void);
void GPTM2_IRQHandler(void);
void GPTM3_IRQHandler(void);
void I2C0_IRQHandler(void);
void SPI0_SPI1_IRQHandler(void);
void UART0_IRQHandler(void);
void UART1_IRQHandler(void);
void UART2_IRQHandler(void);
void UART3_IRQHandler(void);
void UART4_IRQHandler(void);
void UART5_IRQHandler(void);
void PDMA_CH0_IRQHandler(void);
void PDMA_CH1_IRQHandler(void);
void PDMA_CH2_IRQHandler(void);
void PDMA_CH3_IRQHandler(void);
void PDMA_CH4_CH5IRQHandler(void);
void PDMA_CH6_CH7_IRQHandler(void);
void COMP_IRQHandler(void);
void CAN_IRQHandler(void);
