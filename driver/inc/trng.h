/********************************************************************************************************//**
 * @file    trng.h	
 * @brief   The header file of the Trng Control Unit library.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
 
#ifndef __TRNG_H
#define __TRNG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "AM8813.h"

void TRNG_EnaCmd(ControlStatus NewState);
FlagStatus TRNG_DataRead(u32 *data_trng);
void TRNG_ClearPending(void);

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
