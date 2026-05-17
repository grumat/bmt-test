#pragma once

/*
STM32F103 BluePill
*/

// A data-type for the 8 MHz HSE clock
using Hse = Clocks::AnyHse<>;	// BluePill has a 8MHz XTAL

using PeripheralEnabler = Clocks::Enabler<
	Gpio::PortClock<Gpio::Port::PA>,
	Gpio::Afio,			// TIM1_CH1 alternate function on PA8
	Gpio::PortClock<Gpio::Port::PB>,
	Gpio::PortClock<Gpio::Port::PC>,
	Timer::TimerDescriptor<Timer::kTim1>,
	Timer::TimerDescriptor<Timer::kTim2>,
	Dma::Controller<Dma::Itf::k1>
>;

// A data-type for the clock tree
using SysClk = Clocks::AnySycClk <
	Hse							// uses HSE for the clock tree
>;

// The PWM output pin where ECG is generated
using SignalOut = Gpio::TIM1_CH1_PA8_OUT;

// A data-type to setup the Port A GPIO
using InitPA = Gpio::AnyPortSetup<
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
>;

// Port B is entirely unused
using InitPB = Gpio::AnyPortSetup <
	Gpio::Port::PB
>;

//! LED is connected to PC13 on BluePill
using Led = Gpio::AnyOut<Gpio::Port::PC, 13>;
// A data-type to setup the Port C GPIO
using InitPC = Gpio::AnyPortSetup <
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
>;

// All GPIO ports collected for one-shot initialization at startup
using AllGpioStartup = Gpio::PortMerge<InitPA, InitPB, InitPC>;

// The timer used for PWM generation
constexpr Timer::Unit kPwmTimer = kTim1;
// Timer used to update samples
constexpr Timer::Unit kUpdateTimer = kTim2;
// Output channel for PWM output
constexpr Timer::Channel kPwmOutChannel = Channel::k1;
// The ID for the DMA channel used for sample transfers
using IdDmaUpdate = Dma::IdTim2Up;
// Turns the board LED on
inline void LedOn() { Led::SetLow(); }
// Turns the board LED off
inline void LedOff() { Led::SetHigh(); }
// Checks if the board LED is on
inline bool IsLedOn() { return Led::IsLow(); }
