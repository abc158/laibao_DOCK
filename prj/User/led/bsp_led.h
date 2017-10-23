/********************************************************************************************************//**
 * @file    bsp_led.h	
 * @brief   The header file of the bsp_led.
 * @author  Amicro
 * @version V1.00
 * @date:   2017-3-11
 * @note		LED1->PC1;	LED2->PC4;	LED3->PC5
 * Copyright (C) 2017 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
#ifndef __LED_H
#define	__LED_H

#include "AM8813.h"
#include "gpio.h"
#define assert_param(expr) ((void)0)
#define IS_LED_TypeDef(Type) (((Type) == RED) || ((Type) == GREEN) || ((Type) == BLUE))

//���Ŷ���
/*******************************************************/
//R ��ɫ��
#define LED1_PIN                  GPIO_PIN_8
#define LED1_GPIO_PORT            AM_GPIOB

//G ��ɫ��
#define LED2_PIN                  GPIO_PIN_11
#define LED2_GPIO_PORT            AM_GPIOC

//B ��ɫ��
#define LED3_PIN                  GPIO_PIN_5
#define LED3_GPIO_PORT            AM_GPIOC
/************************************************************/

typedef enum
{
	RED=0,
	GREEN=1,
	BLUE=2
}LED_TypeDef;

/** ����LED������ĺ꣬
	* LED�͵�ƽ��������ON=0��OFF=1
	* ��LED�ߵ�ƽ�����Ѻ����ó�ON=1 ��OFF=0 ����
	*/
#define ON  0
#define OFF 1

/* ���κ꣬��������������һ��ʹ�� */
#define LED1(a)	if (a)	\
					LED1_GPIO_PORT->SRR = LED1_PIN;\
					else		\
					LED1_GPIO_PORT->RR = LED1_PIN

#define LED2(a)	if (a)	\
					GPIO_SetOutBits(LED2_GPIO_PORT,LED2_PIN);\
					else		\
					GPIO_ClearOutBits(LED2_GPIO_PORT,LED2_PIN)

#define LED3(a)	if (a)	\
					GPIO_SetOutBits(LED3_GPIO_PORT,LED3_PIN);\
					else		\
					GPIO_ClearOutBits(LED3_GPIO_PORT,LED3_PIN)

void LED_GPIO_Config(void);
void LED_Toggle(LED_TypeDef Light);
void IR_GPIO_Config(void);					
#endif /* __LED_H */
