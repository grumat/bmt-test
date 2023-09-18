#pragma once

/*
** Nucleo-L432KC
** https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-mpu-eval-tools/stm32-mcu-mpu-eval-tools/stm32-nucleo-boards/nucleo-l432kc.html
*/


// A data-type for the 8 MHz MSI clock
typedef Clocks::AnyMsi<
	Clocks::MsiFreq::k8_MHz	// Change STM32L432KC internal oscillator from 4 MHz to 8MHz (good for USB)
	, true					// Nucleo32 has an 32768 LSE Xtal that we will use for accurate MSI frequency
> Msi;

// A data-type for the clock tree
typedef Clocks::AnySycClk <
	Msi						// uses MSI for the clock tree
> SysClk;

// The PWM output pin where ECG is generated
typedef Gpio::TIM1_CH1_PA8 SignalOut;

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
	SignalOut,				// PWM output with ECG signal
	Gpio::Unused<9>,		// unused pin (input + pull-down)
	Gpio::Unused<10>,		// unused pin (input + pull-down)
	Gpio::Unused<11>,		// unused pin (input + pull-down)
	Gpio::Unused<12>,		// unused pin (input + pull-down)
	Gpio::Unchanged<13>,	// unchanged pin used for debugger
	Gpio::Unchanged<14>,	// unchanged pin used for debugger
	Gpio::Unchanged<15>		// unchanged pin used for debugger
> InitPA;

// Nucleo32 features the green LED on PB3
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


// The timer used for PWM generation
constexpr Timer::Unit kPwmTimer = kTim1;
// Timer used to update samples
constexpr Timer::Unit kUpdateTimer = kTim2;
// Output channel for PWM output
constexpr Timer::Channel kPwmOutChannel = Channel::k1;
// The ID for the DMA channel used for sample transfers
typedef Dma::IdTim2Up IdDmaUpdate;

// Turns the board LED on
inline void LedOn() { Led::SetHigh(); }
// Turns the board LED off
inline void LedOff() { Led::SetLow(); }
// Checks if the board LED is on
inline bool IsLedOn() { return Led::IsHigh(); }
