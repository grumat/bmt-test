#pragma once

/*
** Nucleo-G431KB
** https://www.st.com/en/evaluation-tools/nucleo-g431kb.html
**
** IMPORTANT! You have to short SB9 and SB10 jumpers for this example to 
** work.
*/

// A data-type for the 24 MHz HSE clock
using Hse = Clocks::AnyHse<24000000UL>;		// 24MHz HSE clock

// A data-type for the clock tree
using SysClk = Clocks::AnySycClk <
	Hse									// Uses HSE for the clock tree
>;

// A data-type to setup the Port A GPIO
using InitPA = Gpio::AnyPortSetup<
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
>;

// Nucleo32 features the green LED on PB8
using Led = Gpio::AnyOut<Gpio::Port::PB, 8>;
using InitPB = Gpio::AnyPortSetup <
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
>;

// Port C is entirely unused
using InitPC = Gpio::AnyPortSetup <
	Gpio::Port::PC
>;

// All GPIO ports collected for one-shot initialization at startup
using AllGpioStartup = Gpio::PortMerge<InitPA, InitPB, InitPC>;

// All peripheral clocks collected for one-shot initialization at boot
using PeripheralEnabler = Clocks::Enabler<
	Gpio::PortClock<Gpio::Port::PA>,
	Gpio::PortClock<Gpio::Port::PB>,
	Gpio::PortClock<Gpio::Port::PC>,
	Timer::TimerDescriptor<Timer::Unit::kTim1>
>;

// The timer used to generate PWM (requires 3 channels with I/O pins)
static constexpr Timer::Unit kPwmTim = Timer::Unit::kTim1;
// PWM Channel used for the Red LED
static constexpr Timer::Channel kRedCh = Timer::Channel::k1;
// PWM Channel used for the Green LED
static constexpr Timer::Channel kGreenCh = Timer::Channel::k2;
// PWM Channel used for the Blue LED
static constexpr Timer::Channel kBlueCh = Timer::Channel::k3;
