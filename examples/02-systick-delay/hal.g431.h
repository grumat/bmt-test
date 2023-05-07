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

// A data-type for the clock tree
typedef Clocks::AnySycClk <
	Hse						// Uses HSE for the clock tree
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
	Gpio::Unused<8>,		// unused pin (input + pull-down)
	Gpio::Unused<9>,		// unused pin (input + pull-down)
	Gpio::Unused<10>,		// unused pin (input + pull-down)
	Gpio::Unused<11>,		// unused pin (input + pull-down)
	Gpio::Unused<12>,		// unused pin (input + pull-down)
	Gpio::Unchanged<13>,	// unchanged pin used for debugger
	Gpio::Unchanged<14>,	// unchanged pin used for debugger
	Gpio::Unchanged<15>		// unchanged pin used for debugger
> InitPA;

// Nucleo32 features the green LED on PB8
typedef Gpio::AnyOut<Gpio::Port::PB, 8> Led;
typedef Gpio::AnyPortSetup <
	Gpio::Port::PB,
	Gpio::Unused<0>,		// unused pin (input + pull-down)
	Gpio::Unused<1>,		// unused pin (input + pull-down)
	Gpio::Unused<2>,		// unused pin (input + pull-down)
	Gpio::Unchanged<3>,		// unchanged pin used for debugger
	Gpio::Unchanged<4>,		// unchanged pin used for debugger
	Gpio::Unused<5>,		// unused pin (input + pull-down)
	Gpio::Unused<6>,		// unused pin (input + pull-down)
	Gpio::Unused<7>,		// unused pin (input + pull-down)
	Led						// LED on PB8
> InitPB;

// Port C is entirely unused
typedef Gpio::AnyPortSetup <
	Gpio::Port::PC
> InitPC;

