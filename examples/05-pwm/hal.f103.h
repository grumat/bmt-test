#pragma once

/*
STM32F103 BluePill
*/

// A data-type for the 8 MHz HSE clock
typedef Clocks::AnyHse<> Hse;	// BluePill has a 8MHz XTAL
#if 0 // one can experiment to change the SysClk frequency. New timing is adjusted automatically
// Configure the PLL for 72 MHz
typedef Clocks::AnyPll<Hse, 16000000UL> Pll;	// default 8MHz HSE clock
#endif

// A data-type for the clock tree
typedef Clocks::AnySycClk <
	Hse							// uses HSE for the clock tree
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


// The data-type representing the system tick timer
typedef Timer::SysTickCounter<SysClk> Tick;

typedef InternalClock_Hz<Tim::k1, SysClk, 40000> PwmFreq;
typedef TimerTemplate<PwmFreq, TimerMode::kUpCounter, 202> Pwm;

typedef TimerOutputChannel<Pwm
	, TimChannel::k1
	, TimOutMode::kTimOutPwm2
	, TimOutDrive::kTimOutActiveLow
	, TimOutDrive::kTimOutInactive
	, true
> LEDR;

typedef TimerOutputChannel<Pwm
	, TimChannel::k2
	, TimOutMode::kTimOutPwm2
	, TimOutDrive::kTimOutActiveLow
	, TimOutDrive::kTimOutInactive
	, true
> LEDG;

typedef TimerOutputChannel<Pwm
	, TimChannel::k3
	, TimOutMode::kTimOutPwm2
	, TimOutDrive::kTimOutActiveLow
	, TimOutDrive::kTimOutInactive
	, true
> LEDB;

