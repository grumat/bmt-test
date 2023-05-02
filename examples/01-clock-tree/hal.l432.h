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

// A data-type for the 48 MHz MSI clock
typedef Clocks::AnyMsi<
	Clocks::MsiFreq::k48_MHz		// Change STM32L432KC internal oscillator from 4 MHz to 48MHz (good for USB)
	, true							// Nucleo32 has an 32768 LSE Xtal that we will use for accurate MSI frequency
> Msi;
// Configure the PLL for 80 MHz
/*
** This configuration uses a calculator to obtain 80MHz from 48MHz. Obtainend PLL values are:
**		- PLLSCR:	0b01	(MSI)
**		- PLLM:		0b010	(/3)
**		- PLLN:		0x0a	(*10)
**		- PLLREN:	1		(PLLCLK output for the Cortex M4)
**		- PLLR:		0b00	(/2)
** Final frequency is 48MHz (/3) (*10) (/2) = 80MHz
*/
typedef Clocks::AnyPll<
	Msi								// link to 48MHz MSI clock
	, 80000000UL					// Max is 80 MHz
	, Clocks::AutoRange1			// Full voltage range calculator
> Pll;

// A data-type for the clock tree
typedef Clocks::AnySycClk <
	Pll,							// uses PLL for the clock tree
	//Msi,							// uses MSI for the clock tree
	Power::Mode::kRange1,			// Full Voltage for Max performance
	Clocks::AhbPrscl::k1,			// AHB 80 MHz
	Clocks::ApbPrscl::k2,			// APB1 40 Mhz
	Clocks::ApbPrscl::k1,			// APB2 80 MHz
	Clocks::SysClkOpts::kDefault,	// Do not deactivate clock
	Clocks::Mco::kMsi,				// output MSI to the MCO pin (48MHz/16 = 3MHz)
	//Clocks::Mco::kPllClk,			// output PLL to the MCO pin (80MHz/16 = 5MHz)
	Clocks::McoPrscl::k16			// CLK/16 for the MCO output is enough
> SysClk;

/*
** Experiment note: Using MSI with 32768 LSE lock works very good without the PLL.
** It is stable at 48.005 MHz like specified on the data-sheet. By attaching the
** PLL to this clock source a slight frequency reduction is observed: 47,776MHz.
** Seems too much deviation for USB application.
** Maybe the best option is to use HSI48 with SOF synchronisation.
*/

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
	Gpio::MCO_PA8,			// Alternate output for MCO signal
	Gpio::Unused<9>,		// unused pin (input + pull-down)
	Gpio::Unused<10>,		// unused pin (input + pull-down)
	Gpio::Unused<11>,		// unused pin (input + pull-down)
	Gpio::Unused<12>,		// unused pin (input + pull-down)
	Gpio::Unchanged<13>,	// don't change SWD/JTAG
	Gpio::Unchanged<14>,	// don't change SWD/JTAG
	Gpio::Unchanged<15>		// don't change SWD/JTAG
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

