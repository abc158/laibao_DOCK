/********************************************************************************************************//**
 * @file    rtc.c	
 * @brief   The c file of the Rtc Unit firmware functions.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/

#include "rtc.h"

/** @defgroup RTC_Private_Define RTC private definitions
  * @{
  */

#define RTC_CR_ADDR   (AM_RTC_BASE + 0x008)
#define BB_RTCEN    BitBand(RTC_CR_ADDR, 0)
#define BB_RTCSRC   BitBand(RTC_CR_ADDR, 1)
#define BB_LSI_EN   BitBand(RTC_CR_ADDR, 2)
#define BB_LSE_EN   BitBand(RTC_CR_ADDR, 3)
#define BB_CMPCLR   BitBand(RTC_CR_ADDR, 4)
#define BB_SOP      BitBand(RTC_CR_ADDR, 5)
#define BB_ROEN     BitBand(RTC_CR_ADDR, 16)
#define BB_ROES     BitBand(RTC_CR_ADDR, 17)
#define BB_ROWM     BitBand(RTC_CR_ADDR, 18)
#define BB_ROAP     BitBand(RTC_CR_ADDR, 19)
#define BB_ROLF     BitBand(RTC_CR_ADDR, 20)


#define RPRE_MASK   0xF0FF

/** @defgroup RTC_Private_Function RTC private functions
  * @{
  */

/*********************************************************************************************************//**
 * @brief Deinitializes the RTC peripheral registers to their default reset values.
 * @retval None
 ************************************************************************************************************/
void RTC_DeInit(void)
{
  vu32 tmp = 0;

  AM_RTC->CR = 0x00000004;
  AM_RTC->CMP = 0x0;
  AM_RTC->IWEN = 0x0;
  AM_RTC->CR |= 0x00000005;
  while(AM_RTC->CNT);
  AM_RTC->CR = 0x00000F04;
  tmp = AM_RTC->SR;
}

/*********************************************************************************************************//**
 * @brief Selection of RTC timer clock source.
 * @param Source: Specifies the clock source of RTC and backup domain.
 *   @arg RTC_SRC_LSI : Low speed internal clock.
 *   @arg RTC_SRC_LSE : Low speed external clock.
 * @retval None
 ************************************************************************************************************/
void RTC_ClockSourceConfig(RTC_SRC_Enum Source)
{
  AM_RTC->CR = (AM_RTC->CR & (~(1<<1))) | (Source<<1);
}

/*********************************************************************************************************//**
 * @brief Enables or Disables LSI clock.
 * @param NewState: ENABLE or DISABLE
 * @retval None
 ************************************************************************************************************/
void RTC_LSICmd(ControlStatus NewState)
{
  if(NewState == DISABLE)
  {
    AM_RTC->CR &= (~(1<<2));
  }
  else
  {
    AM_RTC->CR |= (1<<2);
    while((AM_CKCU->GCSR & 0x20) == 0);
  }
}

/*********************************************************************************************************//**
 * @brief Enables or Disables LSE clock.
 * @param NewState: ENABLE or DISABLE
 * @retval None
 ************************************************************************************************************/
void RTC_LSECmd(ControlStatus NewState)
{
  if(NewState == DISABLE)
  {
    AM_RTC->CR &= (~(1<<3));
  }
  else
  {
    AM_RTC->CR |= (1<<3);
    while((AM_CKCU->GCSR & 0x10) == 0);
  }
}

/*********************************************************************************************************//**
 * @brief Enables or Disables RTC counter cleared by compare match function.
 * @param NewState: ENABLE or DISABLE
 * @retval None
 ************************************************************************************************************/
void RTC_CMPCLRCmd(ControlStatus NewState)
{
  AM_RTC->CR = (AM_RTC->CR & (~(1<<4))) | (NewState<<4) ;
}

/*********************************************************************************************************//**
 * @brief Config RTC prescaler to a specified value.
 * @param Psc: Value of RTC prescaler.
 *   This parameter can be one of following values:
 *   @arg RTC_RPRE_1
 *   @arg RTC_RPRE_2
 *   @arg RTC_RPRE_4
 *   @arg RTC_RPRE_8
 *   @arg RTC_RPRE_16
 *   @arg RTC_RPRE_32
 *   @arg RTC_RPRE_64
 *   @arg RTC_RPRE_128
 *   @arg RTC_RPRE_256
 *   @arg RTC_RPRE_512
 *   @arg RTC_RPRE_1024
 *   @arg RTC_RPRE_2048
 *   @arg RTC_RPRE_4096
 *   @arg RTC_RPRE_8192
 *   @arg RTC_RPRE_16384
 *   @arg RTC_RPRE_32768
 * @retval None
 ************************************************************************************************************/
void RTC_SetPrescaler(RTC_RPRE_Enum Psc)
{
  AM_RTC->CR = (AM_RTC->CR & RPRE_MASK) | Psc ;
}

/*********************************************************************************************************//**
 * @brief Returns the value of divider.
 * @return The prescaler value. It is powered by 2 and max.is 32768.
 ************************************************************************************************************/
u16 RTC_GetPrescaler(void)
{
  u32 prescaler ;

  prescaler = AM_RTC->CR >> 8 ;

  return ((u16)0x1 << prescaler) ;
}

/*********************************************************************************************************//**
 * @brief Enables or Disables RTC timer.
 * @param NewState: ENABLE or DISABLE
 * @retval None
 ************************************************************************************************************/
void RTC_Cmd(ControlStatus NewState)
{
  AM_RTC->CR = (AM_RTC->CR & (~(1<<0))) | (NewState<<0) ;
}

/*********************************************************************************************************//**
 * @brief Returns the counter value of RTC timer.
 * @return Between 0x0 ~ 0xFFFFFFFF.
 ************************************************************************************************************/
u32 RTC_GetCounter(void)
{
  return AM_RTC->CNT ;
}

/*********************************************************************************************************//**
 * @brief Configures the compare match value.
 * @param Compare: Between 0x0 ~ 0xFFFFFFFF
 * @retval None
 ************************************************************************************************************/
void RTC_SetCompare(u32 Compare)
{
  AM_RTC->CMP = Compare ;
}

/*********************************************************************************************************//**
 * @brief Returns the compare match value of RTC timer.
 * @return Between 0x0 ~ 0xFFFFFFFF.
 ************************************************************************************************************/
u32 RTC_GetCompare(void)
{
  return AM_RTC->CMP ;
}

/*********************************************************************************************************//**
 * @brief Enables or Disables the specified wakeup source.
 * @param RTC_WAKEUP Selection of Wakeup source.
 *   This parameter can be any combination of the following values:
 *   @arg RTC_WAKEUP_CSEC  : Waken up by counter counting.
 *   @arg RTC_WAKEUP_CM    : Waken up by counter compare match with CMP register.
 *   @arg RTC_WAKEUP_OV    : Waken up by conuter overflow.
 *   @arg RTC_WAKEUP_CALALM: Waken up by counter alarm of calendar.
 *   @arg RTC_WAKEUP_CALSEC: Waken up by counter counting of calendar.
 * @param NewState: ENABLE or DISABLE
 * @retval None
 ************************************************************************************************************/
 void RTC_WakeupConfig(u32 RTC_WAKEUP, ControlStatus NewState)
{
  if(NewState != DISABLE)
  {
    AM_RTC->IWEN |= RTC_WAKEUP ;
  }
  else
  {
    AM_RTC->IWEN &= ~RTC_WAKEUP ;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disables the specified interrupt source.
 * @param RTC_INT: Selection of Wakeup source.
 *   This parameter can be any combination of the following values:
 *   @arg RTC_INT_CSEC  : Assert interrupt at counter counting.
 *   @arg RTC_INT_CM    : Assert interrupt at conuter compare match with CMP register.
 *   @arg RTC_INT_OV    : Assert interrupt at conuter overflow.
 *   @arg RTC_INT_CALALM: Assert interrupt at counter alarm of calendar.
 *   @arg RTC_INT_CALSEC: Assert interrupt at counter counting of calendar.
 * @param NewState: ENABLE or DISABLE
 * @retval None
 ************************************************************************************************************/
void RTC_IntConfig(u32 RTC_INT, ControlStatus NewState)
{
  if(NewState != DISABLE)
  {
    AM_RTC->IWEN |= RTC_INT ;
  }
  else
  {
    AM_RTC->IWEN &= ~RTC_INT ;
  }
}

/*********************************************************************************************************//**
 * @brief Returns the RTC flags.
 * @return RTC_STS register value. It maybe combined with the following.
 *   - 0x0 : No flag set
 *   - 0x1 : Count flag
 *   - 0x2 : Match flag
 *   - 0x4 : Overflow flag
 *   - 0x8 : Alarm of calendar flag
 *   - 0x10: Count of calendar flag
 * @note RTC_SR is clear by read action.
 ************************************************************************************************************/
u8 RTC_GetFlagStatus(void)
{
  return (u8)AM_RTC->SR ;
}

/*********************************************************************************************************//**
 * @brief Configures the RTC output function.
 * @param WMode: Specifies the RTC output waveform mode
 *    @arg RTC_ROWM_PULSE: Pulse mode
 *    @arg RTC_ROWM_LEVEL: Level mode
 * @param EventSel: Specifies the RTC output event selection
 *    @arg RTC_ROES_MATCH: Compare match selected
 *    @arg RTC_ROES_SECOND: Second clock selected
 * @param Pol: Specifies the RTC output active polarity
 *    @arg RTC_ROAP_HIGH: Active level is high
 *    @arg RTC_ROAP_LOW: Active level is low
 * @note This function will disable RTC output first.
 ************************************************************************************************************/
void RTC_OutConfig(RTC_ROWM_Enum WMode, RTC_ROES_Enum EventSel, RTC_ROAP_Enum Pol)
{
	AM_RTC->CR &= (~(1<<16));  //rtcout disable
  AM_RTC->CR = (AM_RTC->CR & (~((1<<17)|(1<<18)|(1<<19)))) | WMode | EventSel | Pol;
}

/*********************************************************************************************************//**
 * @brief Enables or Disables RTC output.
 * @param NewState: ENABLE or DISABLE
 * @retval None
 ************************************************************************************************************/
void RTC_OutCmd(ControlStatus NewState)
{
	AM_RTC->CR |= (1<<16);  //rtcout enable
}

/*********************************************************************************************************//**
 * @brief Returns the RTCOUT level mode flag.
 * @retval SET or RESET
 * @note Reads RTC_CR action will clear ROLF flag.
 ************************************************************************************************************/
FlagStatus RTC_GetOutStatus(void)
{
	if(AM_RTC->CR & (1<<20))
		return SET;
	else
		return RESET;
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
