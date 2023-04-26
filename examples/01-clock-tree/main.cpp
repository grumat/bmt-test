#include <bmt.h>

using namespace Bmt;

#ifdef STM32F103xB

/*
STM32F103 BluePill
*/

// A data-type for the 8 MHz HSE clock
typedef Clocks::AnyHse<> Hse;	// default 8MHz HSE clock

// A data-type for the clock tree
typedef Clocks::AnySycClk <
	Hse,						// uses HSE for the clock tree
	Clocks::AhbPrscl::k1,		// AHB 8 MHz
	Clocks::ApbPrscl::k2,		// APB1 4 Mhz
	Clocks::ApbPrscl::k1,		// APB2 8 MHz
	Clocks::AdcPrscl::k8,		// ADC 1 MHz
	true,						// stop HSI
	Clocks::Mco::kHse			// output HSE to the MCO pin
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
	Gpio::MCO_PA8,			// Alternate output for MCO signal
	Gpio::Unused<9>,		// unused pin (input + pull-down)
	Gpio::Unused<10>,		// unused pin (input + pull-down)
	Gpio::Unused<11>,		// unused pin (input + pull-down)
	Gpio::Unused<12>,		// unused pin (input + pull-down)
	Gpio::SWDIO_PA13,		// SWD DIO pin (for debug)
	Gpio::SWCLK_PA14,		// SWD CLK pin (for debug)
	Gpio::Unused<15>		// unused pin (input + pull-down)
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

#else
#error Unsupported configuration
#endif

typedef Gpio::Unchanged<1> TestPin;

const uint32_t g_Value[] = 
{
	(uint32_t)TestPin::kCRL_,
	(uint32_t)TestPin::kCRL_Mask_,
	(uint32_t)TestPin::kODR_,
	(uint32_t)TestPin::kAfConf_,
	(uint32_t)TestPin::kAfMask_,
	(uint32_t)TestPin::kBitValue_,
};

extern "C" void SystemInit()
{
	__NOP();
	// Reset clock system before starting program
	System::Init();
	// Initialize Port A, B and C
	InitPA::Init();
	InitPB::Init();
	InitPC::Init();
	// Initialize HSE and then the clock tree clock, including MCO output
	SysClk::Init();
}


int main()
{
	while ((void*)&g_Value[0] != (void*)0x1000) // Same as true: fools the compiler to keep g_Value vector in memory
	{
		for(volatile int i = 0; i < 250000; ++i)
			__NOP();
		Led::Toggle();
		__NOP();
	}
	return 0;
}

