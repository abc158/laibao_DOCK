/********************************************************************************************************//**
 * @file    flash.c
 * @brief   This file provides all the Flash Control Unit firmware functions.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
 
#include "flash.h"

u8 write_err_flag = 0;
u8 addr_ov_flag = 0;

/*********************************************************************************************************//**
 * @brief Program main flash, and optional verify.
 * @param Addr: specify the program address, which should be word aligned.
 * @param Data: specify the program data to the specific addr.
 * @param Sta: specify the verify status. This parameter can be ENABLE or DISABLE.
 * @retval verify status if verify.
 ************************************************************************************************************/
ErrorStatus FLASH_Prog(unsigned int Addr,unsigned int Data,ControlStatus Sta)
{
	while((AM_FLASH->OSR & 1) != 0);
	AM_FLASH->TADR = Addr;
	AM_FLASH->WRDR = Data;
	AM_FLASH->OCMR = WORD_PROG_MAIN;
	AM_FLASH->OPCR = CMD_COMMIT;
	while((AM_FLASH->OSR & 1) != 0);
	if(Sta==ENABLE)
	{
		if((*(unsigned int *)Addr) != Data)
			return ERROR;
	}
	return SUCCESS;
}

/*********************************************************************************************************//**
 * @brief Program nvr flash, and optional verify.
 * @param Addr: specify the program address, which should be word aligned.
 * @param Data: specify the program data to the specific addr.
 * @param Sta: specify the verify status. This parameter can be ENABLE or DISABLE.
 * @retval verify status if verify.
 ************************************************************************************************************/
ErrorStatus FLASH_Prog_Nvr(unsigned int Addr,unsigned int Data,ControlStatus Sta)
{
	while((AM_FLASH->OSR & 1) != 0);
	AM_FLASH->TADR = Addr;
	AM_FLASH->WRDR = Data;
	AM_FLASH->OCMR = WORD_PROG_INFO;
	AM_FLASH->OPCR = CMD_COMMIT;
	while((AM_FLASH->OSR & 1) != 0);
	if(Sta==ENABLE)
	{
		if((*(unsigned int *)Addr) != Data)
			return ERROR;
	}
	return SUCCESS;
}
/*********************************************************************************************************//**
 * @brief Erase main flash, and optional verify.
 * @param Addr: specify the program address, which should be word aligned.
 * @param Sta: specify the verify status. This parameter can be ENABLE or DISABLE.
 * @retval verify status if verify.
 ************************************************************************************************************/
ErrorStatus FLASH_Page_Erase(unsigned int PageAddr,ControlStatus Sta)
{
	unsigned int i;
	unsigned int Addr;
	while((AM_FLASH->OSR & 1) != 0);
	AM_FLASH->TADR = PageAddr;
	AM_FLASH->OCMR = PAGE_ERASE_MAIN;
	AM_FLASH->OPCR = CMD_COMMIT;
	while((AM_FLASH->OSR & 1) != 0);
	if(Sta==ENABLE)
	{
		for(i=0;i<128;i++)
		{
			Addr = PageAddr*0x200 + 4*i;
			if((*(unsigned int *)Addr) != 0xFFFFFFFF)
				return ERROR;
		}
	}
	return SUCCESS;
}
/*********************************************************************************************************//**
 * @brief Erase nvr flash, and optional verify.
 * @param Addr: specify the program address, which should be word aligned.
 * @param Sta: specify the verify status. This parameter can be ENABLE or DISABLE.
 * @retval verify status if verify.
 ************************************************************************************************************/
ErrorStatus FLASH_Page_Erase_Nvr(unsigned int PageAddr,ControlStatus Sta)
{
	unsigned int i;
	unsigned int Addr;
	while((AM_FLASH->OSR & 1) != 0);
	AM_FLASH->TADR = PageAddr;
	AM_FLASH->OCMR = PAGE_ERASE_INFO;
	AM_FLASH->OPCR = CMD_COMMIT;
	while((AM_FLASH->OSR & 1) != 0);
	if(Sta==ENABLE)
	{
		for(i=0;i<128;i++)
		{
			Addr = PageAddr*0x200 + 4*i;
			if((*(unsigned int *)Addr) != 0xFFFFFFFF)
				return ERROR;
		}
	}
	return SUCCESS;
}
/*********************************************************************************************************//**
 * @brief flash isp read.
 * @param Addr: specify the program address, which should be word aligned.
 ************************************************************************************************************/
u32 FLASH_Isp_Read(unsigned int Addr)
{
	while((AM_FLASH->OSR & 1) != 0);
	AM_FLASH->TADR = Addr;
	AM_FLASH->OCMR = READ_MAIN;
	AM_FLASH->OPCR = CMD_COMMIT;
	while((AM_FLASH->OSR & 1) != 0);
	return (AM_FLASH->RDDR);
}
/*********************************************************************************************************//**
 * @brief flash isp read nvr.
 * @param Addr: specify the program address, which should be word aligned.
 ************************************************************************************************************/
u32 FLASH_Isp_Read_Nvr(unsigned int Addr)
{
	while((AM_FLASH->OSR & 1) != 0);
	AM_FLASH->TADR = Addr;
	AM_FLASH->OCMR = READ_INFO;
	AM_FLASH->OPCR = CMD_COMMIT;
	while((AM_FLASH->OSR & 1) != 0);
	return (AM_FLASH->RDDR);
}
/*********************************************************************************************************//**
 * @brief flash mass erase.
 * @param Sta: specify the verify status. This parameter can be ENABLE or DISABLE.
 ************************************************************************************************************/
ErrorStatus FLASH_Mass_Erase(ControlStatus Sta)
{
	unsigned int i;
	unsigned int Addr,PageAddr=0;
	while((AM_FLASH->OSR & 1) != 0);
	AM_FLASH->OCMR = MASS_ERASE;
	AM_FLASH->OPCR = CMD_COMMIT;
	while((AM_FLASH->OSR & 1) != 0);
	if(Sta==ENABLE)
	{
		for(PageAddr=0;PageAddr<128;PageAddr++)
		{
			for(i=0;i<128;i++)
			{
				Addr = PageAddr*0x200 + 4*i;
				if((*(unsigned int *)Addr) != 0xFFFFFFFF)
					return ERROR;
			}
		}
	}
	return SUCCESS;	
}

/*********************************************************************************************************//**
 * @brief flash error interrupt.
 ************************************************************************************************************/
void FLASH_Err_Irq(void)
{
	if((AM_FLASH->OSR & 0x10) == 0x10)
	{
		write_err_flag = 1;
		AM_FLASH->OSR &= ~(0x10);
	}
	if((AM_FLASH->OSR & 0x20) == 0x20)
	{
		addr_ov_flag = 1;
		AM_FLASH->OSR &= ~(0x20);
	}
}

/**
  * @}
  */
