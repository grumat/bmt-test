# <big>`01-clock-tree` Example</big>

The purpose of this example is to demonstrate the clock tree setup of a 
STM32xxxx MCU using the **bmt template library**. It also demonstrates 
the use of the GPIO.

# Template Library Concepts

Since the library is template based development concept is quite 
different than a regular C program: Your firmware specification has to be 
translated to data-types, which in most cases are internally translated 
to raw constants known to the compiler.

By calling `Init()` or `Setup()` a minimal set of instructions are used 
to apply your model (i.e. specification) into the hardware registers.
This approach has the advantage that you are working with data-models 
in a more abstract way. And the template definition follows the hierarchy 
of your hardware.

For example, in the STM32L432KC, the MSI clock may benefit of the LSE 
clock to produce an accurate frequency, correcting the RC frequency (MSI) 
with the LSE frequency (a tiny and cheap 32768 XTAL). And this MSI clock 
can be used as input to the PLL to generate the system clock at very high 
frequencies.

This makes a dependency implemented on hardware: The Clock Tree depend on 
the PLL, which depends on MSI, which depends on LSE.

A similar dependency will be represented using template data-types like 
below: 

```cpp
// A data-type for the 48 MHz MSI clock
typedef Clocks::AnyMsi<
    Clocks::MsiFreq::k48_MHz    // Change STM32L432KC internal oscillator from 4 MHz 
                                // to 48MHz (good for USB)
    , true                      // Nucleo32 has an 32768 LSE Xtal that we will use 
                                // for accurate MSI frequency
> Msi;
// Configure the PLL for 80 MHz
typedef Clocks::AnyPll<
	Msi								// link to 48MHz MSI clock
	, 80000000UL					// Max is 80 MHz
	, Clocks::AutoRange1			// Full voltage range calculator
> Pll;
// A data-type for the clock tree
typedef Clocks::AnySycClk <
	Pll,							// uses PLL for the clock tree
	Power::Mode::kRange1			// Full Voltage for Max performance
> SysClk;

extern "C" void SystemInit()
{
	// Reset clock system before starting program
	System::Init();

	// ... initialize other stuff ...

	// Start the 80 MHz clock
	SysClk::Init();

	// ... more stuff to initialize...
}
```

> Note that on the exampl LSE data-type is not declared, since this is 
> the single possibility avalable when setting the flag to '`true`' and 
> the library will embed the LSE instance.

Note that a single call to `SysClk::Init()` will apply your clock setup 
according to your data model.

And another interesting advantage: If your firmware contains two 
different performance setup, say for example a full speed and a low power 
model, you can define a second data-type model for your clock setup and 
apply them individually whenever required.

Another interesting advantage of this approach occurs when you change 
specifications (and specs always change in the modern world), you just 
enter a new value and the changes propagates following the data-type 
links.

For example, lets say you decide to operate the MSI clock at 8 MHz 
instead of the 48Mhz shown in the example, just change the value on 
the first definition and changes will propagate:

```cpp
// A data-type for the 8 MHz MSI clock
typedef Clocks::AnyMsi<
    Clocks::MsiFreq::k8_MHz     // Change STM32L432KC internal oscillator from 4MHz 
                                // to 8MHz
    , true                      // Nucleo32 has an 32768 LSE Xtal that we will use 
                                // for accurate MSI frequency
> Msi;

// ... propagates to dependants ...
```

> What is important here, PLL M, N and R factors are automatically 
> updated to cope with new input clock.

If you don't want to use the PLL and use MSI directly as source clock for 
your clock tree, the change would be as simple as:

```cpp
// ...

// A data-type for the clock tree
typedef Clocks::AnySycClk <
	Msi,							// uses MSI for the clock tree
	Power::Mode::kRange1			// Full Voltage for Max performance
> SysClk;

// ...
```


# The Example Project

Compile the desired target and run. You will need a frequency counter/meter 
for this experiment.

The example models a System clock and GPIO pins to read frequency on the 
**MCO output pin**. The MCO output pin is conventionally on the **PA8** 
pin.


## BluePill (STM32F103C8)

For the BluePill, connect your frequency counter/meter on the pins 
highlighted on the following picture:

![bluepill-fs8.png](images/bluepill-fs8.png)

The frequency measured should be 36 MHz.


### Optional Excercises

As an excercise, the following is suggested:
- Use HSE as system clock, results 8 MHz. LED blink will be notably 
slower.
- Use other PLL frequencies. This chip is not so flexible but steps 
around 8MHz are feasible.
- Use HSI as system clock, which oscillates around 8 MHz. In this option 
it should be noticed how accuracy is affected when compared to crystal 
options.


## Nucleo32 L432KC (STM32L432KC)

For the Nucleo32 L432KC the frequency counter has to be connected on the 
folowing highlighted pins:

![nucleo_l432kc-fs8.png](images/nucleo_l432kc-fs8.png)


### Optional Excercises

As an excercise, the following is suggested:
- Try other MSI base frequencies and verify that the PLL output frequency 
keeps unchanged, since the `Clocks::AutoRange1` calculator compute new 
values at compile time.
- Still keeping the PLL as system clock select MSI as output for the MCO 
pin.
- Use HSI instead of the PLL. In this particular case, MSI seems to be 
more accurate without the PLL circuit. Compare with previous test.
- Experiment other MCO divisors.
- Use MSI as system clock without attaching to LSE clock. In this case
occurs a noticeable accurary loss.
- Still using MSI check other working frequencies.
- In this chip HSI16 is also an option. Establish a data-type for it and 
set it as main clock.

