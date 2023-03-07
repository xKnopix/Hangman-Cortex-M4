#ifndef CLOCKTICKS_H
#define CLOCKTICKS_H

#include <stdint.h>
//#include "main.h"
//#include "uart.h"
//#include "registers.h"

uint32_t time;
uint32_t mainTime;

void resetClock (void);
int32_t getCurrentTime();
void SysTick_Handler (void);
void startClock (void);

#endif