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
	Gpio::AnyOut<Gpio::Port::PA, 0>,	// LCD1602 EN pin
	Gpio::AnyOut<Gpio::Port::PA, 1>,	// LCD1602 RS pin
	Gpio::AnyOut<Gpio::Port::PA, 2>,	// LCD1602 RW pin
	Gpio::Unused<3>,					// unused pin (input + pull-down)
	Gpio::AnyOut<Gpio::Port::PA, 4>,	// LCD1602 D4 pin
	Gpio::AnyOut<Gpio::Port::PA, 5>,	// LCD1602 D5 pin
	Gpio::AnyOut<Gpio::Port::PA, 6>,	// LCD1602 D6 pin
	Gpio::AnyOut<Gpio::Port::PA, 7>,	// LCD1602 D7 pin
	Gpio::Unused<8>,					// unused pin (input + pull-down)
	Gpio::Unused<9>,					// unused pin (input + pull-down)
	Gpio::Unused<10>,					// unused pin (input + pull-down)
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
	Gpio::PortClock<Gpio::Port::PC>
>;

// The data-type representing the system tick timer
using Delay = Timer::AnyDelay<SysClk>;
using Tick = Timer::SysTickCounter<SysClk>;
using Lcd = AnyLcd1602<
	Delay, 
	Timer::MicroStopWatch<Tick>, 
	Gpio::Port::PA,
	Options::kDefault,
	1,		// RS
	2,		// RW
	0,		// EN: Use A0, since A3 requires a bridge to function
	4, 5, 6, 7
>;
