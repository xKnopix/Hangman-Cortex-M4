#ifndef CLOCKTICKS_H
#define CLOCKTICKS_H

#include <stdint.h>

static uint32_t time;
static uint32_t mainTime;

void resetClock (void);
int32_t getCurrentTime();
void SysTick_Handler (void);
void startClock (void);

#endif