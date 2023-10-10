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

As first statement, the program includes the **bmt** library and a 
declaration for its namespace:

```cpp
#include <bmt.h>
using namespace Bmt;
```

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
- **``**:


