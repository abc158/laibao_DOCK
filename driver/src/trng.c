/********************************************************************************************************//**
 * @file    trng.c	
 * @brief   The c file of the Crc Unit firmware functions.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
#include "trng.h"
#include "rstcu.h"


/*********************************************************************************************************//**
 * @brief TRNG enable or disable.
 * @param NewState: This parameter can be: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void TRNG_EnaCmd(ControlStatus NewState)
{
  if(NewState == ENABLE)
		AM_TRNG->CTRL |= (1<<0);
	else
		AM_TRNG->CTRL &= (~(1<<0));
}

/*********************************************************************************************************//**
 * @brief TRNG data read.
 * @param data_trng: data pointer
 * @retval ready flag
 ************************************************************************************************************/
FlagStatus TRNG_DataRead(u32 *data_trng)
{
	if( AM_TRNG->CTRL&(1<<1) )
	{
		*data_trng = AM_TRNG->CTRL;
		return SET;
	}
	else
		return RESET;
}

/*********************************************************************************************************//**
 * @brief TRNG data ready flag clear.
 * @param none
 * @retval none
 ************************************************************************************************************/
void TRNG_ClearPending(void)
{
	AM_TRNG->CTRL |= (1<<1);
}
