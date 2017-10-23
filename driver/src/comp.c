/********************************************************************************************************//**
 * @file    comp.c	
 * @brief   The c file of the Wdt Unit firmware functions.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
 
#include "comp.h"
#include "rstcu.h"

/** @defgroup COMP_Private_Function COMP private functions
  * @{
  */

/*********************************************************************************************************//**
 * @brief Deinitialize the COMP peripheral registers to their default reset values.
 * @param None
 * @retval None
 ************************************************************************************************************/
void COMP_DeInit(void)
{
  RSTCU_APBPerip1Reset(RSTCU_APBRST1_COMP, ENABLE);
}


/*********************************************************************************************************//**
 * @brief Configure the COMP.
 * @param Comp_x: where Comp_x can be COMP0 or COMP1.
 * @param CompSpeed: Specify the Comp_x speed mode.
 *   This parameter can be the following values:
 *     @arg COMP_SPEED_HIGH: High speed / full power
 *     @arg COMP_SPEED_LOW : Very-low speed / ultra-low power
 * @param CompInvInput: Specify the Comp_x inverting input selection.
 *   This parameter can be the following values:
 *     @arg COMP_INV_IN_1D4VR: 1/4 of VREFINT
 *     @arg COMP_INV_IN_1D2VR: 1/2 of VREFINT
 *     @arg COMP_INV_IN_3D4VR: 3/4 of VREFINT
 *     @arg COMP_INV_IN_VR   : VREFINT
 *     @arg COMP_INV_IN_IO   : IO INPUT, Comp_0 from pb2, Comp_1 from pb13
 * @param CompOutPol: Specify the Comp_x polarity.
 *   This parameter can be the following values:
 *     @arg COMP_OUT_POS: Output is not inverted
 *     @arg COMP_OUT_INV: Output is inverted
 * @param CompOutHyst: Specify the Comp_x hysteresis level.
 *   This parameter can be the following values:
 *     @arg COMP_OUT_NO_HYST: No hysteresis
 *     @arg COMP_OUT_LOW_HYST: Low hysteresis
 *     @arg COMP_OUT_MID_HYST: Medium hysteresis
 *     @arg COMP_OUT_HIGH_HYST: High hysteresis 
 * @retval None
************************************************************************************************************/
void COMP_Config(COMPx Comp_x, COMP_SPEED CompSpeed, COMP_INV_INPUT CompInvInput, COMP_OUT_POL CompOutPol, COMP_OUT_HYST CompOutHyst)
{
	AM_COMP->CCSR = (AM_COMP->CCSR & (~( (1<<(3+Comp_x*16))|(7<<(4+Comp_x*16))|(1<<(11+Comp_x*16))|(3<<(12+Comp_x*16)) ))) \
	  | (CompSpeed<<(3+Comp_x*16)) | (CompInvInput<<(4+Comp_x*16)) | (CompOutPol<<(11+Comp_x*16)) | (CompOutHyst<<(12+Comp_x*16));
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified COMP peripheral.
 * @param Comp_x: where Comp_x can be COMP0 or COMP1.
 * @param NewState: new state of the COMPx peripheral.
 *   This parameter can be: ENABLE or DISABLE.
 * @retval None
************************************************************************************************************/
void COMP_Cmd(COMPx Comp_x, ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
		AM_COMP->CCSR |= (1<<(Comp_x*16));    
  }
  else
  {
    AM_COMP->CCSR &= (~(1<<(Comp_x*16)));
  }
}

/*********************************************************************************************************//**
 * @brief Get the COMP output.
 * @param Comp_x: where Comp_x can be COMP0 or COMP1.
 * @retval COMP_OUT: Specify the Comp_x output state.
 *   This parameter can be the following values:
 *     @arg COMP_OUT_LOW : Output is low (non-inverting input below inverting input)
 *     @arg COMP_OUT_HIGH: Output is high (non-inverting input above inverting input)
************************************************************************************************************/
COMP_OUT COMP_GetOutput(COMPx Comp_x)
{
	if( AM_COMP->CCSR & (1<<(14+Comp_x*16)) )
		return COMP_OUT_HIGH;
	else
		return COMP_OUT_LOW;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the COMP Window Mode.
 * @param NewState: This parameter can be: ENABLE or DISABLE.
 * @retval None
************************************************************************************************************/
void COMP_WinModeCmd(ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
    AM_COMP->CCSR |= (1<<23);
  }
  else
  {   
		AM_COMP->CCSR &= (~(1<<23));
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified COMP peripheral interrupt.
 * @param Comp_x: where Comp_x can be COMP0 or COMP1.
 * @param NewState: new state of the COMPx peripheral.
 *   This parameter can be: ENABLE or DISABLE.
 * @retval None
************************************************************************************************************/
void COMP_IntCmd(COMPx Comp_x, ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
		AM_COMP->WICR |= (1<<(1+Comp_x*8));   
  }
  else
  {
    AM_COMP->WICR &= (~(1<<(1+Comp_x*8)));
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified COMP peripheral wake-up.
 * @param Comp_x: where Comp_x can be COMP0 or COMP1.
 * @param NewState: new state of the COMPx peripheral.
 *   This parameter can be: ENABLE or DISABLE.
 * @retval None
************************************************************************************************************/
void COMP_WakeUpCmd(COMPx Comp_x, ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
    AM_COMP->WICR |= (1<<(0+Comp_x*8));
  }
  else
  {
		AM_COMP->WICR &= (~(1<<(0+Comp_x*8)));   
  }
}

/*********************************************************************************************************//**
 * @brief Get the COMP interrupt flag.
 * @param Comp_x: where Comp_x can be COMP0 or COMP1.
 * @retval COMP_OUT: Specify the Comp_x output state.
 *   This parameter can be the following values:
 *     @arg COMP_OUT_LOW : Output is low (non-inverting input below inverting input)
 *     @arg COMP_OUT_HIGH: Output is high (non-inverting input above inverting input)
************************************************************************************************************/
ITStatus COMP_GetITStatus(COMPx Comp_x)
{
	if( AM_COMP->CCSR & (1<<(4+Comp_x*8)) )
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
