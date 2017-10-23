/********************************************************************************************************//**
 * @file    can.c	
 * @brief   The c file of the Can Unit firmware functions.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
 
#include "can.h"
#include "rstcu.h"

/*********************************************************************************************************//**
  * @brief  Deinitialize the CANx peripheral registers to their default reset values.
  * @param  CANx: This parameter can be AM_CAN or AM_CAN1.
  * @retval None
  ************************************************************************************************************/
void CAN_DeInit(AM_CAN_TypeDef* CANx)
{
	if (CANx == AM_CAN)
		RSTCU_AHBPeripReset(RSTCU_AHBRST_CAN, ENABLE);
	else
		RSTCU_AHBPeripReset(RSTCU_AHBRST_CAN1, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Initialize the CANx mode.
  * @param  CANx: This parameter can be AM_CAN or AM_CAN1.
  * @param  Mode: Operation mode of CANx.
  *   This parameter can be any combination of following:
  *         @arg CAN_MODE_RESET, CAN_MODE_LISTEN, CAN_MODE_SELFTEST, CAN_MODE_SLEEP.
  * @param  NewState: new state of the CANx.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ************************************************************************************************************/
void CAN_ModeCmd(AM_CAN_TypeDef* CANx, u8 Mode, ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
    CANx->MOD |= Mode;
  }
  else
  {
    CANx->MOD &= (~Mode);
  }
}

/*********************************************************************************************************//**
  * @brief  Configure CANx .
  * @param  CANx: This parameter can be AM_CAN or AM_CAN1.
  * @param  Cmd: Command of CANx.
  *   This parameter can be any combination of following:
  *         @arg CAN_CMD_TRAN, CAN_CMD_TRAN_ABORT, CAN_CMD_RCBBUF_RELEASE, CAN_CMD_CLEAR_DATA_OVERRUN, CAN_CMD_SELFTEST.
  * @retval None
  ************************************************************************************************************/
void CAN_Cmd(AM_CAN_TypeDef* CANx, u8 Cmd)
{
  CANx->CMR |= Cmd;
}

/*********************************************************************************************************//**
  * @brief  Initialize the CANx interrupt.
  * @param  CANx: This parameter can be AM_CAN or AM_CAN1.
  * @param  Int: Interrupt mode of CANx.
  *   This parameter can be any combination of following:
  *         @arg CAN_INT_RCV, CAN_INT_TRAN, CAN_INT_ERR_WARNING, CAN_INT_DATA_OVERRUN, CAN_INT_WAKEUP,
  *              CAN_INT_ERR_PASSIVE, CAN_INT_ARB_LOST, CAN_INT_ERR_BUS, CAN_INT_ALL.
  * @param  NewState: new state of the CANx.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ************************************************************************************************************/
void CAN_IntCmd(AM_CAN_TypeDef* CANx, u8 Int, ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
    CANx->IER |= Int;
  }
  else
  {
    CANx->IER &= (~Int);
  }
}

/*********************************************************************************************************//**
  * @brief  Get status of the CANx interrupt.
  * @param  CANx: This parameter can be AM_CAN or AM_CAN1.
  * @param  Int: Interrupt mode of CANx.
  *   This parameter can be any combination of following:
  *         @arg CAN_INT_RCV, CAN_INT_TRAN, CAN_INT_ERR_WARNING, CAN_INT_DATA_OVERRUN, CAN_INT_WAKEUP,
  *              CAN_INT_ERR_PASSIVE, CAN_INT_ARB_LOST, CAN_INT_ERR_BUS, CAN_INT_ALL.
  *   Note that once read, all interrupt status bit are clear.
  * @retval interrupt status.
  ************************************************************************************************************/
u8 CAN_GetIntStatus(AM_CAN_TypeDef* CANx, u8 Int)
{
  return (CANx->IR & Int);
}

/*********************************************************************************************************//**
  * @brief  Get status of the CANx.
  * @param  CANx: This parameter can be AM_CAN or AM_CAN1.
  * @param  Sta: Status mode of CANx.
  *   This parameter can be any combination of following:
  *         @arg CAN_STA_RCVBUF_FULL, CAN_STA_DATA_OVERRUN, CAN_STA_TRANBUF_RELEASE, CAN_STA_TRAN_CMPL, CAN_STA_RCVING,
  *              CAN_STA_TRANING, CAN_STA_ERR_CNT, CAN_STA_BUS_OFF, CAN_STA_ALL.
  * @retval status.
  ************************************************************************************************************/
u8 CAN_GetStatus(AM_CAN_TypeDef* CANx, u8 Sta)
{
  return (CANx->SR & Sta);
}

/*********************************************************************************************************//**
  * @brief  Get status of the CANx interrupt.
  * @param  CANx: This parameter can be AM_CAN or AM_CAN1.
  * @param  BaudRatePSC: Baud Rate Prescaler of CANx.
  *   This parameter can be 0~63.
  * @param  TSEG1: TSEG1 of CANx.
  *   This parameter can be 0~15.
  * @param  TSEG1: TSEG2 of CANx.
  *   This parameter can be 0~7.
  * @retval None
  ************************************************************************************************************/
void CAN_SetBusTiming(AM_CAN_TypeDef* CANx, u8 BaudRatePSC, u8 TSEG1, u8 TSEG2)
{
  CANx->BTR0 = (1<<6) | (BaudRatePSC&0x3f);
	CANx->BTR1 = (1<<7) | ((TSEG1<<0)&0x0f) | ((TSEG2<<4)&0x70);
}

/*********************************************************************************************************//**
  * @brief  Set Error Warning Limit of the CANx.
  * @param  CANx: This parameter can be AM_CAN or AM_CAN1.
  * @param  ErrWarnLmt: the number of errors after which an Error Warning Interrupt should be generated.
  *   This parameter can be 0~255.
  * @retval None
  ************************************************************************************************************/
void CAN_SetErrWarnLmt(AM_CAN_TypeDef* CANx, u8 ErrWarnLmt)
{
  CANx->EWLR = ErrWarnLmt;
}

/*********************************************************************************************************//**
  * @brief  Set Error Counter of the CANx.
  * @param  CANx: This parameter can be AM_CAN or AM_CAN1.
  * @param  ErrCnt_type: Error Counter Type.
  *   This parameter can be ErrRcvCnt or ErrTranCnt.
  * @retval None
  ************************************************************************************************************/
void CAN_SetErrCnt(AM_CAN_TypeDef* CANx, ErrCntType ErrCnt_type, u8 ErrCnt)
{
	if(ErrCnt_type == ErrRcvCnt)
		CANx->RXERR = ErrCnt;
	else if(ErrCnt_type == ErrTranCnt)
		CANx->TXERR = ErrCnt;
}

/*********************************************************************************************************//**
  * @brief  Get Error Warning Limit of the CANx.
  * @param  CANx: This parameter can be AM_CAN or AM_CAN1.
  * @retval Error Warning Limit
  ************************************************************************************************************/
u8 CAN_GetErrWarnLmt(AM_CAN_TypeDef* CANx)
{
  return CANx->EWLR;
}

/*********************************************************************************************************//**
  * @brief  Get Error Counter of the CANx.
  * @param  CANx: This parameter can be AM_CAN or AM_CAN1.
  * @param  ErrCnt_type: Error Counter Type.
  *   This parameter can be ErrRcvCnt or ErrTranCnt.
  * @retval Error Counter of ErrCnt_type.
  ************************************************************************************************************/
u8 CAN_GetErrCnt(AM_CAN_TypeDef* CANx, ErrCntType ErrCnt_type)
{
	if(ErrCnt_type == ErrRcvCnt)
		return CANx->RXERR;
	else
		return CANx->TXERR;
}

/*********************************************************************************************************//**
  * @brief  Set Arbit and Control filed of the CANx frame.
  * @param  CANx: This parameter can be AM_CAN or AM_CAN1.
  * @param  FF: Frame Format, which indicate ID type.
  *   This parameter can be CAN_FRAMEFORMT_SFF or CAN_FRAMEFORMT_EFF.
  * @param  RTR: identify the frame as either a remote frame or a data frame.
  *   This parameter can be CAN_DATAFRAME or CAN_REMOTEFRAME.
  * @param  DLC: Data Length Code.  Specify the number of data bytes included in message.
  *   This parameter can be 0~8.
  * @retval None
  ************************************************************************************************************/
void CAN_SetFrameArbtCtrl(AM_CAN_TypeDef* CANx, u8 FF, u8 RTR, u8 DLC)
{
	CANx->TRFDI_ACAMR[0] = (CANx->TRFDI_ACAMR[0]&0x00) | FF | RTR | (DLC&0x0f);
}

/*********************************************************************************************************//**
  * @brief  Get Frame Format of the CANx.
  * @param  CANx: This parameter can be AM_CAN or AM_CAN1.
  * @retval Frame Format. Can be CAN_FRAMEFORMT_SFF or CAN_FRAMEFORMT_EFF.
  ************************************************************************************************************/
u8 CAN_GetFF(AM_CAN_TypeDef* CANx)
{
	return (CANx->TRFDI_ACAMR[0] & (1<<7));
}

/*********************************************************************************************************//**
  * @brief  Get Remot or Data bit of the CANx.
  * @param  CANx: This parameter can be AM_CAN or AM_CAN1.
  * @retval RTR. Can be CAN_DATAFRAME or CAN_REMOTEFRAME.
  ************************************************************************************************************/
u8 CAN_GetRTR(AM_CAN_TypeDef* CANx)
{
	return (CANx->TRFDI_ACAMR[0] & (1<<6));
}

/*********************************************************************************************************//**
  * @brief  Get Data Length Code of the CANx.
  * @param  CANx: This parameter can be AM_CAN or AM_CAN1.
  * @retval DLC. Data Length Code. Can be 0~8.
  ************************************************************************************************************/
u8 CAN_GetDLC(AM_CAN_TypeDef* CANx)
{
	return (CANx->TRFDI_ACAMR[0] & 0x0f);
}

/*********************************************************************************************************//**
  * @brief  Transmition of the CANx.
  * @param  CANx: This parameter can be AM_CAN or AM_CAN1.
  * @param  pBuf: Pointor to buffer to be transfer.
  * @param  Len: Length of buffer to be transfer.
  * @retval None
  ************************************************************************************************************/
void CAN_Tran(AM_CAN_TypeDef* CANx, u8 *pBuf, u8 Len)
{
	u8 i;
	for(i=0;i<Len;i++)
	{
		CANx->TRFDI_ACAMR[0+i] = *(pBuf+i); 
	}
}

/*********************************************************************************************************//**
  * @brief  Reception of the CANx.
  * @param  CANx: This parameter can be AM_CAN or AM_CAN1.
  * @param  pBuf: Pointor to buffer to be receive.
  * @param  Len: Length of buffer to be receive.
  * @retval None
  ************************************************************************************************************/
void CAN_Rcv(AM_CAN_TypeDef* CANx, u8 *pBuf, u8 Len)
{
	u8 i;
	for(i=0;i<Len;i++)
	{
	  *(pBuf+i) = CANx->TRFDI_ACAMR[0+i]; 
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
