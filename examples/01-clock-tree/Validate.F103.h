#pragma once

typedef Gpio::AnyPin<Gpio::Port::PA
	, 1
	, Gpio::Mode::kInput
	, Gpio::Speed::kInput
	, Gpio::PuPd::kFloating
	, Gpio::Level::kLow
	, Gpio::AfNoRemap
> Test01;

static_assert(Test01::kCRL_ == 0x00000040, "Error computing CRL value");
static_assert(Test01::kCRL_Mask_ == 0xffffff0f, "Error computing CRL Mask value");
static_assert(Test01::kCRH_ == 0x00000000, "Error computing CRH value");
static_assert(Test01::kCRH_Mask_ == 0xffffffff, "Error computing CRH Mask value");
static_assert(Test01::kODR_ == 0x00000000, "Error computing ODR value");
static_assert(Test01::kAfConf_ == 0x00000000, "Error computing AfConf value");
static_assert(Test01::kAfMask_ == 0xffffffff, "Error computing AfMask value");

typedef Gpio::AnyPin<Gpio::Port::PA
	, 1
	, Gpio::Mode::kInput
	, Gpio::Speed::kFastest
	, Gpio::PuPd::kFloating
	, Gpio::Level::kLow
	, Gpio::AfNoRemap
> Test02;

static_assert(Test02::kCRL_ == 0x00000040, "Error computing CRL value");
static_assert(Test02::kCRL_Mask_ == 0xffffff0f, "Error computing CRL Mask value");

typedef Gpio::AnyPin<Gpio::Port::PA
	, 1
	, Gpio::Mode::kInput
	, Gpio::Speed::kInput
	, Gpio::PuPd::kPullUp
	, Gpio::Level::kLow
	, Gpio::AfNoRemap
> Test03;
static_assert(Test03::kCRL_ == 0x00000080, "Error computing CRL value");
static_assert(Test03::kODR_ == 0x00000002, "Error computing ODR value");

typedef Gpio::AnyPin<Gpio::Port::PA
	, 1
	, Gpio::Mode::kInput
	, Gpio::Speed::kInput
	, Gpio::PuPd::kPullDown
	, Gpio::Level::kHigh
	, Gpio::AfJtag5
> Test04;
static_assert(Test04::kCRL_ == 0x00000080, "Error computing CRL value");
static_assert(Test04::kODR_ == 0x00000000, "Error computing ODR value");
static_assert(Test04::kAfConf_ == 0x00000000, "Error computing AfConf value");
static_assert(Test04::kAfMask_ == 0xf8ffffff, "Error computing AfMask value");

typedef Gpio::AnyPin<Gpio::Port::PA
	, 1
	, Gpio::Mode::kAnalog
	, Gpio::Speed::kInput
	, Gpio::PuPd::kPullDown
	, Gpio::Level::kLow
	, Gpio::AfJtag4
> Test05;
static_assert(Test05::kCRL_ == 0x00000000, "Error computing CRL value");
static_assert(Test05::kCRL_Mask_ == 0xffffff0f, "Error computing CRL Mask value");
static_assert(Test05::kCRH_ == 0x00000000, "Error computing CRH value");
static_assert(Test05::kCRH_Mask_ == 0xffffffff, "Error computing CRH Mask value");
static_assert(Test05::kODR_ == 0x00000000, "Error computing ODR value");
static_assert(Test05::kAfConf_ == 0x01000000, "Error computing AfConf value");
static_assert(Test05::kAfMask_ == 0xf8ffffff, "Error computing AfMask value");

typedef Gpio::AnyPin<Gpio::Port::PA
	, 1
	, Gpio::Mode::kAnalog
	, Gpio::Speed::kInput
	, Gpio::PuPd::kPullDown
	, Gpio::Level::kHigh
	, Gpio::AfSwd3
> Test06;
static_assert(Test06::kCRL_ == 0x00000000, "Error computing CRL value");
static_assert(Test06::kCRL_Mask_ == 0xffffff0f, "Error computing CRL Mask value");
static_assert(Test06::kCRH_ == 0x00000000, "Error computing CRH value");
static_assert(Test06::kCRH_Mask_ == 0xffffffff, "Error computing CRH Mask value");
static_assert(Test06::kODR_ == 0x00000002, "Error computing ODR value");
static_assert(Test06::kAfConf_ == 0x02000000, "Error computing AfConf value");
static_assert(Test06::kAfMask_ == 0xf8ffffff, "Error computing AfMask value");

typedef Gpio::AnyPin<Gpio::Port::PA
	, 1
	, Gpio::Mode::kAnalog
	, Gpio::Speed::kFastest
	, Gpio::PuPd::kFloating
	, Gpio::Level::kLow
	, Gpio::AfSwd2
> Test07;
static_assert(Test07::kCRL_ == 0x00000000, "Error computing CRL value");
static_assert(Test07::kCRL_Mask_ == 0xffffff0f, "Error computing CRL Mask value");
static_assert(Test07::kCRH_ == 0x00000000, "Error computing CRH value");
static_assert(Test07::kCRH_Mask_ == 0xffffffff, "Error computing CRH Mask value");
static_assert(Test07::kODR_ == 0x00000000, "Error computing ODR value");
static_assert(Test07::kAfConf_ == 0x04000000, "Error computing AfConf value");
static_assert(Test07::kAfMask_ == 0xf8ffffff, "Error computing AfMask value");

typedef Gpio::AnyPin<Gpio::Port::PA
	, 9
	, Gpio::Mode::kOutput
	, Gpio::Speed::kFastest
	, Gpio::PuPd::kFloating
	, Gpio::Level::kLow
	, Gpio::Af_PD01_OSC
> Test08;
static_assert(Test08::kCRL_ == 0x00000000, "Error computing CRL value");
static_assert(Test08::kCRL_Mask_ == 0xffffffff, "Error computing CRL Mask value");
static_assert(Test08::kCRH_ == 0x00000030, "Error computing CRH value");
static_assert(Test08::kCRH_Mask_ == 0xffffff0f, "Error computing CRH Mask value");
static_assert(Test08::kODR_ == 0x00000000, "Error computing ODR value");
static_assert(Test08::kAfConf_ == 0x00000000, "Error computing AfConf value");
static_assert(Test08::kAfMask_ == 0xffff7fff, "Error computing AfMask value");

typedef Gpio::AnyPin<Gpio::Port::PA
	, 1
	, Gpio::Mode::kOutput
	, Gpio::Speed::kFast
	, Gpio::PuPd::kFloating
	, Gpio::Level::kHigh
	, Gpio::Af_PD01_GPIO
> Test09;
static_assert(Test09::kCRL_ == 0x00000030, "Error computing CRL value");
static_assert(Test09::kCRL_Mask_ == 0xffffff0f, "Error computing CRL Mask value");
static_assert(Test09::kCRH_ == 0x00000000, "Error computing CRH value");
static_assert(Test09::kCRH_Mask_ == 0xffffffff, "Error computing CRH Mask value");
static_assert(Test09::kODR_ == 0x00000002, "Error computing ODR value");
static_assert(Test09::kAfConf_ == 0x00008000, "Error computing AfConf value");
static_assert(Test09::kAfMask_ == 0xffff7fff, "Error computing AfMask value");

typedef Gpio::AnyPin<Gpio::Port::PA
	, 1
	, Gpio::Mode::kOutput
	, Gpio::Speed::kMedium
	, Gpio::PuPd::kPullUp
	, Gpio::Level::kLow
	, Gpio::AfTim2_PA0_1_PB10_11
> Test10;
static_assert(Test10::kCRL_ == 0x00000010, "Error computing CRL value");
static_assert(Test10::kCRL_Mask_ == 0xffffff0f, "Error computing CRL Mask value");
static_assert(Test10::kCRH_ == 0x00000000, "Error computing CRH value");
static_assert(Test10::kCRH_Mask_ == 0xffffffff, "Error computing CRH Mask value");
static_assert(Test10::kODR_ == 0x00000000, "Error computing ODR value");
static_assert(Test10::kAfConf_ == 0x00000200, "Error computing AfConf value");
static_assert(Test10::kAfMask_ == 0xfffffcff, "Error computing AfMask value");

typedef Gpio::AnyPin<Gpio::Port::PA
	, 1
	, Gpio::Mode::kOutput
	, Gpio::Speed::kSlow
	, Gpio::PuPd::kPullDown
	, Gpio::Level::kLow
	, Gpio::AfCan_PD0_1
> Test11;
static_assert(Test11::kCRL_ == 0x00000020, "Error computing CRL value");
static_assert(Test11::kCRL_Mask_ == 0xffffff0f, "Error computing CRL Mask value");
static_assert(Test11::kCRH_ == 0x00000000, "Error computing CRH value");
static_assert(Test11::kCRH_Mask_ == 0xffffffff, "Error computing CRH Mask value");
static_assert(Test11::kODR_ == 0x00000000, "Error computing ODR value");
static_assert(Test11::kAfConf_ == 0x00006000, "Error computing AfConf value");
static_assert(Test11::kAfMask_ == 0xffff9fff, "Error computing AfMask value");

typedef Gpio::AnyPin<Gpio::Port::PA
	, 1
	, Gpio::Mode::kOpenDrain
	, Gpio::Speed::kSlow
	, Gpio::PuPd::kPullUp
	, Gpio::Level::kLow
	, Gpio::AfCan_PB8_9
> Test12;
static_assert(Test12::kCRL_ == 0x00000060, "Error computing CRL value");
static_assert(Test12::kCRL_Mask_ == 0xffffff0f, "Error computing CRL Mask value");
static_assert(Test12::kCRH_ == 0x00000000, "Error computing CRH value");
static_assert(Test12::kCRH_Mask_ == 0xffffffff, "Error computing CRH Mask value");
static_assert(Test12::kODR_ == 0x00000000, "Error computing ODR value");
static_assert(Test12::kAfConf_ == 0x00004000, "Error computing AfConf value");
static_assert(Test12::kAfMask_ == 0xffff9fff, "Error computing AfMask value");

typedef Gpio::AnyPin<Gpio::Port::PA
	, 1
	, Gpio::Mode::kOpenDrain
	, Gpio::Speed::kMedium
	, Gpio::PuPd::kPullUp
	, Gpio::Level::kLow
	, Gpio::AfCan_PA11_12
> Test13;
static_assert(Test13::kCRL_ == 0x00000050, "Error computing CRL value");
static_assert(Test13::kCRL_Mask_ == 0xffffff0f, "Error computing CRL Mask value");
static_assert(Test13::kCRH_ == 0x00000000, "Error computing CRH value");
static_assert(Test13::kCRH_Mask_ == 0xffffffff, "Error computing CRH Mask value");
static_assert(Test13::kODR_ == 0x00000000, "Error computing ODR value");
static_assert(Test13::kAfConf_ == 0x00000000, "Error computing AfConf value");
static_assert(Test13::kAfMask_ == 0xffff9fff, "Error computing AfMask value");

typedef Gpio::AnyPin<Gpio::Port::PA
	, 1
	, Gpio::Mode::kOpenDrain
	, Gpio::Speed::kFast
	, Gpio::PuPd::kPullDown
	, Gpio::Level::kHigh
	, Gpio::AfTim4_PD12_13_14_15
> Test14;
static_assert(Test14::kCRL_ == 0x00000070, "Error computing CRL value");
static_assert(Test14::kCRL_Mask_ == 0xffffff0f, "Error computing CRL Mask value");
static_assert(Test14::kCRH_ == 0x00000000, "Error computing CRH value");
static_assert(Test14::kCRH_Mask_ == 0xffffffff, "Error computing CRH Mask value");
static_assert(Test14::kODR_ == 0x00000002, "Error computing ODR value");
static_assert(Test14::kAfConf_ == 0x00001000, "Error computing AfConf value");
static_assert(Test14::kAfMask_ == 0xffffefff, "Error computing AfMask value");

typedef Gpio::AnyPin<Gpio::Port::PA
	, 2
	, Gpio::Mode::kAlternate
	, Gpio::Speed::kFast
	, Gpio::PuPd::kPullDown
	, Gpio::Level::kHigh
	, Gpio::AfTim4_PB6_7_8_9
> Test15;
static_assert(Test15::kCRL_ == 0x00000b00, "Error computing CRL value");
static_assert(Test15::kCRL_Mask_ == 0xfffff0ff, "Error computing CRL Mask value");
static_assert(Test15::kCRH_ == 0x00000000, "Error computing CRH value");
static_assert(Test15::kCRH_Mask_ == 0xffffffff, "Error computing CRH Mask value");
static_assert(Test15::kODR_ == 0x00000004, "Error computing ODR value");
static_assert(Test15::kAfConf_ == 0x00000000, "Error computing AfConf value");
static_assert(Test15::kAfMask_ == 0xffffefff, "Error computing AfMask value");

typedef Gpio::AnyPin<Gpio::Port::PA
	, 3
	, Gpio::Mode::kAlternate
	, Gpio::Speed::kMedium
	, Gpio::PuPd::kPullDown
	, Gpio::Level::kHigh
	, Gpio::AfTim3_PC6_7_8_9
> Test16;
static_assert(Test16::kCRL_ == 0x00009000, "Error computing CRL value");
static_assert(Test16::kCRL_Mask_ == 0xffff0fff, "Error computing CRL Mask value");
static_assert(Test16::kCRH_ == 0x00000000, "Error computing CRH value");
static_assert(Test16::kCRH_Mask_ == 0xffffffff, "Error computing CRH Mask value");
static_assert(Test16::kODR_ == 0x00000008, "Error computing ODR value");
static_assert(Test16::kAfConf_ == 0x00000c00, "Error computing AfConf value");
static_assert(Test16::kAfMask_ == 0xfffff3ff, "Error computing AfMask value");

typedef Gpio::AnyPin<Gpio::Port::PA
	, 4
	, Gpio::Mode::kAlternate
	, Gpio::Speed::kSlow
	, Gpio::PuPd::kPullDown
	, Gpio::Level::kHigh
	, Gpio::AfTim3_PB4_5_0_1
> Test17;
static_assert(Test17::kCRL_ == 0x000a0000, "Error computing CRL value");
static_assert(Test17::kCRL_Mask_ == 0xfff0ffff, "Error computing CRL Mask value");
static_assert(Test17::kCRH_ == 0x00000000, "Error computing CRH value");
static_assert(Test17::kCRH_Mask_ == 0xffffffff, "Error computing CRH Mask value");
static_assert(Test17::kODR_ == 0x00000010, "Error computing ODR value");
static_assert(Test17::kAfConf_ == 0x00000800, "Error computing AfConf value");
static_assert(Test17::kAfMask_ == 0xfffff3ff, "Error computing AfMask value");

typedef Gpio::AnyPin<Gpio::Port::PA
	, 5
	, Gpio::Mode::kOpenDrainAlt
	, Gpio::Speed::kSlow
	, Gpio::PuPd::kPullDown
	, Gpio::Level::kHigh
	, Gpio::AfTim3_PA6_7_PB0_1
> Test18;
static_assert(Test18::kCRL_ == 0x00e00000, "Error computing CRL value");
static_assert(Test18::kCRL_Mask_ == 0xff0fffff, "Error computing CRL Mask value");
static_assert(Test18::kCRH_ == 0x00000000, "Error computing CRH value");
static_assert(Test18::kCRH_Mask_ == 0xffffffff, "Error computing CRH Mask value");
static_assert(Test18::kODR_ == 0x00000020, "Error computing ODR value");
static_assert(Test18::kAfConf_ == 0x00000000, "Error computing AfConf value");
static_assert(Test18::kAfMask_ == 0xfffff3ff, "Error computing AfMask value");

typedef Gpio::AnyPin<Gpio::Port::PA
	, 6
	, Gpio::Mode::kOpenDrainAlt
	, Gpio::Speed::kMedium
	, Gpio::PuPd::kPullDown
	, Gpio::Level::kHigh
	, Gpio::AfTim2_PA15_PB3_10_11
> Test19;
static_assert(Test19::kCRL_ == 0x0d000000, "Error computing CRL value");
static_assert(Test19::kCRL_Mask_ == 0xf0ffffff, "Error computing CRL Mask value");
static_assert(Test19::kCRH_ == 0x00000000, "Error computing CRH value");
static_assert(Test19::kCRH_Mask_ == 0xffffffff, "Error computing CRH Mask value");
static_assert(Test19::kODR_ == 0x00000040, "Error computing ODR value");
static_assert(Test19::kAfConf_ == 0x00000300, "Error computing AfConf value");
static_assert(Test19::kAfMask_ == 0xfffffcff, "Error computing AfMask value");

typedef Gpio::Unused<
	1
	, Gpio::PuPd::kPullUp
> Test20;
static_assert(Test20::kCRL_ == 0x00000080, "Error computing CRL value");
static_assert(Test20::kCRL_Mask_ == 0xffffff0f, "Error computing CRL Mask value");
static_assert(Test20::kCRH_ == 0x00000000, "Error computing CRH value");
static_assert(Test20::kCRH_Mask_ == 0xffffffff, "Error computing CRH Mask value");
static_assert(Test20::kBitValue_ == 0x00000000, "Error computing BitValue value");
static_assert(Test20::kODR_ == 0x00000002, "Error computing ODR value");
static_assert(Test20::kAfConf_ == 0x00000000, "Error computing AfConf value");
static_assert(Test20::kAfMask_ == 0xffffffff, "Error computing AfMask value");

typedef Gpio::Unused<
	1
	, Gpio::PuPd::kPullDown
> Test21;
static_assert(Test21::kCRL_ == 0x00000080, "Error computing CRL value");
static_assert(Test21::kCRL_Mask_ == 0xffffff0f, "Error computing CRL Mask value");
static_assert(Test21::kCRH_ == 0x00000000, "Error computing CRH value");
static_assert(Test21::kCRH_Mask_ == 0xffffffff, "Error computing CRH Mask value");
static_assert(Test21::kBitValue_ == 0x00000000, "Error computing BitValue value");
static_assert(Test21::kODR_ == 0x00000000, "Error computing ODR value");
static_assert(Test21::kAfConf_ == 0x00000000, "Error computing AfConf value");
static_assert(Test21::kAfMask_ == 0xffffffff, "Error computing AfMask value");

typedef Gpio::Unchanged<1> Test22;
static_assert(Test22::kCRL_ == 0x00000000, "Error computing CRL value");
static_assert(Test22::kCRL_Mask_ == 0xffffffff, "Error computing CRL Mask value");
static_assert(Test22::kCRH_ == 0x00000000, "Error computing CRH value");
static_assert(Test22::kCRH_Mask_ == 0xffffffff, "Error computing CRH Mask value");
static_assert(Test22::kBitValue_ == 0x00000000, "Error computing BitValue value");
static_assert(Test22::kODR_ == 0x00000000, "Error computing ODR value");
static_assert(Test22::kAfConf_ == 0x00000000, "Error computing AfConf value");
static_assert(Test22::kAfMask_ == 0xffffffff, "Error computing AfMask value");

