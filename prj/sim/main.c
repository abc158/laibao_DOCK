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

void init_sys(void)
{
	Set_sys_Frequency(24);//system_clk:
	Convert_HSI_to_HSE();
	//Set_sys_Frequency_LSE(24);
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
extern void IR_GPIO_Config(void);
int main(void)
{
	init_sys();
	LED_GPIO_Config();
	IR_GPIO_Config();
	USARTx_Config();
	printf("Amicro TIMer 测试开始：\n");
	printf("测试内容：1.计时器满进中断；2.重装定时器；\n");
	TIM_Mode_Config();
	printf("如果输出成功，则可以在LED1输出引脚看到500Hz的波形\n");
	while(1)
	{
		//LED1_GPIO_PORT->SRR = LED1_PIN;  //Debug指示LED灯
		//if(GPIO_ReadInBit(AM_GPIOB,GPIO_PIN_5)==RESET)
		LED1_GPIO_PORT->RR = LED1_PIN;   //Debug指示LED灯
		Delay_us(10000);
		//LED1_GPIO_PORT->RR = LED1_PIN;
		LED1_GPIO_PORT->SRR = LED1_PIN;
		Delay_us(10000);
	}
}
