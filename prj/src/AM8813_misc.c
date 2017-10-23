/********************************************************************************************************//**
 * @file    AM8813_misc.c
 * @brief   This file provides all the miscellaneous firmware functions (add-on
  *          to CMSIS functions).
 * @author  
 * @version V0.00
 * @date:   2016-09-02
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/

#include "AM8813_misc.h"

/* *******************************************************************************
                   ##### Interrupts configuration functions #####
 *******************************************************************************
    [..] This section provide functions allowing to configure the NVIC interrupts
        (IRQ). The Cortex-M0 exceptions are managed by CMSIS functions.
         (#) Enable and Configure the priority of the selected IRQ Channels. 
             The priority can be 0..3. 

        -@- Lower priority values gives higher priority.
        -@- Priority Order:
            (#@) Lowest priority.
            (#@) Lowest hardware priority (IRQn position).  
  
@endverbatim
*/

/**
  * @brief  Initializes the NVIC peripheral according to the specified
  *         parameters in the NVIC_InitStruct.
  * @note   To configure interrupts priority correctly, the NVIC_PriorityGroupConfig()
  *         function should be called before.    
  * @param  NVIC_InitStruct: pointer to a NVIC_InitTypeDef structure that contains
  *         the configuration information for the specified NVIC peripheral.
  * @retval None
  */
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct)
{
  uint32_t tmppriority = 0x00;
  
  /* Check the parameters */
//  assert_param(IS_FUNCTIONAL_STATE(NVIC_InitStruct->NVIC_IRQChannelCmd));
//  assert_param(IS_NVIC_PRIORITY(NVIC_InitStruct->NVIC_IRQChannelPriority));  
    
  if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE)
  {
    /* Compute the Corresponding IRQ Priority --------------------------------*/    
    tmppriority = NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel >> 0x02];
    tmppriority &= (uint32_t)(~(((uint32_t)0xFF) << ((NVIC_InitStruct->NVIC_IRQChannel & 0x03) * 8)));
    tmppriority |= (uint32_t)((((uint32_t)NVIC_InitStruct->NVIC_IRQChannelPriority << 6) & 0xFF) << ((NVIC_InitStruct->NVIC_IRQChannel & 0x03) * 8));    
    
    NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel >> 0x02] = tmppriority;
    
    /* Enable the Selected IRQ Channels --------------------------------------*/
    NVIC->ISER[0] = (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
  else
  {
    /* Disable the Selected IRQ Channels -------------------------------------*/
    NVIC->ICER[0] = (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
}

/**
  * @brief  Selects the condition for the system to enter low power mode.
  * @param  LowPowerMode: Specifies the new mode for the system to enter low power mode.
  *   This parameter can be one of the following values:
  *     @arg NVIC_LP_SEVONPEND: Low Power SEV on Pend.
  *     @arg NVIC_LP_SLEEPDEEP: Low Power DEEPSLEEP request.
  *     @arg NVIC_LP_SLEEPONEXIT: Low Power Sleep on Exit.
  * @param  NewState: new state of LP condition. 
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState)
{
  /* Check the parameters */
//  assert_param(IS_NVIC_LP(LowPowerMode));
  
//  assert_param(IS_FUNCTIONAL_STATE(NewState));  
  
  if (NewState != DISABLE)
  {
    SCB->SCR |= LowPowerMode;
  }
  else
  {
    SCB->SCR &= (uint32_t)(~(uint32_t)LowPowerMode);
  }
}

/**
  * @brief  Configures the SysTick clock source.
  * @param  SysTick_CLKSource: specifies the SysTick clock source.
  *   This parameter can be one of the following values:
  *     @arg SysTick_CLKSource_HCLK_Div8: AHB clock divided by 8 selected as SysTick clock source.
  *     @arg SysTick_CLKSource_HCLK: AHB clock selected as SysTick clock source.
  * @retval None
  */
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource)
{
  /* Check the parameters */
//  assert_param(IS_SYSTICK_CLK_SOURCE(SysTick_CLKSource));
  
  if (SysTick_CLKSource == SysTick_CLKSource_HCLK)
  {
    SysTick->CTRL |= SysTick_CLKSource_HCLK;
  }
  else
  {
    SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable the SysTick counter.
  * @param  SysTick_Counter: new state of the SysTick counter.
  *   This parameter can be one of the following values:
  *     @arg SYSTICK_COUNTER_DISABLE  : Disable counter
  *     @arg SYSTICK_COUNTER_ENABLE   : Enable counter
  *     @arg SYSTICK_COUNTER_CLEAR    : Clear counter value to 0
  * @retval None
  ***********************************************************************************************************/
void SysTick_CounterCmd(u32 SysTick_Counter)
{
  /* Check the parameters */
  //Assert_Param(IS_SYSTICK_COUNTER(SysTick_Counter));

  if (SysTick_Counter == SYSTICK_COUNTER_CLEAR)
  {
    SysTick->VAL = SYSTICK_COUNTER_CLEAR;
  }
  else
  {
    if (SysTick_Counter == SYSTICK_COUNTER_ENABLE)
    {
      SysTick->CTRL |= SYSTICK_COUNTER_ENABLE;
    }
    else
    {
      SysTick->CTRL &= SYSTICK_COUNTER_DISABLE;
    }
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable the SysTick Interrupt.
  * @param  NewState: new state of the SysTick Interrupt.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void SysTick_IntConfig(ControlStatus NewState)
{
  /* Check the parameters */
  //Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    SysTick->CTRL |= CTRL_TICKINT_SET;
  }
  else
  {
    SysTick->CTRL &= CTRL_TICKINT_RESET;
  }
}

/*********************************************************************************************************//**
  * @brief  Set SysTick counter reload value.
  * @param  SysTick_Reload: SysTick reload new value.
  *   This parameter must be a number between 1 and 0xFFFFFF.
  * @retval None
  ***********************************************************************************************************/
void SysTick_SetReloadValue(u32 SysTick_Reload)
{
  /* Check the parameters */
  //Assert_Param(IS_SYSTICK_RELOAD(SysTick_Reload));

  SysTick->LOAD = SysTick_Reload;
}
