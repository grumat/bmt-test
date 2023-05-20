# <big>`03-gpio-lcd1602` Example</big>

The purpose of this example is to demonstrate the timing control using 
the SYSTICK timer.

In the example a simple 350 ms delay is used. The SYSTICK timer can be 
used to measure timing but depends totally on clock speed.  

The advantage of using the SYSTICK timer is that you won't waste other 
timer which has far more features that the tick counter, just to produces 
simple delays or time measures.

For lower CPU clocks very long delays are possible. But the `Delay()` 
method is able to overcome the 24-bit limitation of the timer in case 
a very long delay is needed and the SYSCLK is very high.

![sch.f103.svg](sch.f103.svg)

![sch.l432.svg](sch.l432.svg)

![sch.g431.svg](sch.g431.svg)

## Type Declaration

The **bmt** library allow the use of the **SysTick** in two different 
modes: 
- As a simple timer and the `Timer::SysTickCounter` class with methods 
using polling algorithms
- As a interrupt timer and the `Timer::AnySysTick` or 
`Timer::AnySysTickEx` classes which allows a lower timer resolution, but 
ideal for a collaborative share of the timer functions.

This example covers the first scenario, which is easier from a 
programmatic point of view.

O use the `Timer::SysTickCounter` class, simply declare like this:
```cpp
// The data-type representing the system tick timer
typedef Timer::SysTickCounter<SysClk> Tick;
```

The template parameter is the data-type for your clock tree, as seen on 
the previous example. This data-type is required ro that the operating 
frequency of the SysTick can be obtained from the clock tree. This 
affects the internal calculators used to compute the amount of ticks 
required for a desired interval.

Note that if you change the frequency of your your clock tree, the timer 
logic will be updated during next compilation and everything will work 
instantly with the new settings. 


## Initialization

To initialize the **SysTick** simply add the `Init()` method to the 
`SystemInit()` function.

```cpp
// Start tick counter
Tick::Init();
```

# Available Experiments

The example project contains three different tests that is controlled by 
the `kExample` constant.

For example, to Test the *Very Long Period* test use:

```cpp
// Please select one of the example type
static constexpr ExampleType kExample = ExampleType::kVeryLong;
```

The next topics describes each case.

## 1) Simple Polling Loop

The example implements a simple polling loop to toggle the LED:

```cpp
/*
This is the most generic use of a delay
*/
void SimpleUse()
{
	while (true)
	{
		// A 350ms delay for each phase (LED blinks in a 700 ms blink rate)
		Tick::StopWatch().Delay<350>();
		// Toggle the LED
		Led::Toggle();
	}
}
```

The example demonstrates the `Delay<C>()` method of the tick timer, which 
halts CPU for the given period.

A **absolutely important** concept that should be observed in this class 
is that the `Delay()` method has two forms: A template form and a regular 
method that has exactly the same effect. 

This would be the rewritten example, if we use the non-template version:

```cpp
/*
This is the most generic use of a delay
*/
void SimpleUse()
{
	while (true)
	{
		// Use of the non-template Delay() method:
		Tick::StopWatch().Delay(350);
		// Toggle the LED
		Led::Toggle();
	}
}
```

The crucial difference is that if the programmer knows in advance the 
duration of the period (**a constant**), then the *template version* 
shall be used to provide quite better code. The reason is that the 
template version uses a calculator to compute the total timer ticks 
necessary for the delay and produces inline code for the delay.

> The *non-template version* is appropriate for variable delays.


## 2) A More Useful Use Case

In general, when handling timing events in a complex firmware, some 
parallel operations are also needed. So, for this case a more useful 
approach can be used, like in the following example:

```cpp
/*
This is a use case that is usually more useful, since you can do something while
your time has not elapsed.
*/
void AdvancedUse()
{
	while (true)
	{
		Tick::StopWatch stopwatch;
		while (stopwatch.GetElapsedTicks() < Tick::M2T<250>::kTicks)
		{
			// TODO: Do other stuff while waiting for the period to update LED
		}
		// Toggle the LED
		Led::Toggle();
	}
}
```

### Issue with High MCU Clocks

What is important when using the tick timer in the configuration of this 
example, is that MCU in higher clock rates have a severe limitation on 
the maximal interval measured. For example, on a **STM32G4xx** running at 
**150 MHz** the timer overflows after **895 ms**.

So it is unpractical to use the tick timer for long periods, specially in 
an environment where interrupts occurs: imagine a 150 MHz MCU and a delay 
with **890 ms**, which is theoretically still safe inside the total timer 
duration. If an interrupt occurs which could lock out the test loop for 
more than **5 ms**, an overflow would happen and another **890 ms** delay 
cycle would start, doubling the interval.


## 3) The `PolledStopWatch` class

For this scenario the `PolledStopWatch` class is the solution. This is an 
example:

```cpp
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
		Tick::PolledStopWatch stopwatch(60000UL);
		while (stopwatch.IsNotElapsed())
		{
			// TODO: Do other stuff while waiting for the period to update LED
		}
		// Toggle the LED every minute
		Led::Toggle();
	}
}
```

# Exercise Proposals

Below follows some interesting exercise to be done.


## 1) Verification of the Precision

Connect a frequency counter or oscilloscope and change timer period. 
Check in the measurement device how precise can be this intervals.


## 2) Microseconds resolution

Similar as previous exercise, try the `DelayUS()` method for very short 
periods. 

Note that this is an important feature when manipulating hardware devices 
that imposes latencies for correct access, like a display.


## 3) Two Instances with Different Time Bases

Select any desired GPIO and configure it as output. Connect a LED or 
measurement device.

Make two instances of `PolledStopWatch` with different duration and modify 
the logic so that each instance toggles a different output.

For this exercise you will need to *continue* each instance after the 
toggle. For this use the `PolledStopWatch::Continue()` method.

Important to note here is that the design of `PolledStopWatch::Continue()` 
does not resets the time base, as opposed to `PolledStopWatch::Restart()`, 
which means that no accumulated time shift error will happen when you 
continually *continues* the instance.

If one uses `PolledStopWatch::Restart()` a new time reference is sampled, 
which means that any latencies will shift the time slightly increasing 
the period. This is critical in a timer that runs in several MHz and a 
cyclic phenomenon.


## 4) New Clock Frequencies

Modify your clock chain and activate the PLL as system clock. You can 
experiment any supported PLL frequency.

Here you should check that the timer logic will not be changed because of
clock changes, meaning that the final code is very portable. 
A simple compilation with new parameters will make the compiler 
recalculate all timer periods and no sensible deviations will be noticed. 


