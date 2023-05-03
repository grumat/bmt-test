#include <bmt.h>

using namespace Bmt;

#ifdef STM32F103xB

#include "hal.f103.h"
// Perform many static validations
#include "Validate.F103.h"

#elif defined(STM32L432xx)

#include "hal.l432.h"
// Perform many static validations
#include "Validate.L432.h"

#elif defined(STM32G431xx)

#include "hal.g431.h"

#else
#error Unsupported configuration
#endif

#if 0
typedef Gpio::AnyPortSetup<
	Gpio::Port::PA,
	Gpio::Unused<0>,		// unused pin (input + pull-down)
	Gpio::Unused<1>,		// unused pin (input + pull-down)
	Gpio::Unused<2>,		// unused pin (input + pull-down)
	Gpio::Unused<3>,		// unused pin (input + pull-down)
	Gpio::Unused<4>,		// unused pin (input + pull-down)
	Gpio::Unused<5>,		// unused pin (input + pull-down)
	Gpio::Unused<6>,		// unused pin (input + pull-down)
	Gpio::Unused<7>,		// unused pin (input + pull-down)
	Gpio::MCO_PA8,			// Alternate output for MCO signal
	Gpio::Unused<9>,		// unused pin (input + pull-down)
	Gpio::Unused<10>,		// unused pin (input + pull-down)
	Gpio::Unused<11>,		// unused pin (input + pull-down)
	Gpio::Unused<12>,		// unused pin (input + pull-down)
	Gpio::SWDIO_PA13,		// SWD DIO pin (for debug)
	Gpio::SWCLK_PA14,		// SWD CLK pin (for debug)
	Gpio::Unused<15>		// unused pin (input + pull-down)
> Test;
#elif 0
typedef Gpio::Unchanged<1> Test;
#endif

#if 0
const uint32_t g_Value[] = 
{
	(uint32_t)Test::kMODER_Mask_,
	(uint32_t)Test::kMODER_,
	(uint32_t)Test::kOTYPER_Mask_,
	(uint32_t)Test::kOTYPER_,
	
	(uint32_t)Test::kOSPEEDR_Mask_,
	(uint32_t)Test::kOSPEEDR_,
	(uint32_t)Test::kPUPDR_Mask_,
	(uint32_t)Test::kPUPDR_,

	(uint32_t)Test::kODR_,
	(uint32_t)Test::kODR_Mask_,
	(uint32_t)Test::kAFRL_Mask_,
	(uint32_t)Test::kAFRL_,
	(uint32_t)Test::kAFRH_Mask_,
	(uint32_t)Test::kAFRH_,
};
#elif 0
const uint32_t g_Value[] =
{
	(uint32_t)Test::kCRL_,
	(uint32_t)Test::kCRL_Mask_,
	(uint32_t)Test::kCRH_,
	(uint32_t)Test::kCRH_Mask_,

	(uint32_t)Test::kODR_,
	(uint32_t)Test::kODR_Mask_,
	(uint32_t)Test::kBitValue_,
	(uint32_t)Test::kAfConf_,

	(uint32_t)Test::kAfMask_,
};
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
	//while ((void*)&g_Value[0] != (void*)0x1000) // Same as true: fools the linker to keep g_Value vector in ELF file
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

