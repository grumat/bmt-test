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
	Gpio::MCO_PA8, 			// Alternate output for MCO signal
	Gpio::Unused<9>,		// unused pin (input + pull-down)
	Gpio::Unused<10>,		// unused pin (input + pull-down)
	Gpio::Unused<11>,		// unused pin (input + pull-down)
	Gpio::Unused<12>,		// unused pin (input + pull-down)
	Gpio::Unused<13>,		// unused pin (input + pull-down)
	Gpio::Unused<14>,		// unused pin (input + pull-down)
	Gpio::Unused<15>		// unused pin (input + pull-down)
	> InitPA;
#else
#error Unsupported configuration
#endif

extern "C" void SystemInit()
{
	__NOP();
	// Reset clock system before starting program
	System::Init();
	// Initialize Port A
	InitPA::Init();
	// Initialize HSE and then the clock tree clock, including MCO output
	SysClk::Init();
}


int main()
{
	while(true)
		__NOP();
    return 0;
}

