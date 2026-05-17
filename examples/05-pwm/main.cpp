#include <bmt.h>

using namespace Bmt;

#ifdef STM32F103xB
#	include "hal.f103.h"
#elif defined(STM32L432xx)
#	include "hal.l432.h"
#elif defined(STM32G431xx)
#	include "hal.g431.h"
#else
#	error Unsupported configuration
#endif



// The data-type representing the system tick timer
using Tick = Timer::SysTickCounter<SysClk>;

// 40 KHz PWM base frequency using Timer 1
// This timer provides all 3 required outputs we need for this example
using PwmFreq = Timer::InternalClock_Hz<kPwmTim, SysClk, 40000>;
// This divides base frequency by 200; also, the range we can control LED brightness
using Pwm = Timer::Any<PwmFreq, Timer::Mode::kUpCounter, 200>;

// CH1 output drives red LED
using LEDR = Timer::AnyOutputChannel<Pwm
	, kRedCh
	, Timer::OutMode::kPWM2
	, Timer::Output::kInverted
	, Timer::Output::kDisabled
	, true
>;

// CH2 output drives green LED
using LEDG = Timer::AnyOutputChannel<Pwm
	, kGreenCh
	, Timer::OutMode::kPWM2
	, Timer::Output::kInverted
	, Timer::Output::kDisabled
	, true
>;

// CH3 output drives blue LED
using LEDB = Timer::AnyOutputChannel<Pwm
	, kGreenCh
	, Timer::OutMode::kPWM2
	, Timer::Output::kInverted
	, Timer::Output::kDisabled
	, true
>;


/*
This function is required by STM32 startup file and called during
initial startup.
*/
extern "C" void SystemInit()
{
	// Reset clock system before starting program
	System::Init();
	// Enable clocks for all peripherals used by this firmware (once at boot)
	PeripheralEnabler::Init();
	// Set up all GPIO ports in one shot
	AllGpioStartup::Setup();
	// Starts desired clock
	SysClk::Init();
	// Start tick counter
	Tick::Init();
	LEDR::Setup();
	LEDG::Setup();
	LEDB::Setup();
}



int main()
{
	// A 7 millisecond timer used to update LED status (auto-reload mode)
	Timer::MicroStopWatch<Tick, Tick::ToTicks(Timer::Msec(7))> t;

	// Up or down Sliders for R, G and B LEDs. 
	int r = 0;
	int rd = 1;
	int g = 0;
	int gd = 1;
	int b = 0;
	int bd = 1;

	// Starts the PWM, which runs continuously
	Pwm::CounterStart();
	
	// Display duration forever
	while (true)
	{
		// Apply individual active ratio
		LEDR::SetCompare((uint16_t)r);
		LEDG::SetCompare((uint16_t)g);
		LEDB::SetCompare((uint16_t)b);
		// Now wait until stopwatch overflows
		while (t.IsNotElapsed())
		{}
		// Controls each color slider. Slight different ranges will produce a multitude of colors
		r = r + rd;
		if (r >= 199 || r == 0)
			rd = -rd;
		g = g + gd;
		if (g >= 193 || g == 0)
			gd = -gd;
		b = b + bd;
		if (b >= 197 || b == 0)
			bd = -bd;
	}
	return 0;
}

