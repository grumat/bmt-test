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


// The data-type representing the system tick timer
typedef Timer::SysTickCounter<SysClk> Tick;

// 40 KHz PWM base frequency using Timer 1
// This timer provides all 3 required outputs we need for this example
typedef Timer::InternalClock_Hz<Timer::Unit::kTim1, SysClk, 40000> PwmFreq;
// This divides base frequency by 200; also, the range we can control LED brightness
typedef Timer::Any<PwmFreq, Timer::Mode::kUpCounter, 202> Pwm;

// CH1 output drives red LED
typedef Timer::AnyOutputChannel<Pwm
	, Timer::Channel::k1
	, Timer::OutMode::kPWM2
	, Timer::Output::kInverted
	, Timer::Output::kDisabled
	, true
> LEDR;

// CH2 output drives green LED
typedef Timer::AnyOutputChannel<Pwm
	, Timer::Channel::k2
	, Timer::OutMode::kPWM2
	, Timer::Output::kInverted
	, Timer::Output::kDisabled
	, true
> LEDG;

// CH3 output drives blue LED
typedef Timer::AnyOutputChannel<Pwm
	, Timer::Channel::k3
	, Timer::OutMode::kPWM2
	, Timer::Output::kInverted
	, Timer::Output::kDisabled
	, true
> LEDB;

