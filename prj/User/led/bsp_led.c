/********************************************************************************************************//**
 * @file    bsp_led.c
 * @brief   GPIO Led Driver
 * @author  Amicro
 * @version V1.00
 * @date:   2017-3-11
 * @note		LEDx(y); ... x can be 1-3 ... y can be ON or OFF ...
 *					LED_Toggle(x); ... x can be RED or GREEN or BLUE ...
 * Copyright (C) 2017 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
#include "bsp_led.h"   

 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void LED_GPIO_Config(void)
{		
	/* LED1 */
	GPIO_DirectionConfig(LED1_GPIO_PORT,LED1_PIN,GPIO_DIR_OUT);  //设置引脚模式为输出模式
	GPIO_PullResistorConfig(LED1_GPIO_PORT,LED1_PIN,GPIO_PR_UP); //设置引脚为上拉模式
	//GPIO_InputConfig(LED1_GPIO_PORT,LED1_PIN,ENABLE);
	GPIO_DriveConfig(LED1_GPIO_PORT,LED1_PIN,GPIO_DV_6MA);  //设置引脚的输出类型为6mA输出
	GPIO_OpenDrainConfig(LED1_GPIO_PORT,LED1_PIN,DISABLE);  //关闭开漏输出
	
	/* LED2 */
	GPIO_DirectionConfig(LED2_GPIO_PORT,LED2_PIN,GPIO_DIR_OUT);  //设置引脚模式为输出模式
	GPIO_PullResistorConfig(LED2_GPIO_PORT,LED2_PIN,GPIO_PR_UP); //设置引脚为上拉模式
	//GPIO_InputConfig(LED2_GPIO_PORT,LED2_PIN,ENABLE);
	GPIO_DriveConfig(LED2_GPIO_PORT,LED2_PIN,GPIO_DV_6MA);  //设置引脚的输出类型为6mA输出
	GPIO_OpenDrainConfig(LED2_GPIO_PORT,LED2_PIN,DISABLE);  //关闭开漏输出
	
	/* LED3 */
	GPIO_DirectionConfig(LED3_GPIO_PORT,LED3_PIN,GPIO_DIR_OUT);  //设置引脚模式为输出模式
	GPIO_PullResistorConfig(LED3_GPIO_PORT,LED3_PIN,GPIO_PR_UP); //设置引脚为上拉模式
	//GPIO_InputConfig(LED3_GPIO_PORT,LED3_PIN,ENABLE);
	GPIO_DriveConfig(LED3_GPIO_PORT,LED3_PIN,GPIO_DV_6MA);  //设置引脚的输出类型为6mA输出
	GPIO_OpenDrainConfig(LED3_GPIO_PORT,LED3_PIN,DISABLE);  //关闭开漏输出
	
	LED1(OFF);LED2(OFF);LED3(OFF);
}

void IR_GPIO_Config(void)
{		
	GPIO_DirectionConfig(AM_GPIOC,GPIO_PIN_4,GPIO_DIR_IN);  
	GPIO_PullResistorConfig(AM_GPIOC,GPIO_PIN_4,GPIO_PR_UP); 
  GPIO_InputConfig(AM_GPIOC,GPIO_PIN_4,ENABLE);
	
  GPIO_DirectionConfig(AM_GPIOB,GPIO_PIN_4,GPIO_DIR_IN);  
	GPIO_PullResistorConfig(AM_GPIOB,GPIO_PIN_4,GPIO_PR_UP); 
  GPIO_InputConfig(AM_GPIOB,GPIO_PIN_4,ENABLE);
	
	GPIO_DirectionConfig(AM_GPIOB,GPIO_PIN_5,GPIO_DIR_IN);  
	GPIO_PullResistorConfig(AM_GPIOB,GPIO_PIN_5,GPIO_PR_UP); 
  GPIO_InputConfig(AM_GPIOB,GPIO_PIN_5,ENABLE);
	
	GPIO_DirectionConfig(AM_GPIOB,GPIO_PIN_6,GPIO_DIR_IN);  
	GPIO_PullResistorConfig(AM_GPIOB,GPIO_PIN_6,GPIO_PR_UP); 
  GPIO_InputConfig(AM_GPIOB,GPIO_PIN_6,ENABLE);
	
	GPIO_DirectionConfig(AM_GPIOC,GPIO_PIN_11,GPIO_DIR_IN);  
	GPIO_PullResistorConfig(AM_GPIOC,GPIO_PIN_11,GPIO_PR_UP); 
  GPIO_InputConfig(AM_GPIOC,GPIO_PIN_11,ENABLE);

  GPIO_DirectionConfig(AM_GPIOD,GPIO_PIN_8,GPIO_DIR_OUT);  
	GPIO_PullResistorConfig(AM_GPIOD,GPIO_PIN_8,GPIO_PR_UP); 
  GPIO_InputConfig(AM_GPIOD,GPIO_PIN_8,ENABLE);
	
	GPIO_DirectionConfig(AM_GPIOD,GPIO_PIN_4,GPIO_DIR_OUT);  
	GPIO_PullResistorConfig(AM_GPIOD,GPIO_PIN_4,GPIO_PR_UP); 
  GPIO_InputConfig(AM_GPIOD,GPIO_PIN_4,ENABLE);
}

void LED_Toggle(LED_TypeDef Light)
{
	assert_param(IS_LED_TypeDef(Light));
	if(Light==RED)
	{
		if(GPIO_ReadOutBit(LED1_GPIO_PORT,LED1_PIN)==SET)
			LED1(ON);
		else 
			LED1(OFF);
	}
	else if(Light==GREEN)
	{
		if(GPIO_ReadOutBit(LED2_GPIO_PORT,LED2_PIN)==SET)
			LED2(ON);
		else 
			LED2(OFF);
	}
	else if(Light==BLUE)
	{
		if(GPIO_ReadOutBit(LED3_GPIO_PORT,LED3_PIN)==SET)
			LED3(ON);
		else 
			LED3(OFF);
	}
}

/*********************************************END OF FILE**********************/
