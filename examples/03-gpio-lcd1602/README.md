# <big>`03-gpio-lcd1602` Example</big>

The purpose of this example is to demonstrate the Lcd1602 class provided 
as an accessory on the **kits** folder.


## General schematics

The following pictures illustrates the schematics depending on your MCU 
type. 


### STM32F103 BluePill

This connection diagram shows how to interface a BluePill with a standard 
LCD1602:

![sch.f103.svg](sch.f103.svg)


### Nucleo-L432KC

Very similar to the BluePill, this is the schematics for this setup:

![sch.l432.svg](sch.l432.svg)


### Nucleo-G431KB

Although this board is very similar to the Nucleo-L432KC, the PA3 is not 
connected by default. So for this example to work, PA0 replaces the PA3 
function.

> For all examples of this toolkit, the 24 MHz crystal is used as 
> default clock. For this to work, you should ensure the solder bridges 
> **SB9** and **SB10** are closed.

![sch.g431.svg](sch.g431.svg)

It is recommended to take a look at the implementation of this class to 
check how fine timing synchronization of faster CPU is made to access 
slower hardware


## Include File

The `LCD1602.h` provided in the kit folder is not included by default 
when you include the `<bmt.h>` header file.

So provide the required include file, like the example:

```cpp
#include <bmt.h>
#include <kits/lcd1602.h>	// required for the LCD1602 display class

// Declare namespaces to reduce verbosity of the source code
using namespace Bmt;
using namespace Bmt::Kits::Lcd1602;
```


## Data-Types for the Display

Like all previous examples a clock tree is necessary, which is 
conventionally called `SysClk`. Also GPIO is required. All these types 
can be found on each *`hal.xxx.h`* file, which depends solely on your 
MCU type:

```cpp
#ifdef STM32F103xB
#   include "hal.f103.h"
#elif defined(STM32L432xx)
#   include "hal.l432.h"
#elif defined(STM32G431xx)
#   include "hal.g431.h"
#else
#   error Unsupported configuration
#endif
```

For example, in the *BluePill* the `"hal.f103.h"` file is loaded, and the 
following types are defined:

| Data type | Usage                                                   |
|-----------|---------------------------------------------------------|
| `Hse`     | Manages the 8MHz externally mounted crystal             |
| `SysClk`  | Manages the clock tree sourcing all hardware buses.     |
| `InitPA`  | State of Port A for initialization.                     |
| `InitPB`  | State of Port B for initialization.                     |
| `InitPC`  | State of Port C for initialization.                     |
| `Led`     | The LED mounted on this board (not used in this sample) |
| `Delay`   | Class with utilities that produces short delays         |
| `Tick`    | Class for longer delays                                 |
| `Lcd`     | Data-type that drives the LCD1602 hardware              |

> Other *HAL* files have similar contents.

For details on the clock tree you should check example **1)** and **2)**. 

This example will cover the GPIO and the some details on how to produce 
short delays to synchronize with hardware that is slower than your CPU.  
These details will be covered later.



## Initialization

By STM32 convention, the `SystemInit()` is used to initialize the system 
clock. This happens before the C/C++ library has a chance to initialize 
itself, which means that **no object or variable can be used at this 
point**. 

Since all our hardware elements are also initialized using static 
functions, we break this convention and add also other initialization 
code:


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
}
```

> Note that the LCD class requires an object instance, so we cannot do 
> this now. This object is initialized later on the `main()` function.


# General Description of the Example Functionality

This example does the following:
- Creates an instance of the PolledStopWatch<> class
- Creates an instance of the LCD1602 class and initialize it.
