/********************************************************************************************************//**
 * @file    lcd.h	
 * @brief   The header file of the Lcd Unit library.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __LCD_H
#define __LCD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "AM8813.h"

typedef enum {SEG = 0, LED= !SEG} LCD_LED_SEG_MODE;

/**
 * @brief  Enumeration of LED Common Mode.
 */
typedef enum 
{
  COM_ANODE = 0, 								/*!< led common anode */
  COM_CATHODE = !COM_ANODE			/*!< led common cathode */
}LED_COM_MODE;

typedef enum 
{
	ROW_INVERT = 0, 	
	FRAME_INVERT = !ROW_INVERT
}LCD_MOD;

typedef enum 
{
	BIAS2 = 1, 										/*!< lcd 1/2 bias */
	BIAS3,												/*!< lcd 1/3 bias */
	BIAS4													/*!< lcd 1/4 bias */
}LCD_BIAS;

typedef enum 
{
	DUTY2 = 1, 										/*!< lcd 1/2 duty */
	DUTY3,												/*!< lcd 1/3 bias */
	DUTY4,												/*!< lcd 1/4 bias */
	DUTY5,												/*!< lcd 1/5 bias */
	DUTY6,												/*!< lcd 1/6 bias */
	DUTY7													/*!< lcd 1/7 bias */
}LCD_DUTY;

typedef enum 
{
	LCD_SEG0 = 1, LCD_SEG1,	LCD_SEG2,	LCD_SEG3, LCD_SEG4,	LCD_SEG5, LCD_SEG6, LCD_SEG7,	
	LCD_SEG8, LCD_SEG9, LCD_SEG10, LCD_SEG11, LCD_SEG12, LCD_SEG13, LCD_SEG14, LCD_SEG15,
	LCD_SEG16, LCD_SEG17, LCD_SEG18, LCD_SEG19, LCD_SEG20, LCD_SEG21, LCD_SEG22, LCD_SEG23,
	LCD_SEG24, LCD_SEG25, LCD_SEG26, LCD_SEG27, LCD_SEG28, LCD_SEG29, LCD_SEG30, LCD_SEG31
}LCD_SEGX;

/* Definitions of AFIO_PIN */
#define LED_COM0   (u32)0x00000001 		/*!< LED COM0 selected */
#define LED_COM1   (u32)0x00000002 		/*!< LED COM1 selected */
#define LED_COM2   (u32)0x00000004 		/*!< LED COM2 selected */
#define LED_COM3   (u32)0x00000008 		/*!< LED COM3 selected */
#define LED_COM4   (u32)0x00000010 		/*!< LED COM4 selected */
#define LED_COM5   (u32)0x00000020 		/*!< LED COM5 selected */
#define LED_COM6   (u32)0x00000040 		/*!< LED COM6 selected */
#define LED_COM7   (u32)0x00000080 		/*!< LED COM7 selected */


void LCD_DeInit(void);
void LED_Init(LED_COM_MODE Mode, u32 Led_Comx);
void LED_Seg_Data(u8 SegData, u32 Led_Comx);
void LED_Updata(void);
FlagStatus LED_Updata_Status(void);
void LED_Config(ControlStatus Cmd);
void LCD_PWM_CNT(EventStatus Cmd,u16 PWM_CNT);
void LCD_Init(LCD_MOD Mode, LCD_BIAS Bias, LCD_DUTY Duty);
void LCD_Updata(void);
FlagStatus LCD_Updata_Status(void);
void LCD_Config(ControlStatus Cmd);
void LCD_Com_Data(u8 SegData, LCD_SEGX Segx);
	

#ifdef __cplusplus
}
#endif

#endif 
