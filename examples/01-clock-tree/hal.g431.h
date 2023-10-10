#pragma once

/*
** Nucleo-G431KB
** https://www.st.com/en/evaluation-tools/nucleo-g431kb.html
**
** IMPORTANT! You have to short SB9 and SB10 jumpers for this example to 
** work.
*/

// A data-type for the 24 MHz HSE clock
typedef Clocks::AnyHse<24000000UL> Hse;		// 24MHz HSE clock
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
typedef Clocks::AnyPll<
	Hse								// link to 24MHz MSI clock
	, 150000000UL					// Max is 150 MHz (without boost)
	, Clocks::AutoRange1			// Full voltage range calculator
> Pll;

// A data-type for the clock tree
typedef Clocks::AnySycClk <
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
	Gpio::Unchanged<13>,	// don't change SWD/JTAG
	Gpio::Unchanged<14>,	// don't change SWD/JTAG
	Gpio::Unchanged<15>		// don't change SWD/JTAG
> InitPA;

// Nucleo32 features the green LED on PB8
typedef Gpio::AnyOut<Gpio::Port::PB, 8> Led;
typedef Gpio::AnyPortSetup <
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
> InitPB;

// Port C is entirely unused
typedef Gpio::AnyPortSetup <
	Gpio::Port::PC
> InitPC;

