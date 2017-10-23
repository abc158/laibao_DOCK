/********************************************************************************************************//**
 * @file    flash.h	
 * @brief   The header file of the Flash Control Unit library.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
 
#ifndef __FLASH_H
#define __FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "AM8813.h"

#define WORD_PROG_MAIN       1
#define PAGE_ERASE_MAIN      2
#define READ_MAIN            3
#define WORD_PROG_INFO       4
#define PAGE_ERASE_INFO      5
#define READ_INFO            6
#define MASS_ERASE           8
#define CMD_COMMIT           0xA

/**
  * @}
  */


ErrorStatus FLASH_Prog(unsigned int Addr,unsigned int Data,ControlStatus Sta);
ErrorStatus FLASH_Prog_Nvr(unsigned int Addr,unsigned int Data,ControlStatus Sta);
ErrorStatus FLASH_Page_Erase(unsigned int PageAddr,ControlStatus Sta);
ErrorStatus FLASH_Page_Erase_Nvr(unsigned int PageAddr,ControlStatus Sta);
u32 FLASH_Isp_Read(unsigned int Addr);
u32 FLASH_Isp_Read_Nvr(unsigned int Addr);
ErrorStatus FLASH_Mass_Erase(ControlStatus Sta);
void FLASH_Err_Irq(void);

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
