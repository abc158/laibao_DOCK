/********************************************************************************************************//**
 * @file    comp.h	
 * @brief   The header file of the Clock Control Unit library.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
 
#ifndef __COMP_H
#define __COMP_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "AM8813.h"

typedef enum
{
	COMP0 = 0,
	COMP1
}COMPx;

typedef enum
{
	COMP_SPEED_HIGH = 0,
	COMP_SPEED_LOW
}COMP_SPEED;

typedef enum
{
	COMP_INV_IN_1D4VR = 0,
	COMP_INV_IN_1D2VR,
	COMP_INV_IN_3D4VR,
	COMP_INV_IN_VR,
	COMP_INV_IN_IO
}COMP_INV_INPUT;
	 
typedef enum
{
	COMP_OUT_POS = 0,
	COMP_OUT_INV
}COMP_OUT_POL;

typedef enum
{
	COMP_OUT_NO_HYST = 0,
	COMP_OUT_LOW_HYST,
	COMP_OUT_MID_HYST,
	COMP_OUT_HIGH_HYST
}COMP_OUT_HYST;

typedef enum
{
	COMP_OUT_LOW = 0,
	COMP_OUT_HIGH
}COMP_OUT;


/** @defgroup COMP_Exported_Functions COMP exported functions
  * @{
  */

void COMP_DeInit(void);
void COMP_Config(COMPx Comp_x, COMP_SPEED CompSpeed, COMP_INV_INPUT CompInvInput, COMP_OUT_POL CompOutPol, COMP_OUT_HYST CompOutHyst);
void COMP_Cmd(COMPx Comp_x, ControlStatus NewState);
COMP_OUT COMP_GetOutput(COMPx Comp_x);
void COMP_WinModeCmd(ControlStatus NewState);
void COMP_IntCmd(COMPx Comp_x, ControlStatus NewState);
void COMP_WakeUpCmd(COMPx Comp_x, ControlStatus NewState);
ITStatus COMP_GetITStatus(COMPx Comp_x);


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
