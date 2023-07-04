# <big>`04-timer-delay` Example</big>

This example repeats example `02-systick-delay`, but it demonstrates that 
the regular timer classes serves also as time base for the polling 
classes. A consistent interface between system tick and regular timer, 
makes development more flexible, and a single programming interface is 
accomplished.

One exception is the first test mode, which presents the 
`Timer::AnyTimerDelay<>` template class.

So, please refer to the `02-systick-delay` example before checking this 
one out, for the sake of a detailed coverage of all use cases.


# The `Timer::AnyTimerDelay<>` Template Class

This is the type definition for this class:

```cpp
// Computes the prescaler for 1 kHz counter speed
typedef InternalClock_Hz <kTim1, SysClk, 1000UL> Millisec;
// Simple Delay using a timer as time base
typedef Timer::AnyTimerDelay<Millisec> Delay;
```

The two lines above shows:
- A time-base for the TIM1:
  - Use the internal system clock
  - Instance `InternalClock_Hz` computes a value in Hz, which is given on 
  the last template argument.
  - 1000 Hz, or 1kHz, if you prefer.
- A timer class specialization to produce delays. This class just 
requires the template parameter specifying the type of clock. Depending 
on your design it is possible to specify one of the following time-base 
templates:
  - `InternalClock_us`: Internal clock using microseconds as time unit.
  - `InternalClock_Hz`: Internal clock using Hertz as time unit.
  - `ExternalClock`: External clock, where you provide the working 
  frequency. 

The template initializes the timer hardware by calling: 

```cpp
// initialize TIM1 hardware
Delay::Init();
```

And CPU can be halted for a any desired timer count value, commanding: 

```cpp
/// Halts the CPU for 350ms
Delay::Delay(350);
```


# Using a Timer as Time Base for Polling Classes

As already told, this example substitutes the system tick timer by a 
regular timer unit. Timer units are far more complex and powerful than 
the System Tick Timer. They are designed for motor control, rotary 
encoder decoding, PWM and many other possibilities, but generally lack in 
counter resolution.

> Except for most recent models, timer units uses always 16-bit counters 
> and the system tick timer, in the other side, features a 24-bit 
> counter. 

But in the case you are using a timer unit for any required feature 
you can also use them to control elapsed time. Like in the SysTick 
example, you just couple a *polled software timer* and you can control 
elapsed time.

The example project demonstrates a the typical use case:

```cpp
// Computes the prescaler for 1 MHz counter speed
typedef InternalClock_Hz <kTim1, SysClk, 1000000UL> Microsec;
// Timer that overflows every 5 ms (200Hz) [note: count is 0-base]
typedef Timer::Any<Microsec, Mode::kUpCounter, 5000UL-1UL> FiveMs;
// This is the model that expands resolution of the Tick counter to 32-bit, 
// but requires moderate polling rates
typedef MicroStopWatch<FiveMs> Tick32;
// This is the model with more capabilities
typedef PolledStopWatch<FiveMs> StopWatch;
```

First we establish an internal clock of 1 MHz (1 µs) for **TIM1**. The 
second line is the data-type for the timer itself, where we establish an 
*up-counter* for 5000 steps, which corresponds to 5 ms (i.e. 200 Hz).

Both, the `MicroStopWatch<>` and the `PolledStopWatch<>` templates 
attaches the same way as with the system tick timer, very similar to what 
we covered in the **`02-systick-delay` example**.


# A Brief Description of the Experiment Type

The `ExampleType` enumeration defines all **four** experiment types:

```cpp
// List of supported example types
enum class ExampleType
{
	kSimple,		// Simple delay block to blink LED on a controlled period
	kUsePolling,	// Use polling classes
	kVeryLong,		// Example for very long durations, compensating timer overflows
	kRGB,			// Test RGB LED on PA5, PA6, PA7
	kLast_
};
```

## Experiment 1: **`kSimple`**

This example demonstrates the use of the `Timer::AnyTimerDelay<>` 
dedicated timer template class to produce delays using any timer. This 
class use the timer for this purpose only, programming the timer as a 
single shot counter, meaning, no other timer feature are expected to be 
used.

### Setup and Compilation

To select this experiment, please recompile the project with:
 
```cpp
// Please select one of the example type
static constexpr ExampleType kExample = ExampleType::kSimple;
```

### Tested Functionality

To activate the delay a simple command is required, like:

```cpp
Delay::Delay(350);
```


## Experiment 2: **`kUsePolling`**

In this example the timer `FiveMs` is started and left running free. An 
instance of `MicroStopWatch<>`, called `stopwatch` is used to poll the 
hardware timer.
The poll consists in calls to `stopwatch.IsNotElapsed()`, which updates 
internal software timer and indicates when the interval has elapsed.

### Setup and Compilation

To select this experiment, please recompile the project with:

```cpp
// Please select one of the example type
static constexpr ExampleType kExample = ExampleType::kUsePolling;
```

### Tested Functionality

In this experiment you can perform other necessary tasks using the CPU
while regularly checking for elapsed time. In the first experiment CPU
is completely locked while the time does not elapses, and in this 
experiment controls enters the loop block where you have the opportunity 
to code more CPU functionality in the time interval.

This is the core of the delay routine:

```cpp
Tick32 stopwatch(Msec(350));
while (stopwatch.IsNotElapsed())
{
	// TODO: Add functionality while waiting for the programmed period
	__NOP();
}
```


## Experiment 3: **`kVeryLong`**

Like covered on the `02-systick-delay` example, this experiment 
illustrates the use of `PolledStopWatch<>` template class, which 
incorporates more complexity than `MicroStopWatch<>` and allows for 
longer periods. The first is ideal for short periods and the later for 
very long periods. 

### Setup and Compilation

To select this experiment, please recompile the project with:

```cpp
// Please select one of the example type
static constexpr ExampleType kExample = ExampleType::kVeryLong;
```

### Tested Functionality

The example show a 60 seconds delay, which will work also on very high 
timer frequencies, as long as the polling interval occurs before the 
timer overflows.

Code structure works exactly like the previous experiment:
```cpp
// 60 seconds delay
StopWatch stopwatch(Msec(60000UL));
while (stopwatch.IsNotElapsed())
{
	// TODO: Add functionality while waiting for the programmed period
	__NOP();
}
```

> Note that the programmed interval uses milliseconds and has a 32-bit
> resolution, which means you can program delay as long as **2^32 ms**. 


## Experiment 4: **`kRGB`**

Exactly like covered `02-systick-delay` example, but using three 
`MicroStopWatch<>` instances.

### Setup and Compilation

To select this experiment, please recompile the project with:

```cpp
// Please select one of the example type
static constexpr ExampleType kExample = ExampleType::kRGB;
```

### Tested Functionality

Please refer to the `02-systick-delay` example.