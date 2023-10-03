#pragma once

/*
** Nucleo-L432KC
** https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-mpu-eval-tools/stm32-mcu-mpu-eval-tools/stm32-nucleo-boards/nucleo-l432kc.html
*/


// A data-type for the 8 MHz MSI clock
typedef Clocks::AnyMsi<
	Clocks::MsiFreq::k8_MHz			// Change STM32L432KC internal oscillator from 4 MHz to 8MHz
	, true							// Nucleo32 has an 32768 LSE Xtal that trims MSI frequency accuratelly
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


// The timer used to generate PWM (requires 3 channels with I/O pins)
static constexpr Timer::Unit kPwmTim = Timer::Unit::kTim1;
// PWM Channel used for the Red LED
static constexpr Timer::Channel kRedCh = Timer::Channel::k1;
// PWM Channel used for the Green LED
static constexpr Timer::Channel kGreenCh = Timer::Channel::k2;
// PWM Channel used for the Blue LED
static constexpr Timer::Channel kBlueCh = Timer::Channel::k3;

