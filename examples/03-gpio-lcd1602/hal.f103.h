#pragma once

/*
STM32F103 BluePill
*/

// A data-type for the 8 MHz HSE clock
using Hse = Clocks::AnyHse<>;	// BluePill has a 8MHz XTAL

using PeripheralEnabler = Clocks::Enabler<
	Gpio::PortClock<Gpio::Port::PA>,
	Gpio::PortClock<Gpio::Port::PB>,
	Gpio::PortClock<Gpio::Port::PC>
>;
#if 0 // one can experiment to change the SysClk frequency. New timing is adjusted automatically
// Configure the PLL for 72 MHz
using Pll = Clocks::AnyPll<Hse, 16000000UL>;	// default 8MHz HSE clock
#endif

// A data-type for the clock tree
using SysClk = Clocks::AnySycClk <
	Hse							// uses HSE for the clock tree
>;

// A data-type to setup the Port A GPIO
using InitPA = Gpio::AnyPortSetup<
	Gpio::Port::PA,
	Gpio::Unused<0>,					// unused pin (input + pull-down)
	Gpio::AnyOut<Gpio::Port::PA, 1>,	// LCD1602 RS pin
	Gpio::AnyOut<Gpio::Port::PA, 2>,	// LCD1602 RW pin
	Gpio::AnyOut<Gpio::Port::PA, 3>,	// LCD1602 EN pin
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

// Port B is entirely unused
using InitPB = Gpio::AnyPortSetup <
	Gpio::Port::PB
>;

//! LED is connected to PC13 on BluePill
using Led = Gpio::AnyOut<Gpio::Port::PC, 13>;
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
	Gpio::Unchanged<14>,
	Gpio::Unchanged<15>
>;

// All GPIO ports collected for one-shot initialization at startup
using AllGpioStartup = Gpio::PortMerge<InitPA, InitPB, InitPC>;

// The data-type representing the system tick timer
using Delay = Timer::AnyDelay<SysClk>;
using Tick = Timer::SysTickCounter<SysClk>;
using Lcd = AnyLcd1602<Delay, Timer::MicroStopWatch<Tick>, Gpio::Port::PA>;
