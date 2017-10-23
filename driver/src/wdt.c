/********************************************************************************************************//**
 * @file    wdt.c	
 * @brief   The c file of the Wdt Unit firmware functions.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
 
#include "wdt.h"
#include "rstcu.h"

/** @defgroup WDT_Private_Define WDT private definitions
  * @{
  */

/* WDT Restart Key */
#define RESTART_KEY            ((u32)0x5FA00000)

/* WDT Protect mask */
#define PRCT_SET               ((u32)0x0000CA35)
#define PRCT_RESET             ((u32)0x000035CA)

/* WDT WDTFIEN mask */
#define MODE0_WDTFIEN_SET      ((u32)0x00001000)
#define MODE0_WDTFIEN_RESET    ((u32)0xFFFFEFFF)

/* WDT WDTRSTEN mask */
#define MODE0_WDTRETEN_SET     ((u32)0x00002000)
#define MODE0_WDTRETEN_RESET   ((u32)0xFFFFDFFF)

/* WDT WDTEN mask */
#define MODE0_WDTEN_SET     ((u32)0x00010000)
#define MODE0_WDTEN_RESET   ((u32)0xFFFEFFFF)

/* WDT WDTLOCK mask */
#define MODE0_WDTLOCK_SET     ((u32)0x00000010)
#define MODE0_WDTLOCK_RESET   ((u32)0x00000000)


/** @defgroup WDT_Private_Function WDT private functions
  * @{
  */

/*********************************************************************************************************//**
  * @brief  Deinitialize the WDT peripheral registers to their default reset values.
  * @retval None
  ************************************************************************************************************/
void WDT_DeInit(void)
{
  RSTCU_APBPerip1Reset(RSTCU_APBRST1_WDT, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable the WDT.
  * @param  NewState: new state of the WDT.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ************************************************************************************************************/
void WDT_Cmd(ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
    AM_WDT->MR0 |= MODE0_WDTEN_SET;
  }
  else
  {
    AM_WDT->MR0 &= MODE0_WDTEN_RESET;
  }
}

/*********************************************************************************************************//**
  * @brief  Configure WDT runs or halts in sleep and deep sleep1 mode.
  * @param  NewState: new state of the WDT.
  *     @arg MODE0_WDTSHLT_BOTH    : WDT runs in sleep and deep sleep1 mode.
  *     @arg MODE0_WDTSHLT_SLEEP   : WDT runs in sleep mode.
  *     @arg MODE0_WDTSHLT_HALT    : WDT halts in sleep and deep sleep1 mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ************************************************************************************************************/
void WDT_HaltConfig(u32 WDT_Mode)
{
  if (WDT_Mode == MODE0_WDTSHLT_BOTH)
  {
    AM_WDT->MR0 = (( MODE0_WDTSHLT_BOTH ) | (AM_WDT->MR0 & 0x00013FFF));
  }
  else if (WDT_Mode == MODE0_WDTSHLT_SLEEP)
  {
    AM_WDT->MR0 = (( MODE0_WDTSHLT_SLEEP ) | (AM_WDT->MR0 & 0x00013FFF));
  }
  else
  {
    AM_WDT->MR0 = (( MODE0_WDTSHLT_HALT ) | (AM_WDT->MR0 & 0x00013FFF));
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable the WDT interrupt when WDT meets underflow or error.
  * @param  NewState: new state of the WDT Interrupt.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ************************************************************************************************************/
void WDT_IntConfig(ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
    AM_WDT->MR0 |= MODE0_WDTFIEN_SET;
  }
  else
  {
    AM_WDT->MR0 &= MODE0_WDTFIEN_RESET;
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable the WDT Reset when WDT meets underflow or error.
  * @param   NewState: new state of the WDT Reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ************************************************************************************************************/
void WDT_ResetCmd(ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
    AM_WDT->MR0 |= MODE0_WDTRETEN_SET;
  }
  else
  {
    AM_WDT->MR0 &= MODE0_WDTRETEN_RESET;
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable protection mechanism of the WDT.
  * @param  NewState: new state of the WDT Protect.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ************************************************************************************************************/
void WDT_ProtectCmd(ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
    AM_WDT->PR = PRCT_SET;
  }
  else
  {
    AM_WDT->PR = PRCT_RESET;
  }
}

/*********************************************************************************************************//**
  * @brief  Set Reload value of the WDT.
  * @param  WDT_WDTV : specify the WDT Reload value.
  *   This parameter must be a number between 0 and 0x0FFF.
  * @retval None
  ************************************************************************************************************/
void WDT_SetReloadValue(u16 WDT_WDTV)
{
  AM_WDT->MR0 = WDT_WDTV | (AM_WDT->MR0 & 0x0000F000);
}

/*********************************************************************************************************//**
  * @brief  Get the current reload value of the WDT.
  * @retval WDT reload value between 0 and 0x0FFF
  ************************************************************************************************************/
u16 WDT_GetReloadValue(void)
{
  return ((u16)(AM_WDT->MR0 & 0xFFF)) ;
}

/*********************************************************************************************************//**
  * @brief  Set delta value of the WDT.
  * @param  WDT_WDTD : specify the WDT Delta value.
  *   This parameter must be a number between 0 and 0x0FFF.
  * @retval None
  ************************************************************************************************************/
void WDT_SetDeltaValue(u16 WDT_WDTD)
{
  AM_WDT->MR1 = (WDT_WDTD | (AM_WDT->MR1 & 0x00007000));
}

/*********************************************************************************************************//**
  * @brief  Get current delta value of the WDT.
  * @retval WDT delta value between 0 and 0x0FFF
  ************************************************************************************************************/
u16 WDT_GetDeltaValue(void)
{
  return ((u16)(AM_WDT->MR1 & 0xFFF)) ;
}

/*********************************************************************************************************//**
  * @brief  Set Prescaler value of the WDT.
  * @param  WDT_PRESCALER: specify the WDT Prescaler value.
  *   This parameter can be one of the following values:
  *     @arg WDT_PRESCALER_1   : WDT prescaler set to 1
  *     @arg WDT_PRESCALER_2   : WDT prescaler set to 2
  *     @arg WDT_PRESCALER_4   : WDT prescaler set to 4
  *     @arg WDT_PRESCALER_8   : WDT prescaler set to 8
  *     @arg WDT_PRESCALER_16  : WDT prescaler set to 16
  *     @arg WDT_PRESCALER_32  : WDT prescaler set to 32
  *     @arg WDT_PRESCALER_64  : WDT prescaler set to 64
  *     @arg WDT_PRESCALER_128 : WDT prescaler set to 128
  * @retval None
  ************************************************************************************************************/
void WDT_SetPrescaler(u16 WDT_PRESCALER)
{
  AM_WDT->MR1 = (WDT_PRESCALER | (AM_WDT->MR1 & 0x00000FFF));
}

/*********************************************************************************************************//**
  * @brief  Get the current prescaler value of the WDT.
  * @retval WDT prescaler value
  ************************************************************************************************************/
u8 WDT_GetPrescaler(void)
{
  u32 tmp ;

  tmp = AM_WDT->MR1 & 0x7000 ;
  tmp >>= 12 ;
  return ((u8)0x1 << tmp) ;
}

/*********************************************************************************************************//**
  * @brief  WDT Restart (Reload WDT Counter)
  * @retval None
  ************************************************************************************************************/
void WDT_Restart(void)
{
  AM_WDT->CR = RESTART_KEY | 0x1;
}

/*********************************************************************************************************//**
  * @brief  Check whether the specified WDT flag has been set.
  * @param  WDT_FLAG: specify the flag to be check.
  *   This parameter can be one of the following values:
  *     @arg WDT_FLAG_UNDERFLOW       : WDT underflow active
  *     @arg WDT_FLAG_ERROR           : WDT error active
  * @retval The new state of WDT_FLAG (SET or RESET).
  ************************************************************************************************************/
FlagStatus WDT_GetFlagStatus (u32 WDT_FLAG)
{
  u32 statusreg = 0;
  FlagStatus bitstatus = RESET;

  statusreg = AM_WDT->SR;

  if ( statusreg != WDT_FLAG )
  {
    bitstatus = RESET;
  }
  else
  {
    bitstatus = SET;
  }

  return bitstatus;
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable the WDTLOCK.
  * @param  NewState: new state of the WDTLOCK.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ************************************************************************************************************/
void WDT_LockCmd(ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
    AM_WDT->CSR |= ( MODE0_WDTLOCK_SET | ( AM_WDT->CSR & 0x00000001 ));
  }
  else
  {
    AM_WDT->CSR &= ( MODE0_WDTLOCK_RESET | ( AM_WDT->CSR & 0x00000001 ));
  }
}

/*********************************************************************************************************//**
  * @brief  WDT source select.
  * @param  NewState: LSI or LSE of the WDT source.
  *   This parameter can be: WDT_SOURCE_LSI or WDT_SOURCE_LSE.
  * @retval None
  ************************************************************************************************************/
void WDT_SourceConfig( u32 WDT_SOURCE )
{
  if (WDT_SOURCE != WDT_SOURCE_LSE)
  {
    AM_WDT->CSR = WDT_SOURCE_LSI;
  }
  else
  {
    AM_WDT->CSR = WDT_SOURCE_LSE;
  }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
