/********************************************************************************************************//**
 * @file    AM8813_misc.h
 * @brief   header file
 * @author  
 * @version V0.00
 * @date:   2016-09-02
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MISC_H
#define __MISC_H

#include "AM8813.h"


/** 
  * @brief  NVIC Init Structure definition  
  */

typedef struct
{
  uint8_t NVIC_IRQChannel;             /*!< Specifies the IRQ channel to be enabled or disabled.
                                            This parameter can be a value of @ref IRQn_Type 
                                            (For the complete STM32 Devices IRQ Channels list, 
                                            please refer to stm32f0xx.h file) */

  uint8_t NVIC_IRQChannelPriority;     /*!< Specifies the priority level for the IRQ channel specified
                                            in NVIC_IRQChannel. This parameter can be a value
                                            between 0 and 3.  */

  FunctionalState NVIC_IRQChannelCmd;  /*!< Specifies whether the IRQ channel defined in NVIC_IRQChannel
                                            will be enabled or disabled. 
                                            This parameter can be set either to ENABLE or DISABLE */   
} NVIC_InitTypeDef;


/** @defgroup MISC_Exported_Constants
  * @{
  */

/** @defgroup MISC_System_Low_Power 
  * @{
  */

#define NVIC_LP_SEVONPEND            ((uint8_t)0x10)
#define NVIC_LP_SLEEPDEEP            ((uint8_t)0x04)
#define NVIC_LP_SLEEPONEXIT          ((uint8_t)0x02)
#define IS_NVIC_LP(LP) (((LP) == NVIC_LP_SEVONPEND) || \
                        ((LP) == NVIC_LP_SLEEPDEEP) || \
                        ((LP) == NVIC_LP_SLEEPONEXIT))


/** @defgroup MISC_Preemption_Priority_Group 
  * @{
  */
#define IS_NVIC_PRIORITY(PRIORITY)  ((PRIORITY) < 0x04)


/** @defgroup MISC_SysTick_clock_source 
  * @{
  */
/* SysTick clock source */
#define SysTick_CLKSource_HCLK_Div8    ((uint32_t)0xFFFFFFFB)
#define SysTick_CLKSource_HCLK         ((uint32_t)0x00000004)
#define IS_SYSTICK_CLK_SOURCE(SOURCE) (((SOURCE) == SysTick_CLKSource_HCLK) || \

/* SysTick counter state  */
#define SYSTICK_COUNTER_DISABLE                     ((u32)0xFFFFFFFE)
#define SYSTICK_COUNTER_ENABLE                      ((u32)0x00000001)
#define SYSTICK_COUNTER_CLEAR                       ((u32)0x00000000)

/* SysTick int  */
#define CTRL_TICKINT_SET      ((u32)0x00000002)
#define CTRL_TICKINT_RESET    ((u32)0xFFFFFFFD)
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState);
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);
void SysTick_CounterCmd(u32 SysTick_Counter);
void SysTick_IntConfig(ControlStatus NewState);
void SysTick_SetReloadValue(u32 SysTick_Reload);
#endif
