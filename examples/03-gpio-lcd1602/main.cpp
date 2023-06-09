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
}


/*
This function writes a decimal value to the display.
It inserts a decimal place to the value as a bogus
floating point value.
The value occupies the entire second line.
*/
void WriteElapsedTime(Lcd &lcd, unsigned int v)
{
	char buf[16];

	// Position on second line of the display
	lcd.SetCursorPos(0, 1);
	size_t l = 0;
	// Values below 10 are special: prepend '0' for fake floating point
	if (v < 10)
	{
		// Produces "0.0", "0.1", ..., "0.9"
		buf[0] = '0';
		buf[1] = '.';
		buf[2] = (char)('0' + v);
		buf[3] = 0;
		l = 3;	// length of the printable string
	}
	else
	{
		// Format counter to decimal value
		__utoa(v, buf, 10);
		// Move last digit one position away
		l = strlen(buf);
		buf[l] = buf[l - 1];
		// insert decimal dot
		buf[l - 1] = '.';
		// Update string size and add terminator
		buf[++l] = 0;
	}
	// Compute padding required for move text to the right margin
	l = 14 - l;
	// prepend spaces
	while (l--)
		lcd.Write(' ');
	// Write string with current time
	lcd.Write(buf);
	// Add time unit
	lcd.Write(' ');
	lcd.Write('s');
}


int main()
{
	// A 100 millisecond timer used to update current time (auto-reload mode)
	Timer::MicroStopWatch<Tick, Tick::ToTicks(Timer::Msec(100))> t;
	
	// Instance of the LCD1602
	Lcd lcd;
	// Initialize LCD controller
	lcd.InitLcd();
	// Write static text on the first line
	lcd.Write("Hello World!");
	unsigned int v = 0;
	// Display duration forever
	while (true)
	{
		// Update second line
		WriteElapsedTime(lcd, v);
		// Now wait until stopwatch overflows
		while (t.IsNotElapsed())
			lcd.IsLocked();	// 'ping' internal timer
		// Increment 100 ms counter
		++v;
	}
	return 0;
}

