#include <stdint.h>
#include "uart.h"
#include "registers.h"

/**
 * @brief Simple implementation of SysTick_Handler interrupt
 * Beware: this Code is executed in interrupt-context
 */

static uint32_t time;
static uint32_t mainTime;

void resetClock (void)
{
	time = 0;
	uint32_t clocks_to_tick = 800000 - 1;
	writeToRegister(0xE000E014, clocks_to_tick);
	writeToRegister(0xE000E018, 0);
	writeToRegister(0xE000E010, 0x00000007);
}


void SysTick_Handler (void)
{
	time++;
	if (time == 2000)
	{
		printString("20 sek");
		resetClock();
		
	}
	

}


/**
 * This is the Main - Function in C
 */
void main(void)
{
	// Initialize the 10ms Timer to 0
	time = 0;
	mainTime = 0;

	// Cortex_M4_board->freq_mhz = 80MHz
	// 80 000 000 mal / sek
	//     80 000 mal / msek
	//    800 000 mal / 10 msek
	uint32_t clocks_to_tick = 800000 - 1;

	// [31 ... 24]  Reserved, RAZ/WI.
	// [23 ...  0]  RELOAD The value to load into the SYST_CVR when the counter reaches 0.
	writeToRegister(0xE000E014, clocks_to_tick); // SysTick Reload Value Register, SYST_RVR (RW)
	// TODO: Prüfen ob clocks_to_tick in 24-Bit passen!

	// [31:0] CURRENT Current counter value.
	// Any write to the register clears the register to zero!
	writeToRegister(0xE000E018, 0); // SysTick Current Value Register, SYST_CVR (RW)

	// [   31] NOREF  Indicates whether the IMPLEMENTATION DEFINED reference clock is implemented:
	// [   30] SKEW   Indicates whether the 10ms calibration value is exact
	// [29:24] -      Reserved
	// [23: 0] TENMS  Optionally, holds a reload value to be used for 10ms (100Hz) timing
	//ReadFromRegister(0xE000E01C, 0); // SysTick Calibration value Register, SYST_CALIB (RO)

	// 1 x x  CLKSOURCE = 1 SysTick uses the processor clock.
	// x 1 x  TICKINT   = 1 Count to 0 changes the SysTick exception status to pending.
	// x x 1  ENABLE    = 1 Counter is operating.
	writeToRegister(0xE000E010, 0x00000007); // SysTick Control and Status Register, SYST_CSR (RW)

	for(;;)
	{
		mainTime++;
	}
	SysTick_Handler();
}





