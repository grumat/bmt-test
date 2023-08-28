#pragma once

/*
** Nucleo-L432KC
** https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-mpu-eval-tools/stm32-mcu-mpu-eval-tools/stm32-nucleo-boards/nucleo-l432kc.html
*/


// A data-type for the 8 MHz MSI clock
typedef Clocks::AnyMsi<
	Clocks::MsiFreq::k8_MHz			// Change STM32L432KC internal oscillator from 4 MHz to 8MHz
	, true							// Nucleo32 has an 32768 LSE Xtal that we will use for accurate MSI frequency
> Msi;

// A data-type for the clock tree
typedef Clocks::AnySycClk <
	Msi								// uses MSI for the clock tree
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
	Gpio::TIM1_CH1_PA8,					// RGB LED (R pin)
	Gpio::TIM1_CH2_PA9,					// RGB LED (G pin)
	Gpio::TIM1_CH3_PA10,				// RGB LED (B pin)
	Gpio::Unused<11>,					// unused pin (input + pull-down)
	Gpio::Unused<12>,					// unused pin (input + pull-down)
	Gpio::Unchanged<13>,				// unchanged pin used for debugger
	Gpio::Unchanged<14>,				// unchanged pin used for debugger
	Gpio::Unchanged<15>					// unchanged pin used for debugger
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
