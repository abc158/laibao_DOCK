/********************************************************************************************************//**
 * @file    lcd.c	
 * @brief   The c file of the Lcd Unit firmware functions.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
 
#include "lcd.h"


/*********************************************************************************************************//**
 * @brief  Deinitialize the LED registers to the reset values.
 * @retval None
 ************************************************************************************************************/
void LCD_DeInit(void)
{
  /* Reset system clock */
  AM_LCD->LCD_CTRL = 0x00230000;                                              
  AM_LCD->LCD_DATA0 = 0x0;                                                 
  AM_LCD->LCD_DATA1 = 0x0;   
  AM_LCD->LCD_DATA2 = 0x0;                                              
  AM_LCD->LCD_DATA3 = 0x0;                                                 
  AM_LCD->LCD_DATA4 = 0x0;   
  AM_LCD->LCD_DATA5 = 0x0;                                              
  AM_LCD->LCD_DATA6 = 0x0;                                                 
  AM_LCD->LCD_DATA7 = 0x0;   	
	AM_LCD->PWM_CNT = 0x80003000;                                                 
  AM_LCD->LCD_ANALOGE = 0x00000010;   	
}

/*********************************************************************************************************//**
 * @brief Led Init.
 * @param Mode: mode select, common anode or cathode. 
 *        This parameter can be:
 *        @arg COM_ANODE, COM_CATHODE.
 * @param Led_Comx: This parameter can be any combination of LED_COMx where x can be 0 ~ 7.
 * @retval None
 ************************************************************************************************************/
void LED_Init(LED_COM_MODE Mode, u32 Led_Comx)
{
	AM_LCD->LCD_CTRL |= (1<<30);				// led mode select
	AM_LCD->LCD_CTRL = (AM_LCD->LCD_CTRL & (~(1<<24))) | (Mode<<24);		// led common anode or cathode
	AM_LCD->LCD_CTRL = (AM_LCD->LCD_CTRL & (~(0xff))) | Led_Comx; // led oomx (x=0~7) enable
}

/*********************************************************************************************************//**
 * @brief Led Seg Data.
 * @param SegData: 8bit data for seg7~0. 
 * @param Led_Comx: This parameter can be any combination of LED_COMx where x can be 0 ~ 7.
 * @retval None
 ************************************************************************************************************/
void LED_Seg_Data(u8 SegData, u32 Led_Comx)
{
	u8 i;
	for(i=0;i<6;i++)
	{
		if( ((Led_Comx>>i)&0x01) != 0 )
			break;
	}
	if(i<6)
	{
		if(i<4)
		{
			AM_LCD->LCD_DATA0 = (AM_LCD->LCD_DATA0 & (~(0xff<<(i*8)))) | (SegData<<(i*8));
		}
		else
		{
			AM_LCD->LCD_DATA1 = (AM_LCD->LCD_DATA1 & (~(0xff<<((i-4)*8)))) | (SegData<<((i-4)*8));
		}
	}
}
/*********************************************************************************************************//**
 * @brief Led Update Data.
 * @param None
 * @retval None
 ************************************************************************************************************/
void LED_Updata(void)
{
	AM_LCD->LCD_CTRL |= ((u32)1<<31);
}
 
/*********************************************************************************************************//**
 * @brief Led Update Data Status.
 * @param None
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus LED_Updata_Status(void)
{
	if( (AM_LCD->LCD_CTRL &= ((u32)1<<31)) == 0 )
		return RESET;			//not update yet
	else 
		return SET;				//update completely
}

/*********************************************************************************************************//**
 * @brief Led Enable or Disable Confige.
 * @param Cmd: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void LED_Config(ControlStatus Cmd)
{
	AM_LCD->LCD_ENABLE = (AM_LCD->LCD_ENABLE & (~(0x01))) | Cmd;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable, and configure LCD PWM function.
 * @param PWM_CNT: PWM High level counter, High level time = PWM_CNT*AHB period. 
 *        This parameter can be:
 *        @arg CKCU_AHBEN_FMC,CKCU_AHBEN_PDMA,CKCU_AHBEN_CRC,CKCU_AHBEN_PA,CKCU_AHBEN_PB,CKCU_AHBEN_PC,
 *             CKCU_AHBEN_PD,CKCU_AHBEN_PE,CKCU_AHBEN_CAN,CKCU_AHBEN_CAN1.
 * @param Cmd: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void LCD_PWM_CNT(EventStatus Cmd,u16 PWM_CNT)
{
 	AM_LCD->PWM_CNT &= ~((u32)1<<31|0XFFFF);
	AM_LCD->PWM_CNT |= Cmd<<31|PWM_CNT;
}

/*********************************************************************************************************//**
 * @brief Lcd Init.
 * @param LCD_MOD: mode select, row-invert or frame-invert. 
 *        This parameter can be:
 *        @arg ROW_INVERT, FRAME_INVERT.
 * @param LCD_BIAS: This parameter can be BIASx, x=2~4.
 * @param LCD_DUTY: This parameter can be DUTYx, x=2~7.
 * @retval None
 ************************************************************************************************************/
void LCD_Init(LCD_MOD Mode, LCD_BIAS Bias, LCD_DUTY Duty)
{
	AM_LCD->LCD_CTRL &= (~(1<<30));				// lCd mode select
	AM_LCD->LCD_CTRL = (AM_LCD->LCD_CTRL & (~(1<<24))) | (Mode<<24);		// lcd row-invert or frame-invert. 
	AM_LCD->LCD_CTRL = (AM_LCD->LCD_CTRL & (~(0xf<<16))) | (Duty<<16); // led oomx (x=0~7) enable
}

/*********************************************************************************************************//**
 * @brief Lcd Update Data.
 * @param None
 * @retval None
 ************************************************************************************************************/
void LCD_Updata(void)
{
	LED_Updata();
}

/*********************************************************************************************************//**
 * @brief Lcd Update Data Status.
 * @param None
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus LCD_Updata_Status(void)
{
	return LED_Updata_Status();
}

/*********************************************************************************************************//**
 * @brief Lcd Enable or Disable Confige.
 * @param Cmd: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void LCD_Config(ControlStatus Cmd)
{
	LED_Config(Cmd);
}

/*********************************************************************************************************//**
 * @brief Lcd Com[7:0] of Segx(x=0~31) Data.
 * @param SegData: 8bit data for seg7~0. 
 * @param Segx: This parameter can be LCD_SEGX where x can be 0 ~ 31.
 * @retval None
 ************************************************************************************************************/
void LCD_Com_Data(u8 SegData, LCD_SEGX Segx)
{
	u8 i, reg_off, reg_in_off;
	volatile uint32_t *pt = &AM_LCD->LCD_DATA0;
	
	if(i<32)
	{
		reg_off = Segx/4;
		reg_in_off = Segx&4;
		
		*(pt+reg_off) = (*(pt+reg_off) & (~(0xff<<(reg_in_off*8)))) | (Segx<<(reg_in_off*8));
	}
}




























