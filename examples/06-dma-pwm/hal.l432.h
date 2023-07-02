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
typedef Clocks::AnyMsi<
	Clocks::MsiFreq::k8_MHz			// Change STM32L432KC internal oscillator from 4 MHz to 8MHz (good for USB)
	, true							// Nucleo32 has an 32768 LSE Xtal that we will use for accurate MSI frequency
> Msi;

// A data-type for the clock tree
typedef Clocks::AnySycClk <
	Msi							// uses MSI for the clock tree
> SysClk;

// Types for experiment 4
typedef Gpio::AnyOut<Gpio::Port::PA, 10> LedB;
typedef Gpio::AnyOut<Gpio::Port::PA, 9> LedG;
typedef Gpio::AnyOut<Gpio::Port::PA, 8> SignalOut;

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
	SignalOut,					// R signal of RGB LED for experiment 4
	LedG,					// G signal of RGB LED for experiment 4
	LedB,					// B signal of RGB LED for experiment 4
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

