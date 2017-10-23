/********************************************************************************************************//**
 * @file    user.c
 * @brief   user define
 * @version V0.00
 * @date:   2016-09-02
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
 
#include "AM8813.h"
#include "usart.h"
#include "gptm.h"
#include "bsp_led.h"

//#define WHOLECHIPSIM
//#define DBG_WHOLECHIP_PRINT
typedef uint32_t							FLAG_PASS_FAIL;
#define FLAG_PASS							0
#define FLAG_FAIL							1

extern void pass(void);
extern void fail(void);
extern void cpu_delay(unsigned int tns);		
extern void switch_to_pll(void);
extern void print(char a[],int nu);
