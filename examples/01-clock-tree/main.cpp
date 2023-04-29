#include <bmt.h>

using namespace Bmt;

#ifdef STM32F103xB

/*
STM32F103 BluePill
*/

// A data-type for the 8 MHz HSE clock
typedef Clocks::AnyHse<> Hse;	// BluePill has a 8MHz XTAL
// Configure the PLL for 72 MHz
typedef Clocks::AnyPll<Hse, 72000000UL> Pll;	// default 8MHz HSE clock

// A data-type for the clock tree
typedef Clocks::AnySycClk <
	Pll,							// uses PLL for the clock tree
	Clocks::AhbPrscl::k1,			// AHB 8 MHz
	Clocks::ApbPrscl::k2,			// APB1 4 Mhz
	Clocks::ApbPrscl::k1,			// APB2 8 MHz
	Clocks::AdcPrscl::k8,			// ADC 1 MHz
	Clocks::SysClkOpts::kDefault,	// defaults: stop HSI, frequency up and no USB,
	Clocks::Mco::kPllClkDiv2		// output PLL/2 to the MCO pin (36 MHz)
	> SysClk;

// A data-type to setup the Port A GPIO
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
	Gpio::MCO_PA8			// Alternate output for MCO signal
> InitPA;

// Port B is entirely unused
typedef Gpio::AnyPortSetup <
	Gpio::Port::PB
> InitPB;

//! LED is connected to PC13 on BluePill
typedef Gpio::AnyOut<Gpio::Port::PC, 13> Led;
typedef Gpio::AnyPortSetup <
	Gpio::Port::PC,
	Gpio::Unused<0>,		// unused pin (input + pull-down)
	Gpio::Unused<1>,		// unused pin (input + pull-down)
	Gpio::Unused<2>,		// unused pin (input + pull-down)
	Gpio::Unused<3>,		// unused pin (input + pull-down)
	Gpio::Unused<4>,		// unused pin (input + pull-down)
	Gpio::Unused<5>,		// unused pin (input + pull-down)
	Gpio::Unused<6>,		// unused pin (input + pull-down)
	Gpio::Unused<7>,		// unused pin (input + pull-down)
	Gpio::Unused<8>,		// unused pin (input + pull-down)
	Gpio::Unused<9>,		// unused pin (input + pull-down)
	Gpio::Unused<10>,		// unused pin (input + pull-down)
	Gpio::Unused<11>,		// unused pin (input + pull-down)
	Gpio::Unused<12>,		// unused pin (input + pull-down)
	Led,					// LED on PC13
	Gpio::Unchanged<14>,	// HSE here
	Gpio::Unchanged<15>	
> InitPC;

// Perform many static validations
#include "Validate.F103.h"

#elif defined(STM32L432xx)

// A data-type for the 8 MHz MSI clock
typedef Clocks::AnyMsi<Clocks::MsiFreq::k8_MHz> Msi;	// Nucleo-32/STM32L432KC internal 8MHz oscillator

// A data-type for the clock tree
typedef Clocks::AnySycClk <
	Msi,							// uses MSI for the clock tree
	Power::Mode::kRange1,
	Clocks::AhbPrscl::k1,			// AHB 8 MHz
	Clocks::ApbPrscl::k2,			// APB1 4 Mhz
	Clocks::ApbPrscl::k1,			// APB2 8 MHz
	false,							// Do not deactivate clock
	Clocks::Mco::kMsi				// output MSI to the MCO pin (36 MHz)
> SysClk;

// A data-type to setup the Port A GPIO
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
	Gpio::MCO_PA8			// Alternate output for MCO signal
> InitPA;

// Perform many static validations
#include "Validate.L432.h"

#else
#error Unsupported configuration
#endif

#if 1
typedef Gpio::AnyPin<
	Gpio::Port::PA,
	15,
	Gpio::Mode::kOutput,
	Gpio::Speed::kSlow,
	Gpio::PuPd::kFloating,
	Gpio::Level::kLow,
	Gpio::AfSWPMI1_SUSPEND_PA15
> Test;
#else
typedef Gpio::Unchanged<1> Test;
#endif

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

	(uint32_t)Test::kBitValue_,
	(uint32_t)Test::kBsrrValue_,
	(uint32_t)Test::kODR_,
	(uint32_t)Test::kODR_Mask_,

	(uint32_t)Test::kAFRL_Mask_,
	(uint32_t)Test::kAFRL_,
	(uint32_t)Test::kAFRH_Mask_,
	(uint32_t)Test::kAFRH_,
};

extern "C" void SystemInit()
{
	__NOP();
	// Reset clock system before starting program
#if 0
	System::Init();
#endif
	// Initialize Port A, B and C
	InitPA::Init();
#if 0
	InitPB::Init();
	InitPC::Init();
#endif
	// Initialize HSE and then the clock tree clock, including MCO output
	SysClk::Init();
}


int main()
{
	while ((void*)&g_Value[0] != (void*)0x1000) // Same as true: fools the linker to keep g_Value vector in ELF file
	{
		// A reasonable delay to see the LED blinking
		for(volatile int i = 0; i < 250000; ++i)
			__NOP();
#if 0
		// Toggle the LED
		Led::Toggle();
#endif
	}
	return 0;
}

