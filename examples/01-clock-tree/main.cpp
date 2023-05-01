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

/*
** In this example we have a very good setting for an USB application.
** The MSI is clocked to 48 MHz and trimmed with the 32768 Xtal, offering
** a good accuracy for the USB device. The PLL is also used to obtain 
** 80 MHz for the CPU using the same MSI 48 MHz as source.
*/

// A data-type for the 48 MHz MSI clock
typedef Clocks::AnyMsi<
	Clocks::MsiFreq::k48_MHz		// Change STM32L432KC internal oscillator from 4 MHz to 48MHz (good for USB)
	, true							// Nucleo32 has an 32768 LSE Xtal that we will use for accurate MSI frequency
> Msi;
// Configure the PLL for 80 MHz
/*
** This configuration uses a calculator to obtain 80MHz from 48MHz. Obtainend PLL values are:
**		- PLLSCR:	0b01	(MSI)
**		- PLLM:		0b010	(/3)
**		- PLLN:		0x0a	(*10)
**		- PLLREN:	1		(PLLCLK output for the Cortex M4)
**		- PLLR:		0b00	(/2)
** Final frequency is 48MHz (/3) (*10) (/2) = 80MHz
*/
typedef Clocks::AnyPll<
	Msi								// link to 48MHz MSI clock
	, 80000000UL					// Max is 80 MHz
	, Clocks::AutoRange1			// Full voltage range calculator
> Pll;

// A data-type for the clock tree
typedef Clocks::AnySycClk <
	Pll,							// uses PLL for the clock tree
	//Msi,							// uses MSI for the clock tree
	Power::Mode::kRange1,			// Full Voltage for Max performance
	Clocks::AhbPrscl::k1,			// AHB 8 MHz
	Clocks::ApbPrscl::k2,			// APB1 4 Mhz
	Clocks::ApbPrscl::k1,			// APB2 8 MHz
	Clocks::SysClkOpts::kDefault,	// Do not deactivate clock
	Clocks::Mco::kMsi,				// output MSI to the MCO pin (48MHz/16 = 3MHz)
	//Clocks::Mco::kPllClk,			// output PLL to the MCO pin (80MHz/16 = 5MHz)
	Clocks::McoPrscl::k16			// CLK/16 for the MCO output is enough
> SysClk;

/*
** Experiment note: Using MSI with 32768 LSE lock works very good without the PLL. 
** It is stable at 48.005 MHz like specified on the data-sheet. By attaching the
** PLL to this clock source a slight frequency reduction is observed: 47,776MHz.
** Seems too much deviation for USB application.
** Maybe the best option is to use HSI48 with SOF synchronisation.
*/

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
	Gpio::Unchanged<13>,	// don't change SWD/JTAG
	Gpio::Unchanged<14>,	// don't change SWD/JTAG
	Gpio::Unchanged<15>		// don't change SWD/JTAG
> InitPA;

// Nucleo32 features the gree LED on PB3
typedef Gpio::AnyOut<Gpio::Port::PB, 3> Led;
typedef Gpio::AnyPortSetup <
	Gpio::Port::PB,
	Gpio::Unused<0>,		// unused pin (input + pull-down)
	Gpio::Unused<1>,		// unused pin (input + pull-down)
	Gpio::Unused<2>,		// unused pin (input + pull-down)
	Led						// LED on PB3
> InitPB;

// Port C is entirely unused
typedef Gpio::AnyPortSetup <
	Gpio::Port::PC
> InitPC;

// Perform many static validations
#include "Validate.L432.h"

#else
#error Unsupported configuration
#endif

#if 1
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
	Gpio::Unchanged<13>,	// don't change SWD/JTAG
	Gpio::Unchanged<14>,	// don't change SWD/JTAG
	Gpio::Unchanged<15>		// don't change SWD/JTAG
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

	(uint32_t)Test::kODR_,
	(uint32_t)Test::kODR_Mask_,
	(uint32_t)Test::kAFRL_Mask_,
	(uint32_t)Test::kAFRL_,
	(uint32_t)Test::kAFRH_Mask_,
	(uint32_t)Test::kAFRH_,
};

extern "C" void SystemInit()
{
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

