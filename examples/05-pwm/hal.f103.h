#pragma once

/*
STM32F103 BluePill
*/

// One can experiment to change the SysClk frequency.
// New timing is adjusted automatically and example will
// run exactly as before.
#define OPT_USE_PLL		0

// A data-type for the 8 MHz HSE clock
typedef Clocks::AnyHse<> Hse;	// BluePill has a 8MHz XTAL
#if OPT_USE_PLL
// Configure the PLL for 72 MHz
typedef Clocks::AnyPll<Hse, 16000000UL> Pll;	// default 8MHz HSE clock
#endif

// A data-type for the clock tree
typedef Clocks::AnySycClk <
#if OPT_USE_PLL
	Pll							// uses PLL for the clock tree
#else
	Hse							// uses HSE for the clock tree
#endif
> SysClk;

// A data-type to setup the Port A GPIO
typedef Gpio::AnyPortSetup<
	Gpio::Port::PA,
	Gpio::Unused<0>,					// unused pin (input + pull-down)
	Gpio::Unused<1>,					// unused pin (input + pull-down)
	Gpio::Unused<2>,					// unused pin (input + pull-down)
	Gpio::Unused<3>,					// unused pin (input + pull-down)
	Gpio::Unused<4>,					// unused pin (input + pull-down)
	Gpio::Unused<5>,					// unused pin (input + pull-down)
	Gpio::Unused<6>,					// unused pin (input + pull-down)
	Gpio::Unused<7>,					// unused pin (input + pull-down)
	Gpio::TIM1_CH1_PA8_OUT,				// RGB LED (R pin)
	Gpio::TIM1_CH2_PA9_OUT,				// RGB LED (G pin)
	Gpio::TIM1_CH3_PA10_OUT,			// RGB LED (B pin)
	Gpio::Unused<11>,					// unused pin (input + pull-down)
	Gpio::Unused<12>,					// unused pin (input + pull-down)
	Gpio::Unchanged<13>,				// unchanged pin used for debugger
	Gpio::Unchanged<14>,				// unchanged pin used for debugger
	Gpio::Unchanged<15>					// unchanged pin used for debugger
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
	Gpio::Unchanged<14>,
	Gpio::Unchanged<15>
> InitPC;


// The timer used to generate PWM (requires 3 channels with I/O pins)
static constexpr Timer::Unit kPwmTim = Timer::Unit::kTim1;
// PWM Channel used for the Red LED
static constexpr Timer::Channel kRedCh = Timer::Channel::k1;
// PWM Channel used for the Green LED
static constexpr Timer::Channel kGreenCh = Timer::Channel::k2;
// PWM Channel used for the Blue LED
static constexpr Timer::Channel kBlueCh = Timer::Channel::k3;

