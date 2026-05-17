#pragma once

/*
** Nucleo-L432KC
** https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-mpu-eval-tools/stm32-mcu-mpu-eval-tools/stm32-nucleo-boards/nucleo-l432kc.html
*/

/*
** In this example we have a very good setting for an USB application.
** The MSI is clocked to 48 MHz and trimmed with the 32768 Xtal, offering
** a good accuracy for the USB device. The PLL is also used to obtain
** 80 MHz for the CPU using the same MSI 48 MHz as source.
*/

// A data-type for the 8 MHz MSI clock
using Msi = Clocks::AnyMsi<
	Clocks::MsiFreq::k8_MHz			// Change STM32L432KC internal oscillator from 4 MHz to 8MHz (good for USB)
	, true							// Nucleo32 has an 32768 LSE Xtal that we will use for accurate MSI frequency
>;

// A data-type for the clock tree
using SysClk = Clocks::AnySycClk <
	Msi							// uses MSI for the clock tree
>;

// Types for experiment 4
using LedB = Gpio::AnyOut<Gpio::Port::PA, 5>;
using LedG = Gpio::AnyOut<Gpio::Port::PA, 6>;
using LedR = Gpio::AnyOut<Gpio::Port::PA, 7>;

// A data-type to setup the Port A GPIO
using InitPA = Gpio::AnyPortSetup<
	Gpio::Port::PA,
	Gpio::Unused<0>,		// unused pin (input + pull-down)
	Gpio::Unused<1>,		// unused pin (input + pull-down)
	Gpio::Unused<2>,		// unused pin (input + pull-down)
	Gpio::Unused<3>,		// unused pin (input + pull-down)
	Gpio::Unused<4>,		// unused pin (input + pull-down)
	LedB,					// B signal of RGB LED for experiment 4
	LedG,					// G signal of RGB LED for experiment 4
	LedR,					// R signal of RGB LED for experiment 4
	Gpio::Unused<8>,		// unused pin (input + pull-down)
	Gpio::Unused<9>,		// unused pin (input + pull-down)
	Gpio::Unused<10>,		// unused pin (input + pull-down)
	Gpio::Unused<11>,		// unused pin (input + pull-down)
	Gpio::Unused<12>,		// unused pin (input + pull-down)
	Gpio::Unchanged<13>,	// unchanged pin used for debugger
	Gpio::Unchanged<14>,	// unchanged pin used for debugger
	Gpio::Unchanged<15>		// unchanged pin used for debugger
>;

// Nucleo32 features the gree LED on PB3
using Led = Gpio::AnyOut<Gpio::Port::PB, 3>;
using InitPB = Gpio::AnyPortSetup <
	Gpio::Port::PB,
	Gpio::Unused<0>,		// unused pin (input + pull-down)
	Gpio::Unused<1>,		// unused pin (input + pull-down)
	Gpio::Unused<2>,		// unused pin (input + pull-down)
	Led						// LED on PB3
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
