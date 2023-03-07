#include <stdint.h>
#include "uart.h"

// =================================================================================================================
// Helper Functions:

/**
 * @brief This Function writes a given 32-Bit value to the given address.
 * 
 * @param address  32-Bit wide Addres
 * @param value    32-Bit Value
 */
void WriteToRegister(uint32_t address, uint32_t value)
{
	uint32_t *pointer_to_address;

	// Assign pointer to given address:
	pointer_to_address = (uint32_t *)address;

	// Write to the End of the Pointer
	*pointer_to_address = value;
}

/**
 * @brief This Function reads a 32-Bit register-value from the given address.
 * 
 * @param address    32-Bit wide Addres
 * @return uint32_t  The value from the given Address
 */
uint32_t ReadFromRegister(uint32_t address)
{
	uint32_t *pointer_to_address;
	uint32_t value;

	// Assign pointer to given address:
	pointer_to_address = (uint32_t *)address;

	// Read from the End of the Pointer
	value = *pointer_to_address;

	// Return the read value
	return value;
}

// =================================================================================================================




static uint32_t time;
static uint32_t mainTime;

/**
 * @brief Simple implementation of SysTick_Handler interrupt
 * Beware: this Code is executed in interrupt-context
 */
void SysTick_Handler (void)
{
	time++;
	if (time == 2000)
	{
		printString("20 sek");
	}
	if (time == 4000)
	{
		printString("40 sek");
	}
	if (time == 6000)
	{
		printString("60 sek");
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
	WriteToRegister(0xE000E014, clocks_to_tick); // SysTick Reload Value Register, SYST_RVR (RW)
	// TODO: Prüfen ob clocks_to_tick in 24-Bit passen!

	// [31:0] CURRENT Current counter value.
	// Any write to the register clears the register to zero!
	WriteToRegister(0xE000E018, 0); // SysTick Current Value Register, SYST_CVR (RW)

	// [   31] NOREF  Indicates whether the IMPLEMENTATION DEFINED reference clock is implemented:
	// [   30] SKEW   Indicates whether the 10ms calibration value is exact
	// [29:24] -      Reserved
	// [23: 0] TENMS  Optionally, holds a reload value to be used for 10ms (100Hz) timing
	//ReadFromRegister(0xE000E01C, 0); // SysTick Calibration value Register, SYST_CALIB (RO)

	// 1 x x  CLKSOURCE = 1 SysTick uses the processor clock.
	// x 1 x  TICKINT   = 1 Count to 0 changes the SysTick exception status to pending.
	// x x 1  ENABLE    = 1 Counter is operating.
	WriteToRegister(0xE000E010, 0x00000007); // SysTick Control and Status Register, SYST_CSR (RW)

	for(;;)
	{
		mainTime++;
	}
	SysTick_Handler();
}





