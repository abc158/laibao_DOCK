/********************************************************************************************************//**
 * @file    pwrcu.c	
 * @brief   The c file of the Power Control Unit firmware functions.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
#include "pwrcu.h"

/** @defgroup PWRCU_Private_Define PWRCU private definitions
  * @{
  */

#define LVDS_MASK         0xFFF9FFFF
#define BAKRST_SET        0x1
#define BAKTEST_READY     0x27
#define TIME_OUT          36000000

#define SLEEPDEEP_SET     0x04      /*!< Cortex SLEEPDEEP bit */


/** @defgroup PWRCU_Private_Function PWRCU private functions
  * @{
  */

/*********************************************************************************************************//**
 * @brief Deinitializes backup domain which contains PWRCU and RTC units.
 * @retval None
 ************************************************************************************************************/
void PWRCU_DeInit(void)
{
  AM_PWRCU->BAKCR = BAKRST_SET ;
  while(AM_PWRCU->BAKCR);
  while(AM_PWRCU->BAKSR);    /* Waits until the BAKPORF be cleared by read */
}

/*********************************************************************************************************//**
 * @brief Waits, until the RTC & PWRCU can be accessed.
 * @return PWRCU_TIMEOUT or PWRCU_OK
 ************************************************************************************************************/
PWRCU_Status PWRCU_CheckReadyAccessed(void)
{
  u32 wTimeOutCnt = TIME_OUT ;

  /* Sets the BK_ISO bit */
  AM_CKCU->LPCR = 0x1 ;

  while(--wTimeOutCnt)
  {
    if(AM_PWRCU->BAKTEST == BAKTEST_READY)
    {
      u32 write = ~AM_PWRCU->BAKREG[9];
      u32 backup = AM_PWRCU->BAKREG[9];
      while(1)
      {
        AM_PWRCU->BAKREG[9] = write;
        if(AM_PWRCU->BAKREG[9] == write) break;
      }
      AM_PWRCU->BAKREG[9] = backup;
      return PWRCU_OK ;
    }
  }
  return PWRCU_TIMEOUT ;
}

/*********************************************************************************************************//**
 * @brief Returns the flags of PWRCU.
 * @return This function will return one of following:
 *   - 0x0000                                   : There is no flag is set.
 *   - 0x0001 (PWRCU_FLAG_BAKPOR)               : This is backup domain power on reset.
 *   - 0x0002 (PWRCU_FLAG_PD)                   : Power-Down flag has been set.
 *   - 0x0100 (PWRCU_FLAG_WUP)                  : External WAKEUP pin flag has been set.
 *   - 0x0102 (PWRCU_FLAG_PD | PWRCU_FLAG_WUP)  : Both PDF and WUPF flags have been set.
 ************************************************************************************************************/
u16 PWRCU_GetFlagStatus(void)
{
  return AM_PWRCU->BAKSR;
}

/*********************************************************************************************************//**
 * @brief Returns the value of specified backup register.
 * @param BAKREGx: Number of backup register. Where x can be 0 ~ 9.
 * @return Between 0x0 ~ 0xFFFFFFFF.
 ************************************************************************************************************/
u32 PWRCU_ReadBackupRegister(PWRCU_BAKREG_Enum BAKREGx)
{
  return AM_PWRCU->BAKREG[BAKREGx];
}

/*********************************************************************************************************//**
 * @brief Writes the DATA to specified backup register.
 * @param BAKREGx : Number of backup registers. Where x can be 0 ~ 9.
 * @param DATA : Must between 0x0 ~ 0xFFFFFFFF.
 * @retval None
 ************************************************************************************************************/
void PWRCU_WriteBackupRegister(PWRCU_BAKREG_Enum BAKREGx, u32 DATA)
{
  AM_PWRCU->BAKREG[BAKREGx] = DATA;
}

/*********************************************************************************************************//**
 * @brief Enters SLEEP mode.
 * @param SleepEntry : Enters sleep mode instruction that is used to WFI or WFE.
 *   This parameter can be one of the following values:
 *   @arg PWRCU_SLEEP_ENTRY_WFE: Enters SLEEP mode via WFE instruction.
 *   @arg PWRCU_SLEEP_ENTRY_WFI: Enters SLEEP mode via WFI instruction.
 * @retval None
 ************************************************************************************************************/
void PWRCU_Sleep(PWRCU_SLEEP_ENTRY_Enum SleepEntry)
{
  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR &= ~(u32)SLEEPDEEP_SET;

  if(SleepEntry == PWRCU_SLEEP_ENTRY_WFE)
  {
    /* Wait for event */
    __WFE();
  }
  else
  {
    /* Wait for interrupt */
    __WFI();
  }
}

/*********************************************************************************************************//**
 * @brief Enters DEEP-SLEEP Mode 1.
 * @param SleepEntry : Enters sleep mode instruction that is used to WFI or WFE.
 *   This parameter can be one of the following values:
 *   @arg PWRCU_SLEEP_ENTRY_WFE: Enters SLEEP mode via WFE instruction.
 *   @arg PWRCU_SLEEP_ENTRY_WFI: Enters SLEEP mode via WFI instruction.
 * @retval None
 ************************************************************************************************************/
void PWRCU_DeepSleep1(PWRCU_SLEEP_ENTRY_Enum SleepEntry)
{
  AM_PWRCU->BAKCR &= (~(1<<3));  //ldo on	
  AM_PWRCU->BAKCR &= (~(1<<7));  //dmos off

  /* Sets SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR |= SLEEPDEEP_SET;

  if(SleepEntry == PWRCU_SLEEP_ENTRY_WFE)
  {
    /* Wait for event */
    __WFE();
  }
  else
  {
    /* Wait for interrupt */
    __WFI();
  }
}

/*********************************************************************************************************//**
 * @brief Enters DEEP-SLEEP Mode 2.
 * @param SleepEntry : Enters sleep mode instruction that is used to WFI or WFE.
 *   This parameter can be one of the following values:
 *   @arg PWRCU_SLEEP_ENTRY_WFE: Enters SLEEP mode via WFE instruction.
 *   @arg PWRCU_SLEEP_ENTRY_WFI: Enters SLEEP mode via WFI instruction.
 * @retval None
 ************************************************************************************************************/
void PWRCU_DeepSleep2(PWRCU_SLEEP_ENTRY_Enum SleepEntry)
{
  AM_PWRCU->BAKCR |= (1<<7);  //dmos on

  /* Sets SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR |= SLEEPDEEP_SET;

  if(SleepEntry == PWRCU_SLEEP_ENTRY_WFE)
  {
    /* Wait for event */
    __WFE();
  }
  else
  {
    /* Wait for interrupt */
    __WFI();
  }
}

/*********************************************************************************************************//**
 * @brief Enters POWER-DOWN Mode.
 * @retval None
 ************************************************************************************************************/
void PWRCU_PowerDown(void)
{
  AM_PWRCU->BAKCR &= (~(1<<7));  //dmos off
  AM_PWRCU->BAKCR |= (1<<3);  //ldo off	

  /* Sets SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR |= SLEEPDEEP_SET;

  /* Enters power-down mode. */
  __WFE();
}

/*********************************************************************************************************//**
 * @brief Configures LVD voltage level.
 * @param Level: Low voltage detect level.
 *   This parameter can be one of following:
 *   @arg PWRCU_LVDS_2V7: 2.7 V
 *   @arg PWRCU_LVDS_2V8: 2.9 V
 *   @arg PWRCU_LVDS_2V9: 2.9 V
 *   @arg PWRCU_LVDS_3V : 3.0 V
 * @retval None
 ************************************************************************************************************/
void PWRCU_SetLVDS(PWRCU_LVDS_Enum Level)
{
  AM_PWRCU->LVDCSR = (AM_PWRCU->LVDCSR & LVDS_MASK) | Level ;
}

/*********************************************************************************************************//**
 * @brief Enables or Disables LVD function.
 * @param NewState: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_LVDCmd(ControlStatus NewState)
{
  AM_PWRCU->LVDCSR = (AM_PWRCU->LVDCSR & (~(1<<16))) | (NewState<<16);
}

/*********************************************************************************************************//**
 * @brief Enables or Disables BOD reset function.
 * @param NewState: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_BODCmd(ControlStatus NewState)
{
  AM_PWRCU->LVDCSR = (AM_PWRCU->LVDCSR & (~(1<<0))) | (NewState<<0);
}

/*********************************************************************************************************//**
 * @brief Select when the BOD occurs, the action for the cause Reset or Interrupt.
 * @param Selection: BOD reset or interrupt selection.
 *   This parameter can be one of following:
 *   @arg PWRCU_BODRIS_RESET: Reset the whole chip
 *   @arg PWRCU_BODRIS_INT: Assert interrupt
 * @retval None
 ************************************************************************************************************/
void PWRCU_BODRISConfig(PWRCU_BODRIS_Enum Selection)
{
  AM_PWRCU->LVDCSR = (AM_PWRCU->LVDCSR & (~(1<<1))) | (Selection<<1);
}

/*********************************************************************************************************//**
 * @brief Return the flag status of LVD .
 * @return SET or RESET.
 ************************************************************************************************************/
FlagStatus PWRCU_GetLVDFlagStatus(void)
{
	if( AM_PWRCU->LVDCSR & (1<<19) )
		return SET;
	else
		return RESET;
}

/*********************************************************************************************************//**
 * @brief Return the flag status of BOD .
 * @return SET or RESET.
 ************************************************************************************************************/
FlagStatus PWRCU_GetBODFlagStatus(void)
{
	if( AM_PWRCU->LVDCSR & (1<<3) )
		return SET;
	else
		return RESET;
}

/*********************************************************************************************************//**
 * @brief Returns the DMOS status.
 * @return This function will return one of following:
 *    - PWRCU_DMOS_STS_ON              : DMOS on
 *    - PWRCU_DMOS_STS_OFF             : DMOS off
 *    - PWRCU_DMOS_STS_OFF_BY_BODRESET : DMOS off caused by brow out reset
 ************************************************************************************************************/
PWRCU_DMOSStatus PWRCU_GetDMOSStatus(void)
{
  u32 wDmosStatus = AM_PWRCU->BAKCR & 0x8080 ;

  if(wDmosStatus == 0x0 )
  {
    return PWRCU_DMOS_STS_OFF;
  }
  else if(wDmosStatus == 0x8080)
  {
    return PWRCU_DMOS_STS_ON;
  }
  else
  {
    return PWRCU_DMOS_STS_OFF_BY_BODRESET;
  }
}

/*********************************************************************************************************//**
 * @brief Enables or Disables DMOS function.
 * @param NewState: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_DMOSCmd(ControlStatus NewState)
{
  AM_PWRCU->BAKCR = (AM_PWRCU->BAKCR & (~(1<<7))) | (NewState<<7);
}

/*********************************************************************************************************//**
 * @brief Configures VDD18 power good source.
 * @param Sel: Specifies VDD18 power good source.
 *    @arg PWRCU_V18RDYSC_BKISO  : Vdd18 power good source come from BK_ISO bit in CKCU unit
 *    @arg PWRCU_V18RDYSC_V18POR : Vdd18 power good source come from Vdd18 power on reset
 * @retval None
 ************************************************************************************************************/
void PWRCU_V18RDYSourceConfig(PWRCU_V18RDYSC_Enum Sel)
{
  AM_PWRCU->BAKCR = (AM_PWRCU->BAKCR & (~(1<<12))) | (Sel<<12);
}

/*********************************************************************************************************//**
 * @brief Enables or Disables LVD interrupt wakeup function.
 * @param NewState: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_LVDIntWakeupConfig(ControlStatus NewState)
{
  AM_PWRCU->LVDCSR = (AM_PWRCU->LVDCSR & (~(1<<20))) | (NewState<<20);
}

/*********************************************************************************************************//**
 * @brief Enables or Disables LVD event wakeup function.
 * @param NewState: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_LVDEventWakeupConfig(ControlStatus NewState)
{
  AM_PWRCU->LVDCSR = (AM_PWRCU->LVDCSR & (~(1<<16))) | (NewState<<16);
}

/*********************************************************************************************************//**
 * @brief Enables or Disables external WAKEUP pin function.
 * @param NewState: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_WakeupPinCmd(ControlStatus NewState)
{
  AM_PWRCU->BAKCR = (AM_PWRCU->BAKCR & (~(1<<8))) | (NewState<<8);
}

/*********************************************************************************************************//**
 * @brief Enables or Disables external WAKEUP pin interrupt function.
 * @param NewState: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_WakeupPinIntConfig(ControlStatus NewState)
{
  AM_PWRCU->BAKCR = (AM_PWRCU->BAKCR & (~(1<<9))) | (NewState<<9);
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


