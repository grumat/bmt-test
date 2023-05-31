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

// Computes the prescaler for 1 kHz counter speed
typedef InternalClock_Hz <kTim4, SysClk, 1000UL> Millisec;
// Simple Delay using a timer as time base
typedef AnyTimerDelay<Millisec> Delay;
// Computes the prescaler for 1 MHz counter speed
typedef InternalClock_Hz <kTim4, SysClk, 1000000UL> Microsec;
// Timer that overflows every 5 ms (200Hz) [note: count is 0-base]
typedef AnyTimer<Microsec, Mode::kUpCounter, 5000UL-1UL> FiveMs;
// This is the model that expands resolution of the Tick counter to 32-bit, 
// but requires moderate polling rates
typedef MicroStopWatch<FiveMs> Tick32;
// This is the model with more capabilities
typedef PolledStopWatch<FiveMs> StopWatch;
#if 0
// The data-type representing the system tick timer
typedef SysTickCounter<SysClk> Tick;
#endif

/*
This function is required by STM32 startup file and called during
initial startup.
*/
extern "C" void SystemInit()
{
	__NOP();
	// Reset clock system before starting program
	System::Init();
	// Initialize Port A, B and C
	InitPA::Init();
	InitPB::Init();
	InitPC::Init();
	// Starts desired clock
	SysClk::Init();
	__NOP();
}

// List of supported example types
enum class ExampleType
{
	kSimple,		// Simple delay block to blink LED on a controlled period
	kUsePolling,	// Use polling classes
	kVeryLong,		// Example for very long durations, compensating timer overflows
	kRGB,			// Test RGB LED on PA5, PA6, PA7
	kLast_
};

// Please select one of the example type
static constexpr ExampleType kExample = ExampleType::kRGB;


/*
This is the most generic use of a delay
*/
void SimpleUse()
{
	// initialize TIM4 hardware
	Delay::Init();
	while (true)
	{
		// In this timer we use a timer (TIM4 for STM32F103) programmed to 
		// update every ms. The AnyTimerDelay<> template class uses the 
		// counter to create a delay solely based on the programmed timebase
		// of the timer.
		Delay::Delay(350);
		// Toggle the LED
		Led::Toggle();
	}
}


/*
This is a use case that is usually more useful, since you can do something while
your time has not elapsed. Besides, as long as a moderate polling rate is granted 
the MicroStopWatch<>() instance expands the resolution to 32-bit values.
*/
void AdvancedUse()
{
	// This timer updates every 5ms and is used here as timebase for the polling 
	// classes already presented on 02-systick-delay example
	// Usually systick is the way to go, but in this example you establish a timer for 
	// any other purpose and it can also serve as timebase for polling classes.
	FiveMs::Init();
	FiveMs::CounterStart();
	while (true)
	{
		// Attaches the 'Tick' timer to the 'stopwatch' instance and initializes 
		// it with 350 ms. 
		Tick32 stopwatch(Msec(350));
		// A loop is established until this period elapses to perform any required 
		// activity.
		while (stopwatch.IsNotElapsed())
		{
			// TODO: Do other stuff while waiting for the period to update LED
			__NOP();
		}
		// Toggle the LED
		Led::Toggle();
	}
}

/*
This example illustrates the use of PolledStopWatch, which supports a very 
long interval, as long as IsNotElapsed() method is called within the 
timer overflow period. Though, this model is limited to milliseconds resolution.
*/
void UseOfLongPeriods()
{
	FiveMs::Init();
	FiveMs::CounterStart();
	while (true)
	{
		// 60 seconds delay
		StopWatch stopwatch(Msec(60000UL));
		while (stopwatch.IsNotElapsed())
		{
			// TODO: Do other stuff while waiting for the period to update LED
			__NOP();
		}
		// Toggle the LED every minute
		Led::Toggle();
	}
}


/*
This example illustrates an additional feature of the MicroStopWatch<> class.
A second template parameter can be defined to establish a constant auto-reload 
feature.
This example requires an RGB LED on the PA5, PA6 and PA7 pins.
*/
void TestRGB()
{
	// Establish intervals using prime numbers to establish a reasonable random 
	// behavior of the LED.
	MicroStopWatch<FiveMs, FiveMs::ToTicks(Msec(607))> stopwatch_r;
	MicroStopWatch<FiveMs, FiveMs::ToTicks(Msec(601))> stopwatch_g;
	MicroStopWatch<FiveMs, FiveMs::ToTicks(Msec(613))> stopwatch_b;

	FiveMs::Init();
	FiveMs::CounterStart();
	// Loop until something changes
	while (true)
	{
		if (!stopwatch_r.IsNotElapsed())
			LedR::Toggle();	// toggle R LED (timer will auto-reload)
		if (!stopwatch_g.IsNotElapsed())
			LedG::Toggle();	// toggle G LED (timer will auto-reload)
		if (!stopwatch_b.IsNotElapsed())
			LedB::Toggle();	// toggle B LED (timer will auto-reload)
	}
}


int main()
{
	// Hey don't trick me!!!
	static_assert(kExample >= ExampleType::kSimple
		&& kExample < ExampleType::kLast_
		, "Invalid example was selected");

	if (kExample == ExampleType::kSimple)
		SimpleUse();
	else if (kExample == ExampleType::kUsePolling)
		AdvancedUse();
	else if (kExample == ExampleType::kVeryLong)
		UseOfLongPeriods();
	else //if (kExample == ExampleType::kRGB)
		TestRGB();
	return 0;
}

