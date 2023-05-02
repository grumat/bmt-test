#pragma once

/*
** Nucleo-G431KB
** https://www.st.com/en/evaluation-tools/nucleo-g431kb.html
*/

// A data-type for the 48 MHz MSI clock
typedef Clocks::AnyHsi16<> Hsi;		// 16MHz internal RC clock

// A data-type for the clock tree
typedef Clocks::AnySycClk <
	//Pll,							// uses PLL for the clock tree
	Hsi,							// uses HSI for the clock tree
	Power::Mode::kRange1,			// Full Voltage for Max performance
	Clocks::AhbPrscl::k1,			// AHB 8 MHz
	Clocks::ApbPrscl::k2,			// APB1 4 Mhz
	Clocks::ApbPrscl::k1,			// APB2 8 MHz
	Clocks::SysClkOpts::kDefault,	// Do not deactivate clock
	Clocks::Mco::kHsi16,			// output HSI16 to the MCO pin (48MHz/16 = 3MHz)
	//Clocks::Mco::kPllClk,			// output PLL to the MCO pin (80MHz/16 = 5MHz)
	Clocks::McoPrscl::k16			// CLK/16 for the MCO output is enough
> SysClk;

