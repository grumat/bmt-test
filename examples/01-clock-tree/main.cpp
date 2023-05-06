#include <bmt.h>

using namespace Bmt;


#ifdef STM32F103xB
#	include "hal.f103.h"
	// Perform many static validations for GPIO
#	include "Validate.F103.h"
#elif defined(STM32L432xx)
#	include "hal.l432.h"
	// Perform many static validations for GPIO
#	include "Validate.L432.h"
#elif defined(STM32G431xx)
#	include "hal.g431.h"
	// Perform many static validations for GPIO
#	include "Validate.G431.h"
#else
#	error Unsupported configuration
#endif


extern "C" void SystemInit()
{
	__NOP();
	// Reset clock system before starting program
	System::Init();
	// Initialize Port A, B and C
	InitPA::Init();
	InitPB::Init();
	InitPC::Init();
	/*
	** BluePill: Initializes HSE, then PLL and the clock tree clock, including MCO output
	** Nucleo32 L432KC: Initializes LSE, then increases MSI with LSE trimming, PLL, clock tree with MCO output
	** On all cases Flash wait state is programmed before increasing frequency
	*/
	SysClk::Init();
}


int main()
{
	while (true) // Same as true: fools the linker to keep g_Value vector in ELF file
	{
		// A reasonable delay to see the LED blinking
		for(volatile int i = 0; i < 250000; ++i)
			__NOP();
		// Toggle the LED
		Led::Toggle();
	}
	return 0;
}

