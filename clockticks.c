#include <stdint.h>
#include "main.h"
#include "clockticks.h"
#include "uart.h"
#include "registers.h"

/**
 * @brief resets the current value of the time variable and restarts clock
 * 
 */
void resetClock (void)
{
	time = 0;
	uint32_t clocks_to_tick = 800000 - 1;
	writeToRegister(0xE000E014, clocks_to_tick);
	writeToRegister(0xE000E018, 0);
	writeToRegister(0xE000E010, 0x00000007);
}

/**
 * @brief Get the Current Time object
 * 
 * @return int32_t Timevalue
 */
int32_t getCurrentTime() 
{
	return time;
}

/**
 * @brief Counts the value of the time
 * 
 */
void SysTick_Handler (void)
{
	time++;
}

/**
 * @brief Starts the counting of the Clock
 * 
 */
void startClock (void)
{
	time = 0;
	mainTime = 0;
    uint32_t clocks_to_tick = 800000 - 1;
    writeToRegister(0xE000E014, clocks_to_tick);
    writeToRegister(0xE000E018, 0);
    writeToRegister(0xE000E010, 0x00000007);
}