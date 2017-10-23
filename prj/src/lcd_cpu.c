#include "user.h"
#include "AM8813.h"
#include "AM8813_misc.h"
#include "ckcu.h"
#include "gpio.h"
#include "lcd.h"
#include "main.h"

extern STATE State[NumMdl];

#define CK_PLL 0
#define CK_AHB  1
#define CK_SYS 2
#define CK_LSE 5
#define CK_LSI 6
#define CK_DEBUG   7

typedef struct 
{
u8 CKOUTSRC;
u8 DB_CKSRC;
u8 DB_CS;		
}	CK_DEBUG_TypeDef;   

void Frequency_output_from_CKOUT(CK_DEBUG_TypeDef CKOUT)
{
	int temp;
	AM_CKCU_TypeDef * pCKCU= AM_CKCU;
  AM_CKCU->GCFGR &= ~(0x7);
	AM_CKCU->GCFGR |= CKOUT.CKOUTSRC;	
	temp=0;
	if(CKOUT.CKOUTSRC==CK_DEBUG)
	{
		
		temp &= ~(0x3<<30);
		temp |= (CKOUT.DB_CKSRC<<30);	
		temp &= 0x3<<30;
		temp |= CKOUT.DB_CS<<(5*CKOUT.DB_CKSRC);
	 	pCKCU->RESERVED1[45] =temp;			
	}
		
		
}
/*
void CLK_ENABLE(void)
{	
	u32 LED_CLK;	
	AM_CKCU_TypeDef * pCKCU= AM_CKCU;
  AM_RSTCU_TypeDef * pRSTCU=AM_RSTCU;
	 //pCKCU->AHBCCR |=0x000408e5;// clock gating		
	pCKCU->AHBCCR |=0x3FE8F5;// clock gating		
	//pCKCU->APBCCR0 |=0x00004000;// clock gating	
	pCKCU->APBCCR0 |=0x107C513;// clock gating	
	pCKCU->APBCCR1 |=0xFF07077F;// clock gating		
}
*/
void LCD_MFP(void)
{
/*	AM_AFIO_TypeDef * pAFIO =AM_AFIO;
//LCD MFP
	pAFIO->GPCCFGR[0] &=~0xf0000fff;
	pAFIO->GPCCFGR[0] |=0xa0000aaa;
	
	pAFIO->GPCCFGR[1] &=~0xffffffff;
	pAFIO->GPCCFGR[1] |= 0xaaaaaaaa;
	
	pAFIO->GPDCFGR[0] &=~0xffffffff;
	pAFIO->GPDCFGR[0] |= 0xaaaaaaaa;
	
	pAFIO->GPDCFGR[1] &=~0xffffffff;
	pAFIO->GPDCFGR[1] |= 0xaaaaaaaa;
	
	pAFIO->GPECFGR[0] &=~0xffffffff;
	pAFIO->GPECFGR[0] |= 0xaaaaaaaa;*/
	
	AFIO_GPCConfig(AFIO_PIN_0|AFIO_PIN_1|AFIO_PIN_2|AFIO_PIN_3|AFIO_PIN_4|AFIO_PIN_5|AFIO_PIN_10|AFIO_PIN_11|AFIO_PIN_12|AFIO_PIN_13,AFIO_MODE_10);
	AFIO_GPDConfig(AFIO_PIN_1|AFIO_PIN_2|AFIO_PIN_8|AFIO_PIN_9|AFIO_PIN_14|AFIO_PIN_15,AFIO_MODE_10);
	AFIO_GPBConfig(AFIO_PIN_6|AFIO_PIN_7|AFIO_PIN_8|AFIO_PIN_12|AFIO_PIN_14,AFIO_MODE_10);
}

int lcd_start(void)
{
	CK_DEBUG_TypeDef CKOUT;	
	AM_CKCU_TypeDef * pCKCU= AM_CKCU;
	
  LCD_MFP( );
  LCD_DeInit();
	
	LCD_SEG_COM0Cmd(ENABLE);
	LCD_SEG_COM1Cmd(ENABLE);
	LCD_SEG_COM2Cmd(ENABLE);
	LCD_SEG_COM3Cmd(ENABLE);
	
	LCD_SEG_COM4Cmd(ENABLE);
	LCD_SEG_COM5Cmd(ENABLE);
	
	LCD_SEG_COM6Cmd(ENABLE);
	LCD_SEG_COM7Cmd(ENABLE);
	
	LCD_ModCmd(CATHODE_RI);
	LCD_LED_SEG_ModeCmd(SEG);
	LCD_DutyCmd(_8DUTY);
	LCD_BiasCmd(_4BIAS);
	LCD_PWM_CNT(ENABLE,0x1f4);
	
  LCD_ANALOGE(ENABLE,0,0);	
  LCD_Enable();
	LCD_DATA0(0X08040200);
	LCD_DATA1(0X00020408);
	LCD_DATA2(0X08040200);
	LCD_DATA3(0X00020408);
	LCD_DATA4(0X08040200);
	LCD_DATA5(0X00020408);
	LCD_DATA6(0X08040200);
	LCD_DATA7(0X00020408);
	
	LCD_Upate( );
	
	State[MdlLcd] = State_StartFinish;	
}

FLAG_PASS_FAIL lcd_ok(void)
{
	return FLAG_PASS;		
}
