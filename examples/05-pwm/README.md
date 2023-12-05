# <big>`05-pwm` Example</big>

In this example we will setup the Timer 1 as a continuous counter and use 
3 output channels in PWM mode to control an RGB LED. Because of the form 
that we swipe each channel, we can produce a multitude of color 
combinations. 

This example repeats the wiring used in `04-timer-delay` example. 


## Bluepill Pinout

The wiring for the **Blue-pill** board is the following:

![bluepill.png](../04-timer-delay/images/bluepill.png)


## Nucleo32 L432KC Pinout

The wiring for the **Nucleo L432KC** board is the following:

![nucleo_l432kc.png](../04-timer-delay/images/nucleo_l432kc.png)


## Nucleo32 G431KB Pinout

The wiring for the **Nucleo G431** board is the following:

![nucleo-g431kb.png](../04-timer-delay/images/nucleo-g431kb.png)


# Technical Description

## Inclusion of the **bmt** library

As first statement, the program includes the **bmt** library and a 
declaration for its namespace:

```cpp
#include <bmt.h>
using namespace Bmt;
```

## Hardware Abstraction Layer

Then it switches the include file for the correct *hardware abstraction 
layer* include file, by checking the control macros provided by the build 
environment:

```cpp
#ifdef STM32F103xB
#	include "hal.f103.h"
#elif defined(STM32L432xx)
#	include "hal.l432.h"
#elif defined(STM32G431xx)
#	include "hal.g431.h"
#else
#	error Unsupported configuration
#endif
```

The *Hardware Abstraction Layer* has to provide basic data-types for the 
working of this example. The really important definitions are:
- **`SysClk`**: A data-type for the system clock tree.  
*Since all peripherals are connected to the clock tree, this is a type* 
*that needs to be shared among all other types.* 
- **`InitPA`**: This data-type provides the setup for the GPIOA used to 
initialize it.  
*Note hat pins used for the debug port needs to be carefully managed and* 
*requires the use of `Gpio::Unchanged<nn>` to ensure they are not* 
*modified. Without this the SWD link used by the debugger will stall.* 
- **`InitPB`**: This is the same as **`InitPA`**, but for the GPIOB port. 
- **`InitPC`**: This is the same as **`InitPA`**, but for the GPIOC port. 
- **`kPwmTim`**: Timer used to generate the PWM signals.
- **`kRedCh`**: Channel of `kPwmTim` timer used to drive the red LED. 
- **`kGreenCh`**: Channel of `kPwmTim` timer used to drive the green LED. 
- **`kBlueCh`**: Channel of `kPwmTim` timer used to drive the blue LED. 


## The System Tick Timer

To control timing, access to the System Tick Timer is granted by the 
**`Tick`** data-type:

```cpp
// The data-type representing the system tick timer
typedef Timer::SysTickCounter<SysClk> Tick;
```

> This data-type was covered in 
[02-systick-delay](../02-systick-delay/README.md) example. 


## Timer Base Frequency

To generate a base frequency for the PWM generation, we need to 
setup a clock for the timer: 

```cpp
// 40 KHz PWM base frequency using Timer 1
// This timer provides all 3 required outputs we need for this example
typedef Timer::InternalClock_Hz<kPwmTim, SysClk, 40000> PwmFreq;
// This divides base frequency by 200; also, the range we can control 
// LED brightness
typedef Timer::Any<PwmFreq, Timer::Mode::kUpCounter, 202> Pwm;
```

The **`PwmFreq`** data-type establishes a timer period calculator based 
in a constant specified in **Hz** and the **`Pwm`** data-type associates 
it to help initialize the timer with a clock frequency of **40 kHz**.  
This frequency counts in a loop up to 202 units. 
This value determines the resolution of the PWM, which grants variations 
of LED intensity in **0.5%** per step.


## Independent Output Channel

Each drive pin of the RGB LED will be controlled by one dedicated timer 
channel:

```cpp
// CH1 output drives red LED
typedef Timer::AnyOutputChannel<Pwm
	, kRedCh
	, Timer::OutMode::kPWM2
	, Timer::Output::kInverted
	, Timer::Output::kDisabled
	, true
> LEDR;

// CH2 output drives green LED
typedef Timer::AnyOutputChannel<Pwm
	, kGreenCh
	, Timer::OutMode::kPWM2
	, Timer::Output::kInverted
	, Timer::Output::kDisabled
	, true
> LEDG;

// CH3 output drives blue LED
typedef Timer::AnyOutputChannel<Pwm
	, kGreenCh
	, Timer::OutMode::kPWM2
	, Timer::Output::kInverted
	, Timer::Output::kDisabled
	, true
> LEDB;
```

Definitions are the same regardless of the channel. Note that timer 
output has many ways to determine the PWM polarity, thanks to the 
flexibility of the hardware. We could define a channel without modifying 
the end result, like the following:

```cpp
// CH1 output drives red LED
typedef Timer::AnyOutputChannel<Pwm
	, kRedCh
	, Timer::OutMode::kPWM1
	, Timer::Output::kEnabled
	, Timer::Output::kDisabled
	, true
> LEDR;
```


## Firmware Initialization

Every STM32 program requires a startup file as part of the program, which 
contains important system information like the default interrupt handlers 
and the reset vector handler.  
It could sound a bit too low level, but just think that all embedded 
hardware that your firmware wants to handle asynchronously, will do it 
through interrupts. This file contains all available options for your 
specific MCU model. 

As already mentioned one of the handlers is called *reset handler*. To 
understand how this works, when your MCU receives a reset signal from the 
hardware pin or any of the alternative sources, it generates an 
*interrupt* handled by the *reset handler*. This *reset handler* contains 
the address of your *firmware boot*. The code for this is also provided 
by the startup file, which prepares memory and other system related stuff 
to safely start your firmware. This *boot code* expects two functions 
from your side: the `SystemInit()` and the `main()` function.

For this firmware, the `SystemInit()`, which is used to put your embedded 
peripherals in a usable state, looks like:

```cpp
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
```

This is a simple sequential function, that performs the following steps: 
- Calls the `System::Init()` function which is provided by the **bmt** 
library and responsible to clear clock circuits and other core 
initialization.
- Initialize the all GPIO pins, through `InitPA::Init()`, 
`InitPB::Init()` and `InitPC::Init()` calls.
- Calls `SysClk::Init()` to start the system clock tree to run on the 
desired MCU frequency. 
- Starts the system tick timer, by calling `Tick::Init()`. 
- Initialize the PWM timer by calling `LEDR::Init()`. 
- Note the important detail here: Since all timer channels share the same 
timer count unit, the other channels have only be setup, by calling 
`LEDG::Setup()` and `LEDB::Setup()`. 

> Note that all this *functions* were declared as `inline`. This means 
that the produced binary code is very compact and optimized. 


## The `main()` Funtion

After the initialization of the hardware, the static variables and static 
constructors (for C++ programs), the `main()` function is started, which 
is the entry point of our program.

This topic describes in details every step of the program.


### The Soft Timer for LED Update Rate

One of the requirements is to update LEDs at a reasonable rate and 
produce a multitude of color patterns: 

```cpp
	// A 7 millisecond timer used to update LED state 
	// (timer in auto-reload mode)
	Timer::MicroStopWatch<
		Tick
		, Tick::ToTicks(Timer::Msec(7))
		> t;
```

In this setup, we take the hardware tick counter as a precise time base 
to update a software counter and obtain updates at a 7ms rate. 


### Up and Down Sliders

A slider is specified for each LED. it consists on a counter that moves 
between 0 and a top value. And when it arrives the top value it changes 
the direction and starts to decrement until it reaches 0 again. THen the 
cycle restarts.

The top value is slightly different for each LED color. A prime number, 
near the timer overflow value was selected for each channel. This tends 
to reduce the chances that a pattern repeats in the timeline.

For each color slider we establish two variables: a **counter** and a 
**direction control value**, according to the table:

| LED   | Counter | Direction |
|:-----:|:-------:|:---------:|
| Red   |    r    |    rd     |
| Green |    g    |    gd     |
| Blue  |    b    |    bd     |


Slider are initialized once at the start of the program. The code below 
shows the implementation for the Red LED, since the others follow similar 
pattern: 

```cpp
	// Up or down Sliders for R, G and B LEDs. 
	int r = 0;
	int rd = 1;
```

Later, 

