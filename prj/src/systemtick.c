#include "user.h"
#include "main.h"
#include "AM8813.h"
#include "ckcu.h"
#include "gpio.h"
#include "rstcu.h"
#include "AM8813_misc.h"

extern STATE State[NumMdl];

int tick_count=0;

void systick_interrupt_req(void)
{
	tick_count++;
	if(tick_count == 10)
	{
		State[MdlSystick] = State_StartFinish;
	}
}

FLAG_PASS_FAIL systick_ok(void)
{
	tick_count = 0;
	return FLAG_PASS;
}

void systick_start(void)
{
  AM_CKCU_TypeDef* pCKCU= AM_CKCU;
  int data,data1;
  int i,j;

	State[MdlSystick] = State_Continue;	

  /* SYSTICK configuration */
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK); // Default : 9MHz on chip
	SysTick_SetReloadValue(24000);
	SysTick_IntConfig(ENABLE);
	SysTick_CounterCmd(SYSTICK_COUNTER_ENABLE);	
}

