#pragma once

/*
** Nucleo-G431KB
** https://www.st.com/en/evaluation-tools/nucleo-g431kb.html
**
** IMPORTANT! You have to short SB9 and SB10 jumpers for this example to 
** work.
*/

// A data-type for the 24 MHz HSE clock
using Hse = Clocks::AnyHse<24000000UL>;		// 24MHz HSE clock
// Configure the PLL for 150 MHz
/*
** This configuration uses a calculator to obtain 150MHz from 24MHz. Obtained 
** PLL values are:
**		- PLLSCR:	0b03	(HSE)
**		- PLLM:		0b001	(/2)
**		- PLLN:		0x19	(*25)
**		- PLLREN:	1		(PLLCLK output for the Cortex M4)
**		- PLLR:		0b00	(/2)
** Final frequency is 24MHz (/2) (*25) (/2) = 150MHz
*/
using Pll = Clocks::AnyPll<
	Hse								// link to 24MHz MSI clock
	, 150000000UL					// Max is 150 MHz (without boost)
	, Clocks::AutoRange1			// Full voltage range calculator
>;

// A data-type for the clock tree
using SysClk = Clocks::AnySycClk <
	Pll,							// uses PLL for the clock tree
	//Hse,							// uses HSE for the clock tree
	Power::Mode::kRange1,			// Full Voltage for Max performance
	Clocks::AhbPrscl::k1,			// AHB 24 MHz
	Clocks::ApbPrscl::k2,			// APB1 12 Mhz
	Clocks::ApbPrscl::k1,			// APB2 24 MHz
	Clocks::SysClkOpts::kDefault,	// Do not deactivate clock
	Clocks::Mco::kPllClk,			// output PLL to the MCO pin (150MHz/16 = 9.375MHz)
	//Clocks::Mco::kHse,			// output HSE to the MCO pin (24MHz/16 = 1.5MHz)
	Clocks::McoPrscl::k16			// CLK/16 for the MCO output is enough
>;

// A data-type to setup the Port A GPIO
using InitPA = Gpio::AnyPortSetup<
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
>;

// Nucleo32 features the green LED on PB8
using Led = Gpio::AnyOut<Gpio::Port::PB, 8>;
using InitPB = Gpio::AnyPortSetup <
	Gpio::Port::PB,
	Gpio::Unused<0>,		// unused pin (input + pull-down)
	Gpio::Unused<1>,		// unused pin (input + pull-down)
	Gpio::Unused<2>,		// unused pin (input + pull-down)
	Gpio::Unused<3>,		// unused pin (input + pull-down)
	Gpio::Unused<4>,		// unused pin (input + pull-down)
	Gpio::Unused<5>,		// unused pin (input + pull-down)
	Gpio::Unused<6>,		// unused pin (input + pull-down)
	Gpio::Unused<7>,		// unused pin (input + pull-down)
	Led						// LED on PB8
>;

// Port C is entirely unused
using InitPC = Gpio::AnyPortSetup <
	Gpio::Port::PC
>;

// All GPIO ports collected for one-shot initialization at startup
using AllGpioStartup = Gpio::PortMerge<InitPA, InitPB, InitPC>;

// All peripheral clocks collected for one-shot initialization at boot
using PeripheralEnabler = Clocks::Enabler<
	Gpio::PortClock<Gpio::Port::PA>,
	Gpio::PortClock<Gpio::Port::PB>,
	Gpio::PortClock<Gpio::Port::PC>
>;
