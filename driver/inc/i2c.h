/********************************************************************************************************//**
 * @file    i2c.h	
 * @brief   The header file of the I2c Control Unit library.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
 
#ifndef __I2C_H
#define __I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "AM8813.h"

typedef struct
{
  u32 I2C_GeneralCall;
  u32 I2C_AddressingMode;
  u32 I2C_Acknowledge;
  u16 I2C_OwnAddress;
  u32 I2C_Speed;
}I2C_InitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/

/** @defgroup I2C_Exported_Constants I2C exported constants
  * @{
  */

#define I2C_GENERALCALL_ENABLE                      ((u32)0x00000004)
#define I2C_GENERALCALL_DISABLE                     ((u32)0x00000000)

#define IS_I2C_GENERAL_CALL(CALL)                   ((CALL == I2C_GENERALCALL_ENABLE) || \
                                                     (CALL == I2C_GENERALCALL_DISABLE))


#define I2C_ADDRESSING_7BIT                         ((u32)0x00000000)
#define I2C_ADDRESSING_10BIT                        ((u32)0x00000080)

#define IS_I2C_ACKNOWLEDGE_ADDRESS(ADDRESS)         ((ADDRESS == I2C_ADDRESSING_7BIT) || \
                                                     (ADDRESS == I2C_ADDRESSING_10BIT))


#define I2C_ACK_ENABLE                              ((u32)0x00000001)
#define I2C_ACK_DISABLE                             ((u32)0x00000000)

#define IS_I2C_ACKNOWLEDGE(ACKNOWLEDGE)             ((ACKNOWLEDGE == I2C_ACK_ENABLE) || \
                                                     (ACKNOWLEDGE == I2C_ACK_DISABLE))


#define I2C_INT_STA                                 ((u32)0x00000001)
#define I2C_INT_STO                                 ((u32)0x00000002)
#define I2C_INT_ADRS                                ((u32)0x00000004)
#define I2C_INT_GCS                                 ((u32)0x00000008)
#define I2C_INT_ARBLOS                              ((u32)0x00000100)
#define I2C_INT_RXNACK                              ((u32)0x00000200)
#define I2C_INT_BUSERR                              ((u32)0x00000400)
#define I2C_INT_TOUT                                ((u32)0x00000800)
#define I2C_INT_RXDNE                               ((u32)0x00010000)
#define I2C_INT_TXDE                                ((u32)0x00020000)
#define I2C_INT_RXBF                                ((u32)0x00040000)
#define I2C_INT_ALL                                 ((u32)0x00070F0F)

#define IS_I2C_INT(int)                             (((int & 0xFFF8F0F0) == 0x0) && (int != 0x0))


#define I2C_MASTER_READ                             ((u32)0x00000400)
#define I2C_MASTER_WRITE                            ((u32)0x00000000)

#define IS_I2C_DIRECTION(DIRECTION)                 ((DIRECTION == I2C_MASTER_READ) || \
                                                     (DIRECTION == I2C_MASTER_WRITE))


#define I2C_REGISTER_CR                             ((u8)0x00)
#define I2C_REGISTER_IER                            ((u8)0x04)
#define I2C_REGISTER_ADDR                           ((u8)0x08)
#define I2C_REGISTER_SR                             ((u8)0x0C)
#define I2C_REGISTER_SHPGR                          ((u8)0x10)
#define I2C_REGISTER_SLPGR                          ((u8)0x14)
#define I2C_REGISTER_DR                             ((u8)0x18)
#define I2C_REGISTER_BFCLR                          ((u8)0x1C)
#define I2C_REGISTER_TAR                            ((u8)0x20)

#define IS_I2C_REGISTER(REGISTER)                   ((REGISTER == I2C_REGISTER_CR) || \
                                                     (REGISTER == I2C_REGISTER_IER) || \
                                                     (REGISTER == I2C_REGISTER_ADDR) || \
                                                     (REGISTER == I2C_REGISTER_SR) || \
                                                     (REGISTER == I2C_REGISTER_SHPGR) || \
                                                     (REGISTER == I2C_REGISTER_SLPGR) || \
                                                     (REGISTER == I2C_REGISTER_DR) || \
                                                     (REGISTER == I2C_REGISTER_BFCLR) || \
                                                     (REGISTER == I2C_REGISTER_TAR))


#define I2C_FLAG_STA                                ((u32)0x00000001)
#define I2C_FLAG_STO                                ((u32)0x00000002)
#define I2C_FLAG_ADRS                               ((u32)0x00000004)
#define I2C_FLAG_GCS                                ((u32)0x00000008)
#define I2C_FLAG_ARBLOS                             ((u32)0x00000100)
#define I2C_FLAG_RXNACK                             ((u32)0x00000200)
#define I2C_FLAG_BUSERR                             ((u32)0x00000400)
#define I2C_FLAG_TOUTF                              ((u32)0x00000800)
#define I2C_FLAG_RXDNE                              ((u32)0x00010000)
#define I2C_FLAG_TXDE                               ((u32)0x00020000)
#define I2C_FLAG_RXBF                               ((u32)0x00040000)
#define I2C_FLAG_BUSBUSY                            ((u32)0x00080000)
#define I2C_FLAG_MASTER                             ((u32)0x00100000)
#define I2C_FLAG_TXNRX                              ((u32)0x00200000)

#define IS_I2C_FLAG(FLAG)                           ((FLAG == I2C_FLAG_STA) || \
                                                     (FLAG == I2C_FLAG_STO) || \
                                                     (FLAG == I2C_FLAG_ADRS) || \
                                                     (FLAG == I2C_FLAG_GCS) || \
                                                     (FLAG == I2C_FLAG_ARBLOS) || \
                                                     (FLAG == I2C_FLAG_RXNACK) || \
                                                     (FLAG == I2C_FLAG_BUSERR) || \
                                                     (FLAG == I2C_FLAG_TOUTF) || \
                                                     (FLAG == I2C_FLAG_RXDNE) || \
                                                     (FLAG == I2C_FLAG_TXDE) || \
                                                     (FLAG == I2C_FLAG_RXBF) || \
                                                     (FLAG == I2C_FLAG_BUSBUSY) || \
                                                     (FLAG == I2C_FLAG_MASTER) || \
                                                     (FLAG == I2C_FLAG_TXNRX))

#define IS_I2C_CLEAR_FLAG(FLAG)                     ((FLAG == I2C_FLAG_ARBLOS) || \
                                                     (FLAG == I2C_FLAG_RXNACK) || \
                                                     (FLAG == I2C_FLAG_BUSERR) || \
                                                     (FLAG == I2C_FLAG_TOUTF))


#define I2C_MASTER_SEND_START                       ((u32)0x00180001)
#define I2C_MASTER_RECEIVER_MODE                    ((u32)0x00180004)
#define I2C_MASTER_TRANSMITTER_MODE                 ((u32)0x003A0004)
#define I2C_MASTER_RX_NOT_EMPTY                     ((u32)0x00190000)
#define I2C_MASTER_RX_NOT_EMPTY_NOBUSY              ((u32)0x00010000)
#define I2C_MASTER_TX_EMPTY                         ((u32)0x003A0000)
#define I2C_MASTER_RX_BUFFER_FULL                   ((u32)0x001D0000)
#define I2C_SLAVE_ACK_TRANSMITTER_ADDRESS           ((u32)0x002A0004)
#define I2C_SLAVE_ACK_RECEIVER_ADDRESS              ((u32)0x00080004)
#define I2C_SLAVE_ACK_GCALL_ADDRESS                 ((u32)0x00080008)
#define I2C_SLAVE_RX_NOT_EMPTY                      ((u32)0x00090000)
#define I2C_SLAVE_RX_NOT_EMPTY_STOP                 ((u32)0x00010002)
#define I2C_SLAVE_TX_EMPTY                          ((u32)0x002A0000)
#define I2C_SLAVE_RX_BUFFER_FULL                    ((u32)0x000D0000)
#define I2C_SLAVE_RECEIVED_NACK                     ((u32)0x00080200)
#define I2C_SLAVE_RECEIVED_NACK_STOP                ((u32)0x00000202)
#define I2C_SLAVE_STOP_DETECTED                     ((u32)0x00000002)


#define IS_I2C_STATUS(STATUS)                       ((STATUS == I2C_MASTER_SEND_START) || \
                                                     (STATUS == I2C_MASTER_RECEIVER_MODE) || \
                                                     (STATUS == I2C_MASTER_TRANSMITTER_MODE) || \
                                                     (STATUS == I2C_MASTER_RX_NOT_EMPTY) || \
                                                     (STATUS == I2C_MASTER_RX_NOT_EMPTY_NOBUSY) || \
                                                     (STATUS == I2C_MASTER_TX_EMPTY) || \
                                                     (STATUS == I2C_MASTER_RX_BUFFER_FULL) || \
                                                     (STATUS == I2C_SLAVE_ACK_TRANSMITTER_ADDRESS) || \
                                                     (STATUS == I2C_SLAVE_ACK_RECEIVER_ADDRESS) || \
                                                     (STATUS == I2C_SLAVE_ACK_GCALL_ADDRESS) || \
                                                     (STATUS == I2C_SLAVE_RX_NOT_EMPTY) || \
                                                     (STATUS == I2C_SLAVE_RX_NOT_EMPTY_STOP) || \
                                                     (STATUS == I2C_SLAVE_TX_EMPTY) || \
                                                     (STATUS == I2C_SLAVE_RX_BUFFER_FULL) || \
                                                     (STATUS == I2C_SLAVE_RECEIVED_NACK) || \
                                                     (STATUS == I2C_SLAVE_RECEIVED_NACK_STOP) || \
                                                     (STATUS == I2C_SLAVE_STOP_DETECTED))


#define I2C_PDMAREQ_TX                              ((u32)0x00000100)
#define I2C_PDMAREQ_RX                              ((u32)0x00000200)

#define IS_I2C_PDMA_REQ(REQ)                        (((REQ & 0xFFFFFCFF) == 0x0) && (REQ != 0x0))


#define I2C_PRESCALER_1                             ((u32)0x00000000)
#define I2C_PRESCALER_2                             ((u32)0x00010000)
#define I2C_PRESCALER_4                             ((u32)0x00020000)
#define I2C_PRESCALER_8                             ((u32)0x00030000)
#define I2C_PRESCALER_16                            ((u32)0x00040000)
#define I2C_PRESCALER_32                            ((u32)0x00050000)
#define I2C_PRESCALER_64                            ((u32)0x00060000)
#define I2C_PRESCALER_128                           ((u32)0x00070000)


#define IS_I2C_PRESCALER(PRESCALER)                 ((PRESCALER == I2C_PRESCALER_1) || \
                                                     (PRESCALER == I2C_PRESCALER_2) || \
                                                     (PRESCALER == I2C_PRESCALER_4) || \
                                                     (PRESCALER == I2C_PRESCALER_8) || \
                                                     (PRESCALER == I2C_PRESCALER_16) || \
                                                     (PRESCALER == I2C_PRESCALER_32) || \
                                                     (PRESCALER == I2C_PRESCALER_64) || \
                                                     (PRESCALER == I2C_PRESCALER_128))


#define I2C_MASKBIT_0                               ((u32)0x00000001)
#define I2C_MASKBIT_1                               ((u32)0x00000002)
#define I2C_MASKBIT_2                               ((u32)0x00000003)
#define I2C_MASKBIT_3                               ((u32)0x00000004)
#define I2C_MASKBIT_4                               ((u32)0x00000010)
#define I2C_MASKBIT_5                               ((u32)0x00000020)
#define I2C_MASKBIT_6                               ((u32)0x00000040)
#define I2C_MASKBIT_7                               ((u32)0x00000080)
#define I2C_MASKBIT_8                               ((u32)0x00000100)
#define I2C_MASKBIT_9                               ((u32)0x00000200)


#define IS_I2C_ADDRESS_MASK(MASK)                   ((MASK == I2C_MASKBIT_0) || \
                                                     (MASK == I2C_MASKBIT_1) || \
                                                     (MASK == I2C_MASKBIT_2) || \
                                                     (MASK == I2C_MASKBIT_3) || \
                                                     (MASK == I2C_MASKBIT_4) || \
                                                     (MASK == I2C_MASKBIT_5) || \
                                                     (MASK == I2C_MASKBIT_6) || \
                                                     (MASK == I2C_MASKBIT_7) || \
                                                     (MASK == I2C_MASKBIT_8) || \
                                                     (MASK == I2C_MASKBIT_9))


#define IS_I2C(I2C)                                 ((I2C == AM_I2C0) || (I2C == AM_I2C1))

#define IS_I2C_ADDRESS(ADDRESS)                     (ADDRESS <= 0x3FF)

#define IS_I2C_SPEED(SPEED)                         ((SPEED >= 1) && (SPEED <= 1000000))

#define IS_I2C_SCL_HIGH(HIGH)                       (HIGH <= 0xFFFF)

#define IS_I2C_SCL_LOW(LOW)                         (LOW <= 0xFFFF)

#define IS_I2C_TIMEOUT(TIMEOUT)                     (TIMEOUT <= 0xFFFF)

#define SEQ_FILTER_DISABLE                          ((u32)0x00000000)
#define SEQ_FILTER_1_PCLK                           ((u32)0x00004000)
#define SEQ_FILTER_2_PCLK                           ((u32)0x00008000)

#define IS_I2C_SEQ_FILTER_MASK(CONFIG)              ((CONFIG == SEQ_FILTER_DISABLE) || \
                                                     (CONFIG == SEQ_FILTER_1_PCLK) || \
                                                     (CONFIG == SEQ_FILTER_2_PCLK))

/**
  * @}
  */

void I2C_DeInit(AM_I2C_TypeDef* I2Cx);
void I2C_Init(AM_I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStructure);
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStructure);
void I2C_Cmd(AM_I2C_TypeDef* I2Cx, ControlStatus NewState);
void I2C_GenerateSTOP(AM_I2C_TypeDef* I2Cx);
void I2C_IntConfig(AM_I2C_TypeDef* I2Cx, u32 I2C_Int, ControlStatus NewState);
void I2C_GeneralCallCmd(AM_I2C_TypeDef* I2Cx, ControlStatus NewState);
void I2C_AckCmd(AM_I2C_TypeDef* I2Cx, ControlStatus NewState);
void I2C_SetOwnAddress(AM_I2C_TypeDef* I2Cx, u16 I2C_Address);
void I2C_TargetAddressConfig(AM_I2C_TypeDef* I2Cx, u16 I2C_Address, u32 I2C_Direction);
void I2C_SendData(AM_I2C_TypeDef* I2Cx, u8 I2C_Data);
u8 I2C_ReceiveData(AM_I2C_TypeDef* I2Cx);
u32 I2C_ReadRegister(AM_I2C_TypeDef* I2Cx, u8 I2C_Register);
FlagStatus I2C_GetFlagStatus(AM_I2C_TypeDef* I2Cx, u32 I2C_Flag);
ErrStatus I2C_CheckStatus(AM_I2C_TypeDef* I2Cx, u32 I2C_Status);
void I2C_ClearFlag(AM_I2C_TypeDef* I2Cx, u32 I2C_Flag);
void I2C_SetSCLHighPeriod(AM_I2C_TypeDef* I2Cx, u32 I2C_HighPeriod);
void I2C_SetSCLLowPeriod(AM_I2C_TypeDef* I2Cx, u32 I2C_LowPeriod);
void I2C_PDMACmd(AM_I2C_TypeDef* I2Cx, u32 I2C_PDMAREQ, ControlStatus NewState);
void I2C_PDMANACKCmd(AM_I2C_TypeDef* I2Cx, ControlStatus NewState);
void I2C_TimeOutCmd(AM_I2C_TypeDef* I2Cx, ControlStatus NewState);
void I2C_SetTimeOutValue(AM_I2C_TypeDef* I2Cx, u32 I2C_Timeout);
void I2C_SetTimeOutPrescaler(AM_I2C_TypeDef* I2Cx, u32 I2C_Prescaler);
void I2C_AddressMaskConfig(AM_I2C_TypeDef* I2Cx, u32 I2C_Mask);
u16 I2C_GetAddressBuffer(AM_I2C_TypeDef* I2Cx);
void I2C_CombFilterCmd(AM_I2C_TypeDef* I2Cx, ControlStatus NewState);
void I2C_SequentialFilterConfig(AM_I2C_TypeDef* I2Cx, u32 Seq_Filter_Select);

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