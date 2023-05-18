#include <bmt.h>

using namespace Bmt;

#ifdef STM32F103xB
#	include "hal.f103.h"
#elif defined(STM32L432xx)
#	include "hal.l432.h"
#elif defined(STM32G431xx)
#	include "hal.g431.h"
#else
#error Unsupported configuration
#endif


// The data-type representing the system tick timer
typedef Timer::SysTickCounter<SysClk> Tick;


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
	// Start tick counter
	Tick::Init();
}

// List of supported example types
enum class ExampleType
{
	kSimple,	// Simple delay block to blink LED on a controlled period
	kAdvanced,	// Allows other activities while waiting foi period elapse
	kVeryLong,	// Example for very long durations, compensating timer overflows
};

// Please select one of the example type
static constexpr ExampleType kExample = ExampleType::kSimple;


/*
This is the most generic use of a delay
*/
void SimpleUse()
{
	while (true)
	{
		// The following line attaches a temporary PolledStopWatch<> instance 
		// to the 'Tick'  timer, initializes with 350 ms and halts CPU until 
		// time has elapsed. This establishes a 700 ms LED period.
		Timer::PolledStopWatch<Tick>(350).Wait();
		// Toggle the LED
		Led::Toggle();
	}
}


/*
This is a use case that is usually more useful, since you can do something while
your time has not elapsed.
*/
void AdvancedUse()
{
	while (true)
	{
		// Attaches the 'Tick' timer to the 'stopwatch' instance and initializes 
		// it with 350 ms. 
		Timer::PolledStopWatch<Tick> stopwatch(350);
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
timer overflow period.
*/
void UseOfLongPeriods()
{
	while (true)
	{
		// 60 seconds delay
		Timer::PolledStopWatch<Tick> stopwatch(60000UL);
		while (stopwatch.IsNotElapsed())
		{
			// TODO: Do other stuff while waiting for the period to update LED
			__NOP();
		}
		// Toggle the LED every minute
		Led::Toggle();
	}
}


int main()
{
	// Hey don't trick me!!!
	static_assert(kExample >= ExampleType::kSimple
		&& kExample <= ExampleType::kVeryLong
		, "Invalid example was selected");

	if (kExample == ExampleType::kSimple)
		SimpleUse();
	else if (kExample == ExampleType::kAdvanced)
		AdvancedUse();
	else
		UseOfLongPeriods();
	return 0;
}

