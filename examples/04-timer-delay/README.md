# <big>`04-timer-delay` Example</big>

This example repeats example `02-systick-delay`, but it demonstrates that 
the regular timer classes serves also as time base for the polling 
classes. This makes them more flexible, and a single programming 
interface is accomplished.

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
the System Tick Timer. They are designed for motor control, Rotary 
encoder decoding, PWM and many other possibilities, but lack in counter 
resolution. Except for most recent models, timer units uses always 16-bit 
counters and the system tick timer, in the other side, features a 24-bit 
counter.

But chances are that you are using a timer unit for any required feature 
and sometimes you have to control elapsed time, so, coupling polling 
software timers to them makes sense.

The example project shows the typical use case:

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
we covered in the `02-systick-delay` example.

