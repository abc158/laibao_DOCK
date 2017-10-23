/********************************************************************************************************//**
 * @file    main.c
 * @brief   GPIO & SysTick & USART TEST
 * @author  Amicro
 * @version V1.00
 * @date:   2017.3.27
 * @note		1.计时器满进中断；2.进中断Toggle LED1的引脚；
 * Copyright (C) 2017 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
#include "main.h"
#include "system.h"
#include "AM8813.h"
#include "AM8813_misc.h"
#include "ckcu.h"
#include "gpio.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_timer.h"
#include "bsp_spi.h" 
#include "ui-ir.h"
#define   UINT8			uint8_t
#define WR_TX_PLOAD     0xA0  // Define TX payload register address
#define W_TX_PAYLOAD_NOACK_CMD	0xb0
void init_sys(void)
{
	Set_sys_Frequency(24);//system_clk:
	Convert_HSI_to_HSE();
	SystemInit();
//CKCU_AHBPeripClockConfig(CKCU_AHBEN_PA,ENABLE);  		//Clock for UART0/UART2
  CKCU_AHBPeripClockConfig(CKCU_AHBEN_PB,ENABLE);  		//Clock for UART3
	CKCU_AHBPeripClockConfig(CKCU_AHBEN_PC,ENABLE);  		//Clock for LEDx/UART0/UART4
	CKCU_AHBPeripClockConfig(CKCU_AHBEN_PD,ENABLE);  		//Clock for UART1/UART5
//CKCU_AHBPeripClockConfig(CKCU_AHBEN_PE,ENABLE);  		//Clock for ...
	
	CKCU_APBPerip0ClockConfig(CKCU_APBEN0_AFIO,ENABLE); 	//Clock for GPIO Others Function	
//CKCU_AHBPeripClockConfig(CKCU_AHBEN_PDMA,ENABLE);			//DMA Clock
	CKCU_APBPerip1ClockConfig(CKCU_APBEN1_GPTM0, ENABLE);	//Clock for TIM0
	CKCU_APBPerip1ClockConfig(CKCU_APBEN1_GPTM1, ENABLE);	//Clock for TIM1
	CKCU_APBPerip1ClockConfig(CKCU_APBEN1_GPTM2, ENABLE);	//Clock for TIM2
	CKCU_APBPerip1ClockConfig(CKCU_APBEN1_GPTM3, ENABLE);	//Clock for TIM3
	CKCU_APBPerip0ClockConfig(CKCU_APBEN0_SPI0,ENABLE);    //Clock for SPI0
	CKCU_APBPerip0ClockConfig(CKCU_APBEN0_SPI1,ENABLE);    //Clock for SPI1
	CKCU_APBPerip0ClockConfig(CKCU_APBEN0_EXTI,ENABLE);		//Clock for Interrupt
	
	#if defined (BSP_USART0_BAUDRATE) 
		CKCU_APBPerip0ClockConfig(CKCU_APBEN0_USART0,ENABLE);		//Clock for USART0
	#endif
	#if defined (BSP_USART2_BAUDRATE) 
		CKCU_APBPerip0ClockConfig(CKCU_APBEN0_USART2,ENABLE);		//Clock for USART2
	#endif
	#if defined (BSP_USART4_BAUDRATE) 
		CKCU_APBPerip0ClockConfig(CKCU_APBEN0_USART4,ENABLE);		//Clock for USART4
	#endif
	#if defined (BSP_USART5_BAUDRATE) 
		CKCU_APBPerip0ClockConfig(CKCU_APBEN0_USART5,ENABLE);		//Clock for USART5
	#endif
	#if defined (BSP_USART1_BAUDRATE) 
		CKCU_APBPerip1ClockConfig(CKCU_APBEN1_USART1,ENABLE);		//Clock for USART1
	#endif
	#if defined (BSP_USART3_BAUDRATE) 
		CKCU_APBPerip1ClockConfig(CKCU_APBEN1_USART3,ENABLE);		//Clock for USART3
	#endif
}
extern uint8_t Get_Chip_ID(void);
extern void BK2425_Initialize(void);
extern void Receive_Packet();
extern REMOTE_DECODE remote_decode[REMOTE_DECODER_MAX];
int main(void)
{
	init_sys();
	LED_GPIO_Config();
	IR_GPIO_Config();
	USARTx_Config();
	SPI0_Init();
	TIM_Mode_Config();
	BK2425_Initialize();
	printf("chip id = %d \r\n",Get_Chip_ID());
	LED1_GPIO_PORT->RR = LED1_PIN;   //Debug指示LED灯
	while(1)
	{
//		uint8_t i;
//		for(i=0;i<6;n++)
//		{
//			if((remote_decode[n].rxByte==(BACK_LEFT_WEAK))||
//				(remote_decode[n].rxByte==(BACK_RIGHT_WEAK))||\
//				(remote_decode[n].rxByte==(LEFT_WEAK))||\
//				(remote_decode[n].rxByte==(RIGHT_WEAK))||\
//				(remote_decode[n].rxByte==(MIDDLE_WEAK)))
//			
//			n=1;
//				else	if((remote_decode[n].rxByte==BACK_LEFT_STRONG)||
//				(remote_decode[n].rxByte==BACK_RIGHT_STRONG)||\
//				(remote_decode[n].rxByte==LEFT_STRONG)||\
//				(remote_decode[n].rxByte==RIGHT_STRONG)||\
//				(remote_decode[n].rxByte==MIDDLE_STRONG))
//			n=10;
//		  else n=0;
//		LED1_GPIO_PORT->RR = LED1_PIN;   //Debug指示LED灯
//		Delay_us(5000*n);
//		LED1_GPIO_PORT->SRR = LED1_PIN;
//		Delay_us(5000*n);
//	  printf("signal_code %x \r\n",remote_decode[n].rxByte);
//		}
   	LED1_GPIO_PORT->RR = LED1_PIN;   //Debug指示LED灯
		Delay_us(10000);
		LED1_GPIO_PORT->SRR = LED1_PIN;
		Delay_us(10000);
		

	}
}
