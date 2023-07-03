#include <bmt.h>

using namespace Bmt;
using namespace Bmt::Timer;

#ifdef STM32F103xB
#	include "hal.f103.h"
#elif defined(STM32L432xx)
#	include "hal.l432.h"
#elif defined(STM32G431xx)
#	include "hal.g431.h"
#else
#error Unsupported configuration
#endif


// This table contains an ECG sample using Absolute Offset Bytes format.
static constexpr uint8_t s_EcgTable[] =
{
	0x2D, 0x2D, 0x2F, 0x30, 0x31, 0x32, 0x34, 0x34,
	0x35, 0x36, 0x36, 0x37, 0x39, 0x3A, 0x3B, 0x3C,
	0x3E, 0x3F, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x43,
	0x43, 0x43, 0x42, 0x40, 0x3F, 0x3F, 0x3E, 0x3C,
	0x3B, 0x3A, 0x38, 0x35, 0x34, 0x33, 0x31, 0x30,
	0x2F, 0x2E, 0x2D, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C,
	0x2C, 0x2A, 0x29, 0x27, 0x25, 0x25, 0x23, 0x23,
	0x21, 0x21, 0x20, 0x20, 0x24, 0x25, 0x28, 0x2E,
	0x5C, 0x9E, 0xD6, 0xF4, 0xFD, 0xFC, 0xED, 0xD9,
	0xC2, 0xAE, 0x9E, 0x8A, 0x78, 0x64, 0x53, 0x41,
	0x36, 0x2B, 0x20, 0x15, 0x0E, 0x08, 0x0F, 0x14,
	0x19, 0x1B, 0x1E, 0x20, 0x22, 0x23, 0x24, 0x25,
	0x26, 0x26, 0x27, 0x27, 0x28, 0x29, 0x2A, 0x2A,
	0x2A, 0x2B, 0x2B, 0x2C, 0x2C, 0x2D, 0x2E, 0x2D,
	0x2D, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C,
	0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2D, 0x2D, 0x2D,
	0x2D, 0x2D, 0x2E, 0x2E, 0x2F, 0x2F, 0x30, 0x30,
	0x31, 0x31, 0x32, 0x32, 0x33, 0x33, 0x34, 0x35,
	0x36, 0x37, 0x39, 0x3A, 0x3A, 0x3B, 0x3C, 0x3E,
	0x3F, 0x3F, 0x40, 0x42, 0x43, 0x44, 0x45, 0x46,
	0x47, 0x47, 0x49, 0x49, 0x4A, 0x4A, 0x4A, 0x4A,
	0x4B, 0x4B, 0x4B, 0x4B, 0x4B, 0x4C, 0x4C, 0x4C,
	0x4D, 0x4D, 0x4D, 0x4D, 0x4C, 0x4C, 0x4B, 0x4B,
	0x4B, 0x4A, 0x49, 0x48, 0x47, 0x47, 0x46, 0x45,
	0x44, 0x44, 0x43, 0x43, 0x42, 0x40, 0x3F, 0x3F,
	0x3E, 0x3C, 0x3B, 0x3A, 0x3A, 0x39, 0x38, 0x37,
	0x36, 0x35, 0x35, 0x34, 0x34, 0x34, 0x34, 0x33,
	0x33, 0x32, 0x32, 0x32, 0x31, 0x31, 0x31, 0x31,
	0x31, 0x31, 0x30, 0x30, 0x30, 0x2F, 0x2E, 0x2E,
	0x2D, 0x2D, 0x2C, 
};

// Size of the table containing ECG samples
constexpr uint32_t kTableSize = _countof(s_EcgTable);

// We want to specify dummy counts on update timer, within updates
// (this increases timer clock frequency and make it suitable for higher clock frequencies)
constexpr uint32_t kDummyCount = 100;


// Computes the prescaler for 1 MHz counter speed
typedef InternalClock_Hz <kPwmTimer, SysClk, 1000000> PwmFreq;
// PWM should quantize a byte (0-255), producing almost 4 kHz PWM sample rate
// A ~50 Hz low pass filter is required to produce the ECG signal
typedef Any<PwmFreq, Mode::kUpCounter, 255> Pwm;

// The output channel, attached to PWM timer
typedef AnyOutputChannel<Pwm
	, kPwmOutChannel
	, OutMode::kPWM1
	, Output::kEnabled
	, Output::kDisabled
	, true
	, true
> PwmOut;

// Heart rate (Hard coded for this example; recompile for any feasible BPM)
constexpr uint32_t kBPM = 60;

// Data rate varies a bit so ECG image won't overlap on higher BPM rates
constexpr uint32_t kSPS = kBPM > 60 
	? 400 + 3*(kBPM - 60)
	: 400
	;
// Computes the prescaler to copy table with ECG samples to the PWM (x kDummyCount)
typedef InternalClock_Hz <kUpdateTimer, SysClk, kDummyCount * kSPS> UpdateFreq;
// Updates PWM values on every counter overflow using DMA
typedef Any<UpdateFreq, Mode::kUpCounter, kDummyCount-1> Updater;

// This DMA is triggered on every timer update
typedef Dma::AnyChannel<
	IdDmaUpdate
	, Dma::Dir::kMemToPer			// runs samples in a single shot then stop
	, Dma::PtrPolicy::kBytePtrInc	// source buffer are bytes
	, Dma::PtrPolicy::kLongPtr		// destination CCR register
> TheDma;


// A stopwatch to control BPM rate
typedef MicroStopWatch <Pwm, Pwm::ToTicks(Msec(60 * 1000UL / kBPM))> Tick32;


/*
This function is required by STM32 startup file and called during
initial startup.
*/
extern "C" void SystemInit()
{
	// Reset clock system before starting program
	System::Init();
	// Initialize Port A, B and C
	InitPA::Init();
	InitPB::Init();
	InitPC::Init();
	// Starts desired clock
	SysClk::Init();
	// Init PWM output
	PwmOut::Init();
	// Init sample updater
	Updater::Init();
	// Sample updates using DMA
	TheDma::Init();
}



/*
** General description: The s_EcgTable table contains samples to produce an ECG pulse
** having P, QRS and T pulses/waves. Once the pulse is finished, DMA stops and the last
** sample value is kept running until the DMA is rearmed.
** Some tricks are done by the settings above to accommodate adjustable heart rates.
** Sample rate is increased proportionally reducing all PQRST widths, which is probably not 
** completely valid for a natural beat.
** So as said, after the beat ends, DMA rests but PWM keeps outputting a constant ratio. A 
** software timer is kept tracking the heart rate interval. When heart rate interval is 
** reached, DMA is rearmed and a new cycle starts.
*/
int main()
{
	// Initialize DMA to transfer values to CCR0 of PWM Output
	TheDma::Setup();
	TheDma::Start(s_EcgTable, PwmOut::GetCcrAddress(), _countof(s_EcgTable));
	// Starts the PWM
	Pwm::CounterStart();
	// Starts the first cycle of the PWM updater
	Updater::EnableUpdateDma();
	Updater::CounterStart();
	// This software timer establishes the Heart Rate
	Tick32 stopwatch;
	while (true)
	{
		// Tests if heart rate interval is ellapsed
		if (!stopwatch.IsNotElapsed())
		{
			// Starts a LED blink to signal ECG cycle
			LedOn();
			// Restarts DMA for subsequent heart beats
			TheDma::Start(s_EcgTable, PwmOut::GetCcrAddress(), _countof(s_EcgTable));
		}
		else if (IsLedOn()
			&& (TheDma::GetTransferCount() < (7 * kTableSize / 8)))
		{
			// After a short period turn LED off
			LedOff();
		}
	}
	return 0;
}

