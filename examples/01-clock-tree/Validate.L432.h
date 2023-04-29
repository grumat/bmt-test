#pragma once

typedef Gpio::Unused<1, Gpio::PuPd::kFloating> Test00;
static_assert(Test00::kMODER_ == 0x00000000, "Value of MODER register is invalid");
static_assert(Test00::kMODER_Mask_ == 0xfffffff3, "Value of MODER register mask is invalid");
static_assert(Test00::kOTYPER_ == 0x00000000, "Value of OTYPER register is invalid");
static_assert(Test00::kOTYPER_Mask_ == 0xffffffff, "Value of OTYPER register mask is invalid");
static_assert(Test00::kOSPEEDR_ == 0x00000000, "Value of OSPEEDR register is invalid");
static_assert(Test00::kOSPEEDR_Mask_ == 0xffffffff, "Value of OSPEEDR register mask is invalid");
static_assert(Test00::kPUPDR_ == 0x00000000, "Value of PUPDR register is invalid");
static_assert(Test00::kPUPDR_Mask_ == 0xfffffff3, "Value of PUPDR register mask is invalid");
static_assert(Test00::kBitValue_ == 0x00000002, "Value of ODR register is invalid");
static_assert(Test00::kBsrrValue_ == 0x00020000, "Value of BSSR register is invalid");
static_assert(Test00::kODR_ == 0x00000000, "Value of ODR register is invalid");
static_assert(Test00::kODR_Mask_ == 0xffffffff, "Value of ODR register mask is invalid");
static_assert(Test00::kAFRL_ == 0x00000000, "Value of AFRL register is invalid");
static_assert(Test00::kAFRL_Mask_ == 0xffffffff, "Value of AFRL register mask is invalid");
static_assert(Test00::kAFRH_ == 0x00000000, "Value of AFRH register is invalid");
static_assert(Test00::kAFRH_Mask_ == 0xffffffff, "Value of AFRH register mask is invalid");

typedef Gpio::Unused<1, Gpio::PuPd::kPullUp> Test01;
static_assert(Test01::kMODER_ == 0x00000000, "Value of MODER register is invalid");
static_assert(Test01::kMODER_Mask_ == 0xfffffff3, "Value of MODER register mask is invalid");
static_assert(Test01::kOTYPER_ == 0x00000000, "Value of OTYPER register is invalid");
static_assert(Test01::kOTYPER_Mask_ == 0xffffffff, "Value of OTYPER register mask is invalid");
static_assert(Test01::kOSPEEDR_ == 0x00000000, "Value of OSPEEDR register is invalid");
static_assert(Test01::kOSPEEDR_Mask_ == 0xffffffff, "Value of OSPEEDR register mask is invalid");
static_assert(Test01::kPUPDR_ == 0x00000004, "Value of PUPDR register is invalid");
static_assert(Test01::kPUPDR_Mask_ == 0xfffffff3, "Value of PUPDR register mask is invalid");
static_assert(Test01::kBitValue_ == 0x00000002, "Value of ODR register is invalid");
static_assert(Test01::kBsrrValue_ == 0x00020000, "Value of BSSR register is invalid");
static_assert(Test01::kODR_ == 0x00000000, "Value of ODR register is invalid");
static_assert(Test01::kODR_Mask_ == 0xffffffff, "Value of ODR register mask is invalid");
static_assert(Test01::kAFRL_ == 0x00000000, "Value of AFRL register is invalid");
static_assert(Test01::kAFRL_Mask_ == 0xffffffff, "Value of AFRL register mask is invalid");
static_assert(Test01::kAFRH_ == 0x00000000, "Value of AFRH register is invalid");
static_assert(Test01::kAFRH_Mask_ == 0xffffffff, "Value of AFRH register mask is invalid");

typedef Gpio::Unused<1, Gpio::PuPd::kPullDown> Test02;
static_assert(Test02::kMODER_ == 0x00000000, "Value of MODER register is invalid");
static_assert(Test02::kMODER_Mask_ == 0xfffffff3, "Value of MODER register mask is invalid");
static_assert(Test02::kOTYPER_ == 0x00000000, "Value of OTYPER register is invalid");
static_assert(Test02::kOTYPER_Mask_ == 0xffffffff, "Value of OTYPER register mask is invalid");
static_assert(Test02::kOSPEEDR_ == 0x00000000, "Value of OSPEEDR register is invalid");
static_assert(Test02::kOSPEEDR_Mask_ == 0xffffffff, "Value of OSPEEDR register mask is invalid");
static_assert(Test02::kPUPDR_ == 0x00000008, "Value of PUPDR register is invalid");
static_assert(Test02::kPUPDR_Mask_ == 0xfffffff3, "Value of PUPDR register mask is invalid");
static_assert(Test02::kBitValue_ == 0x00000002, "Value of ODR register is invalid");
static_assert(Test02::kBsrrValue_ == 0x00020000, "Value of BSSR register is invalid");
static_assert(Test02::kODR_ == 0x00000000, "Value of ODR register is invalid");
static_assert(Test02::kODR_Mask_ == 0xffffffff, "Value of ODR register mask is invalid");
static_assert(Test02::kAFRL_ == 0x00000000, "Value of AFRL register is invalid");
static_assert(Test02::kAFRL_Mask_ == 0xffffffff, "Value of AFRL register mask is invalid");
static_assert(Test02::kAFRH_ == 0x00000000, "Value of AFRH register is invalid");
static_assert(Test02::kAFRH_Mask_ == 0xffffffff, "Value of AFRH register mask is invalid");

typedef Gpio::Unchanged<1> Test03;
static_assert(Test03::kMODER_ == 0x00000000, "Value of MODER register is invalid");
static_assert(Test03::kMODER_Mask_ == 0xffffffff, "Value of MODER register mask is invalid");
static_assert(Test03::kOTYPER_ == 0x00000000, "Value of OTYPER register is invalid");
static_assert(Test03::kOTYPER_Mask_ == 0xffffffff, "Value of OTYPER register mask is invalid");
static_assert(Test03::kOSPEEDR_ == 0x00000000, "Value of OSPEEDR register is invalid");
static_assert(Test03::kOSPEEDR_Mask_ == 0xffffffff, "Value of OSPEEDR register mask is invalid");
static_assert(Test03::kPUPDR_ == 0x00000000, "Value of PUPDR register is invalid");
static_assert(Test03::kPUPDR_Mask_ == 0xffffffff, "Value of PUPDR register mask is invalid");
static_assert(Test03::kBitValue_ == 0x00000000, "Value of Bit value register is invalid");
static_assert(Test03::kBsrrValue_ == 0x00000000, "Value of BSSR register is invalid");
static_assert(Test03::kODR_ == 0x00000000, "Value of ODR register is invalid");
static_assert(Test03::kODR_Mask_ == 0xffffffff, "Value of ODR register mask is invalid");
static_assert(Test03::kAFRL_ == 0x00000000, "Value of AFRL register is invalid");
static_assert(Test03::kAFRL_Mask_ == 0xffffffff, "Value of AFRL register mask is invalid");
static_assert(Test03::kAFRH_ == 0x00000000, "Value of AFRH register is invalid");
static_assert(Test03::kAFRH_Mask_ == 0xffffffff, "Value of AFRH register mask is invalid");

typedef Gpio::AnyPin<
	Gpio::Port::PA,
	15,
	Gpio::Mode::kInput,
	Gpio::Speed::kInput,
	Gpio::PuPd::kPullDown,
	Gpio::Level::kHigh,
	Gpio::AfJTDI_PA15
> Test04;
static_assert(Test04::kMODER_ == 0x00000000, "Value of MODER register is invalid");
static_assert(Test04::kMODER_Mask_ == 0x3fffffff, "Value of MODER register mask is invalid");
static_assert(Test04::kOTYPER_ == 0x00000000, "Value of OTYPER register is invalid");
static_assert(Test04::kOTYPER_Mask_ == 0xffffffff, "Value of OTYPER register mask is invalid");
static_assert(Test04::kOSPEEDR_ == 0x00000000, "Value of OSPEEDR register is invalid");
static_assert(Test04::kOSPEEDR_Mask_ == 0xffffffff, "Value of OSPEEDR register mask is invalid");
static_assert(Test04::kPUPDR_ == 0x80000000, "Value of PUPDR register is invalid");
static_assert(Test04::kPUPDR_Mask_ == 0x3fffffff, "Value of PUPDR register mask is invalid");
static_assert(Test04::kBitValue_ == 0x00008000, "Value of Bit mask is invalid");
static_assert(Test04::kBsrrValue_ == 0x80000000, "Value of BSSR register is invalid");
static_assert(Test04::kODR_ == 0x00008000, "Value of ODR register is invalid");
static_assert(Test04::kODR_Mask_ == 0xffff7fff, "Value of ODR register mask is invalid");
static_assert(Test04::kAFRL_ == 0x00000000, "Value of AFRL register is invalid");
static_assert(Test04::kAFRL_Mask_ == 0xffffffff, "Value of AFRL register mask is invalid");
static_assert(Test04::kAFRH_ == 0x00000000, "Value of AFRH register is invalid");
static_assert(Test04::kAFRH_Mask_ == 0x0fffffff, "Value of AFRH register mask is invalid");

typedef Gpio::AnyPin<
	Gpio::Port::PA,
	15,
	Gpio::Mode::kInput,
	Gpio::Speed::kInput,
	Gpio::PuPd::kPullUp,
	Gpio::Level::kLow,
	Gpio::AfSPI1_NSS_PA15
> Test05;
static_assert(Test05::kMODER_ == 0x00000000, "Value of MODER register is invalid");
static_assert(Test05::kMODER_Mask_ == 0x3fffffff, "Value of MODER register mask is invalid");
static_assert(Test05::kOTYPER_ == 0x00000000, "Value of OTYPER register is invalid");
static_assert(Test05::kOTYPER_Mask_ == 0xffffffff, "Value of OTYPER register mask is invalid");
static_assert(Test05::kOSPEEDR_ == 0x00000000, "Value of OSPEEDR register is invalid");
static_assert(Test05::kOSPEEDR_Mask_ == 0xffffffff, "Value of OSPEEDR register mask is invalid");
static_assert(Test05::kPUPDR_ == 0x40000000, "Value of PUPDR register is invalid");
static_assert(Test05::kPUPDR_Mask_ == 0x3fffffff, "Value of PUPDR register mask is invalid");
static_assert(Test05::kBitValue_ == 0x00008000, "Value of Bit mask is invalid");
static_assert(Test05::kBsrrValue_ == 0x80000000, "Value of BSSR register is invalid");
static_assert(Test05::kODR_ == 0x00000000, "Value of ODR register is invalid");
static_assert(Test05::kODR_Mask_ == 0xffffffff, "Value of ODR register mask is invalid");
static_assert(Test05::kAFRL_ == 0x00000000, "Value of AFRL register is invalid");
static_assert(Test05::kAFRL_Mask_ == 0xffffffff, "Value of AFRL register mask is invalid");
static_assert(Test05::kAFRH_ == 0x50000000, "Value of AFRH register is invalid");
static_assert(Test05::kAFRH_Mask_ == 0x0fffffff, "Value of AFRH register mask is invalid");

typedef Gpio::AnyPin<
	Gpio::Port::PA,
	15,
	Gpio::Mode::kAnalog,
	Gpio::Speed::kInput,
	Gpio::PuPd::kFloating,
	Gpio::Level::kLow,
	Gpio::AfSPI3_NSS_PA15
> Test06;
static_assert(Test06::kMODER_ == 0xc0000000, "Value of MODER register is invalid");
static_assert(Test06::kMODER_Mask_ == 0x3fffffff, "Value of MODER register mask is invalid");
static_assert(Test06::kOTYPER_ == 0x00000000, "Value of OTYPER register is invalid");
static_assert(Test06::kOTYPER_Mask_ == 0xffffffff, "Value of OTYPER register mask is invalid");
static_assert(Test06::kOSPEEDR_ == 0x00000000, "Value of OSPEEDR register is invalid");
static_assert(Test06::kOSPEEDR_Mask_ == 0xffffffff, "Value of OSPEEDR register mask is invalid");
static_assert(Test06::kPUPDR_ == 0x00000000, "Value of PUPDR register is invalid");
static_assert(Test06::kPUPDR_Mask_ == 0x3fffffff, "Value of PUPDR register mask is invalid");
static_assert(Test06::kBitValue_ == 0x00008000, "Value of Bit mask is invalid");
static_assert(Test06::kBsrrValue_ == 0x80000000, "Value of BSSR register is invalid");
static_assert(Test06::kODR_ == 0x00000000, "Value of ODR register is invalid");
static_assert(Test06::kODR_Mask_ == 0xffffffff, "Value of ODR register mask is invalid");
static_assert(Test06::kAFRL_ == 0x00000000, "Value of AFRL register is invalid");
static_assert(Test06::kAFRL_Mask_ == 0xffffffff, "Value of AFRL register mask is invalid");
static_assert(Test06::kAFRH_ == 0x60000000, "Value of AFRH register is invalid");
static_assert(Test06::kAFRH_Mask_ == 0x0fffffff, "Value of AFRH register mask is invalid");

typedef Gpio::AnyPin<
	Gpio::Port::PA,
	15,
	Gpio::Mode::kOutput,
	Gpio::Speed::kSlow,
	Gpio::PuPd::kFloating,
	Gpio::Level::kLow,
	Gpio::AfSWPMI1_SUSPEND_PA15
> Test07;
static_assert(Test07::kMODER_ == 0x40000000, "Value of MODER register is invalid");
static_assert(Test07::kMODER_Mask_ == 0x3fffffff, "Value of MODER register mask is invalid");
static_assert(Test07::kOTYPER_ == 0x00000000, "Value of OTYPER register is invalid");
static_assert(Test07::kOTYPER_Mask_ == 0xffff7fff, "Value of OTYPER register mask is invalid");
static_assert(Test07::kOSPEEDR_ == 0x00000000, "Value of OSPEEDR register is invalid");
static_assert(Test07::kOSPEEDR_Mask_ == 0x3fffffff, "Value of OSPEEDR register mask is invalid");
static_assert(Test07::kPUPDR_ == 0x00000000, "Value of PUPDR register is invalid");
static_assert(Test07::kPUPDR_Mask_ == 0x3fffffff, "Value of PUPDR register mask is invalid");
static_assert(Test07::kBitValue_ == 0x00008000, "Value of Bit mask is invalid");
static_assert(Test07::kBsrrValue_ == 0x80000000, "Value of BSSR register is invalid");
static_assert(Test07::kODR_ == 0x00000000, "Value of ODR register is invalid");
static_assert(Test07::kODR_Mask_ == 0xffffffff, "Value of ODR register mask is invalid");
static_assert(Test07::kAFRL_ == 0x00000000, "Value of AFRL register is invalid");
static_assert(Test07::kAFRL_Mask_ == 0xffffffff, "Value of AFRL register mask is invalid");
static_assert(Test07::kAFRH_ == 0xc0000000, "Value of AFRH register is invalid");
static_assert(Test07::kAFRH_Mask_ == 0x0fffffff, "Value of AFRH register mask is invalid");

