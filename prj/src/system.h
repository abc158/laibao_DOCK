#ifndef __SYSTEM_H
#define __SYSTEM_H
#include "AM8813.h"

void SystemInit(void);
void Delay_us(__IO u32 nTime);
void Delay_ms(__IO u32 nTime);
void SystemCoreClockUpdate(void);

#endif /* _SYSTEM_H */
