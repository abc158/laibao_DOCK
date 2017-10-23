/********************************************************************************************************//**
 * @file    can.h	
 * @brief   The header file of the Can Unit library.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
 
#ifndef __CAN_H
#define __CAN_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "AM8813.h"

typedef enum
{
	ErrRcvCnt = 0,
	ErrTranCnt
}ErrCntType;

/** @defgroup CAN_Exported_Constants CAN exported constants
  * @{
  */

/* CAN mode  */
#define CAN_MODE_RESET                           	((u8)0x01)
#define CAN_MODE_LISTEN                           ((u8)0x02)
#define CAN_MODE_SELFTEST                         ((u8)0x04)
#define CAN_MODE_SLEEP                            ((u8)0x10)
	 
/* CAN command  */
#define CAN_CMD_TRAN															((u8)0x01)	 
#define CAN_CMD_TRAN_ABORT												((u8)0x02)	
#define CAN_CMD_RCBBUF_RELEASE										((u8)0x04)
#define CAN_CMD_CLEAR_DATA_OVERRUN								((u8)0x08)
#define CAN_CMD_SELFTEST													((u8)0x10)

/* CAN acceptance  */	 
#define CAN_ACC_FILTER_DUAL												((u8)0x00)		
#define CAN_ACC_FILTER_SINGLE  										((u8)0x08)	 

/* CAN interrupt  */	 
#define CAN_INT_RCV																((u8)0x01)
#define CAN_INT_TRAN															((u8)0x02)
#define CAN_INT_ERR_WARNING												((u8)0x04)
#define CAN_INT_DATA_OVERRUN											((u8)0x08)
#define CAN_INT_WAKEUP														((u8)0x10)
#define CAN_INT_ERR_PASSIVE												((u8)0x20)
#define CAN_INT_ARB_LOST													((u8)0x40)
#define CAN_INT_ERR_BUS														((u8)0x80)
#define CAN_INT_ALL																((u8)0xff)

/* CAN status  */	
#define CAN_STA_RCVBUF_FULL												((u8)0x01)
#define CAN_STA_DATA_OVERRUN											((u8)0x02)
#define CAN_STA_TRANBUF_RELEASE										((u8)0x04)
#define CAN_STA_TRAN_CMPL													((u8)0x08)
#define CAN_STA_RCVING														((u8)0x10)
#define CAN_STA_TRANING														((u8)0x20)
#define CAN_STA_ERR_CNT														((u8)0x40)
#define CAN_STA_BUS_OFF														((u8)0x80)
#define CAN_STA_ALL 															((u8)0xff)

/* CAN frame format  */	
#define CAN_FRAMEFORMT_SFF												((u8)0x00)
#define CAN_FRAMEFORMT_EFF												((u8)0x80)
#define CAN_DATAFRAME															((u8)0x00)
#define CAN_REMOTEFRAME														((u8)0x40)


/** @defgroup CAN_Exported_Functions CAN exported functions
  * @{
  */

void CAN_DeInit(AM_CAN_TypeDef* CANx);
void CAN_ModeCmd(AM_CAN_TypeDef* CANx, u8 Mode, ControlStatus NewState);
void CAN_Cmd(AM_CAN_TypeDef* CANx, u8 Cmd);
void CAN_IntCmd(AM_CAN_TypeDef* CANx, u8 Int, ControlStatus NewState);
u8 CAN_GetIntStatus(AM_CAN_TypeDef* CANx, u8 Int);
u8 CAN_GetStatus(AM_CAN_TypeDef* CANx, u8 Sta);
void CAN_SetBusTiming(AM_CAN_TypeDef* CANx, u8 BaudRatePSC, u8 TSEG1, u8 TSEG2);
void CAN_SetErrWarnLmt(AM_CAN_TypeDef* CANx, u8 ErrWarnLmt);
void CAN_SetErrCnt(AM_CAN_TypeDef* CANx, ErrCntType ErrCnt_type, u8 ErrCnt);
u8 CAN_GetErrWarnLmt(AM_CAN_TypeDef* CANx);
u8 CAN_GetErrCnt(AM_CAN_TypeDef* CANx, ErrCntType ErrCnt_type);
void CAN_SetFrameArbtCtrl(AM_CAN_TypeDef* CANx, u8 FF, u8 RTR, u8 DLC);
u8 CAN_GetFF(AM_CAN_TypeDef* CANx);
u8 CAN_GetRTR(AM_CAN_TypeDef* CANx);
u8 CAN_GetDLC(AM_CAN_TypeDef* CANx);
void CAN_Tran(AM_CAN_TypeDef* CANx, u8 *pBuf, u8 Len);
void CAN_Rcv(AM_CAN_TypeDef* CANx, u8 *pBuf, u8 Len);
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
