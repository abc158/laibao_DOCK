/********************************************************************************************************//**
 * @file    rstcu.c
 * @brief   This file provides all the Reset Control Unit firmware functions.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/

#include "rstcu.h"

/*********************************************************************************************************//**
 * @brief Enable APB peripheral 0 reset function.
 * @param RSTCU_APBP: specifies the APB peripheral 0.
 *        This parameter can be:
 *        @arg RSTCU_APBRST0_UART0, RSTCU_APBRST0_UART2,  RSTCU_APBRST0_UART4, RSTCU_APBRST0_UART5,
 *             RSTCU_APBRST0_SPI0, RSTCU_APBRST0_ADC, RSTCU_APBRST0_AFIO, RSTCU_APBRST0_EXTI,
 *             RSTCU_APBRST0_LCD, RSTCU_APBRST0_TRNG
 * @param Cmd: new status of the peripheral reset.
 *        This parameter can be:
 *        @arg ENABLE
 *        @arg DISABLE
 * @retval None
 ************************************************************************************************************/
void RSTCU_APBPerip0Reset(u32 RSTCU_APBP, ControlStatus Cmd)
{
  if (Cmd == ENABLE)
  {
    AM_RSTCU->APBPRST0 |= RSTCU_APBP;
  }
  else
  {
    AM_RSTCU->APBPRST0 &= ~RSTCU_APBP;
  }
}

/*********************************************************************************************************//**
 * @brief Enable APB peripheral 1 reset function.
 * @param RSTCU_APBP: specifies the APB peripheral 1.
 *        This parameter can be:
 *        @arg RSTCU_APBRST1_UART1, RSTCU_APBRST1_UART3, RSTCU_APBRST1_I2C0, RSTCU_APBRST1_WDT,  
							 RSTCU_APBRST1_GPTM0, RSTCU_APBRST1_GPTM1, RSTCU_APBRST1_GPTM2,RSTCU_APBRST1_GPTM3 
 *             RSTCU_APBRST1_RTC
 * @param Cmd: new status of the peripheral reset.
 *        This parameter can be:
 *        @arg ENABLE
 *        @arg DISABLE
 * @retval None
 ************************************************************************************************************/
void RSTCU_APBPerip1Reset(u32 RSTCU_APBP, ControlStatus Cmd)
{
  if (Cmd == ENABLE)
  {
    AM_RSTCU->APBPRST1 |= RSTCU_APBP;
  }
  else
  {
    AM_RSTCU->APBPRST1 &= ~RSTCU_APBP;
  }
}


/*********************************************************************************************************//**
 * @brief Enable AHB peripheral reset function.
 * @param RSTCU_AHBP: specifies the AHB peripheral.
 *        This parameter can be:
 *        @arg RSTCU_AHBRST_CAN, RSTCU_AHBRST_CAN1, RSTCU_AHBRST_PDMA, RSTCU_AHBRST_CRC, RSTCU_AHBRST_PA, 
               RSTCU_AHBRST_PB, RSTCU_AHBRST_PC, RSTCU_AHBRST_PD, RSTCU_AHBRST_PE
 * @param Cmd: new status of the peripheral reset.
 *        This parameter can be:
 *        @arg ENABLE
 *        @arg DISABLE
 * @retval None
 ************************************************************************************************************/
void RSTCU_AHBPeripReset(u32 RSTCU_AHBP, ControlStatus Cmd)
{
  if (Cmd == ENABLE)
  {
    AM_RSTCU->AHBPRST |= RSTCU_AHBP;
  }
  else
  {
    AM_RSTCU->AHBPRST &= ~RSTCU_AHBP;
  }
}



