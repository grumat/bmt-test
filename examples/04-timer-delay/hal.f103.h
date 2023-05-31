#pragma once

/*
STM32F103 BluePill
*/

// A data-type for the 8 MHz HSE clock
typedef Clocks::AnyHse<> Hse;	// BluePill has a 8MHz XTAL

// A data-type for the clock tree
typedef Clocks::AnySycClk <
	Hse							// uses HSE for the clock tree
> SysClk;

// Types for experiment 4
typedef Gpio::AnyOut<Gpio::Port::PA, 10> LedB;
typedef Gpio::AnyOut<Gpio::Port::PA, 9> LedG;
typedef Gpio::AnyOut<Gpio::Port::PA, 8> LedR;

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
	LedR,					// R signal of RGB LED for experiment 4
	LedG,					// G signal of RGB LED for experiment 4
	LedB,					// B signal of RGB LED for experiment 4
	Gpio::Unused<11>,		// unused pin (input + pull-down)
	Gpio::Unused<12>,		// unused pin (input + pull-down)
	Gpio::Unchanged<13>,	// unchanged pin used for debugger
	Gpio::Unchanged<14>,	// unchanged pin used for debugger
	Gpio::Unchanged<15>		// unchanged pin used for debugger
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

