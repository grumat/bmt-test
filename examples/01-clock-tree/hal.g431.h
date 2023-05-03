#pragma once

/*
** Nucleo-G431KB
** https://www.st.com/en/evaluation-tools/nucleo-g431kb.html
*/

// A data-type for the 16 MHz HSI clock
typedef Clocks::AnyHsi16<> Hsi;		// 16MHz internal RC clock

// A data-type for the clock tree
typedef Clocks::AnySycClk <
	//Pll,							// uses PLL for the clock tree
	Hsi,							// uses HSI for the clock tree
	Power::Mode::kRange1,			// Full Voltage for Max performance
	Clocks::AhbPrscl::k1,			// AHB 8 MHz
	Clocks::ApbPrscl::k2,			// APB1 4 Mhz
	Clocks::ApbPrscl::k1,			// APB2 8 MHz
	Clocks::SysClkOpts::kDefault,	// Do not deactivate clock
	Clocks::Mco::kHsi16,			// output HSI16 to the MCO pin (48MHz/16 = 3MHz)
	//Clocks::Mco::kPllClk,			// output PLL to the MCO pin (80MHz/16 = 5MHz)
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

