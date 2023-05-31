#include <bmt.h>
#include <kits/lcd1602.h>
#include <stdlib.h>

using namespace Bmt;
using namespace Bmt::Kits::Lcd1602;

#ifdef STM32F103xB
#	include "hal.f103.h"
#elif defined(STM32L432xx)
#	include "hal.l432.h"
#elif defined(STM32G431xx)
#	include "hal.g431.h"
#else
#	error Unsupported configuration
#endif


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
	// Start tick counter
	Tick::Init();
	LEDR::Init();
	LEDG::Setup();
	LEDB::Setup();
}



int main()
{
	// A 100 millisecond timer used to update current time (auto-reload mode)
	Timer::MicroStopWatch<Tick, Tick::ToTicks(Timer::Msec(7))> t;

	int r = 0;
	int rd = 1;
	int g = 0;
	int gd = 1;
	int b = 0;
	int bd = 1;

	Pwm::CounterStart();
	
	// Display duration forever
	while (true)
	{
		LEDR::SetCompare(r);
		LEDG::SetCompare(g);
		LEDB::SetCompare(b);
		// Now wait until stopwatch overflows
		while (t.IsNotElapsed())
		{}
		__NOP();
		r = r + rd;
		if (r > 199 || r == 0)
			rd = -rd;
		g = g + gd;
		if (g > 193 || g == 0)
			gd = -gd;
		b = b + bd;
		if (b > 197 || b == 0)
			bd = -bd;
	}
	return 0;
}

