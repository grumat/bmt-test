# <big>`06-dma-pwm` Example</big>

This example shows an implementation of an ECG simulator using DMA an 
PWM.  
The implementation uses two timers for the generation of the ECG signal. One for the PWM and the other provides timely samples, through a DMA trigger.

In the next topics we discuss implementation details.


# ECG Samples

A table having ordered samples of a complete ECG cycle is provided in the 
**main.cpp** file. It is declared as the **`s_EcgTable`** constant array 
and it contains all samples in absolute offset values, which means that a 
value of 127 you have the baseline of the EEG complex. Value above this 
reference are positive and all other values are negative.

The table contains a minimal representation of an ECG, where the Heart 
muscle has any kind of electrical activity. This means that between two 
heart beats there is no activity and a iso-electric line is left running 
(i.e. PWM ratio is left unchanged).


# Timer to generate PWM

The **Channel 1** of **TIM1** is used to produce the PWM signal. It is 
clocked at a high frequency (1 MHz) and has 256 counter steps for each 
cycle. Not incidentally, this step count provides conversion of a byte 
value to the respective PWM ratio. 

So, a byte value of 0 will produce no output, while the value of 255 
produces the maximal output. The byte value shall be written to the 
**CCR1** (*Capture Compare Register*) register of **TIM1** and a new 
ratio takes effect. 

![PWM Ratio](https://www.realdigital.org/img/e939633b0c24c828604904c4a20ea7df.svg)

> Source: [Real Digital](https://www.realdigital.org/doc/6136c69c3acc4bf52bc2653a067e36cc)

The timer is programmed to use shadow registers, which means that values 
that are written to the registers are not applied instantly. They are 
stored in a cache register and only when the timer updates they are 
copied to the actual register. This has the advantage that samples can 
be provided asynchronously to the **TIM1** period. 


# Sample Rate Timer

In this example **TIM2** is used to control the rate in which ECG samples 
are transferred to the **CCR1** register of **TIM1**.  
This is done autonomously and stops at the end of the ECG sample block.
A new cycle is started by the main routine, which controls the simulated 
heart rate.

For the TIM2 counter we set a dummy value of 100 counts, just to keep 
math simple, but it could be any value, since the timer is dedicated for 
this duty.

The sample rate depends on the desired BPM that the example will 
simulate and once programmed it will remain running at a constant rate. 

> If you choose a higher BPM, a slight increase is added to the sample 
rate, stretching the QRS. This is very limited since also human body 
cannot change the activity within a running beat too much and increasing 
the heart rate to a limit where two beats overlaps will break the logic 
of the program. In human body this is also not allowed and could be the 
cause for uncontrolled heart beat runs. 

On every update of this timer, a trigger is produced to cause a DMA 
transfer. 


# DMA Transfers

The DMA is used to copy an entry of the ECG Samples table to the **CCR1** 
register of **TIM1**. When no more samples are left the DMA stops the 
transfer.

So, the main program start the DMA to trigger an initial QRS pulse. Then
a software timer attached to one of the timers is used to compute the 
delay required for the specified heart rate. 

The main program waits until the heart rate period elapses to trigger the 
next DMA transfer. Aside from the control of the LED, the main program 
just waits until the next heart rate period expires, to trigger a new DMA 
transfer.

Like we saw before, on each TIM2 update, the DMA transfers a byte to the 
Channel 1 of TIM1 and specifies the PWM ratio. This progressively 
modulates the amplitudes on the filtered output pin and produce the QRS 
wave. 


# Band Pass Filter

The period of the timer is 256 µs, which is almost 4 kHz. ECG frequencies 
are in a on much lower. This enormous difference allows us to use a very 
simple band-pass filter.

This filter has the ability to convert the pulse ratio into a constant 
voltage, like in the picture:

![PWM Filter](https://www.realdigital.org/img/01231a14c587d8b64cf02979970e3b09.svg)

> Source: [Real Digital](https://www.realdigital.org/doc/6136c69c3acc4bf52bc2653a067e36cc)

For this example we chose very generic values for the R/C filter, but 
they produce quite good results. Note that if the cutoff frequency of the 
filter is too high the output is contaminated with additional noise 
caused by the pulse switching. On the other side too low cutoff 
frequencies will attenuate the ECG signal, which hinders the resulting 
wave. 

> Filter design is not the purpose of this example, which is a actually 
a very complex matter.  
> For production quality design it is recommended to let an analog 
electronics specialist design it.


# Other Analog Conversion Limitations

To keep the test simple, no AC decoupling of the PWM output is performed 
and result shall be observed using an oscilloscope. ECG signals have very 
low frequency and most slopes, like the ST segment, are very sensitive 
to the results interpretation. A good DC decoupling is normally a 
design effort also not covered by this example. 

Another issue is that PWM will produce values in the range of 0 and 3.3V, 
which is not compatible to human body, including any ECG capturing 
device.  
Usually, the human heart produces voltages below 10 mV.  
A good approach is to attenuate the PWM filtered output by a factor of up 
to 1000 and signal will be quite compatible with any ECG device found on 
the market. This is not covered by the circuit presented in this example.

> Actually, by hypothetically applying a 1000 factor attenuation, you 
will also attenuate the DC level, by the same factor, which turns your 
signal compatible with all EG devices, even without AC decoupling. Human 
body and electrodes, can easily introduce 100 or 200mV of DC offset, 
which are internally compensated by any professional ECG capturing 
device. 


# Comments to the Source Code


The example is build around the **examples\06-dma-pwm\main.cpp** file. 


## Including the **bmt** Library

It starts with the inclusion of the **bmt** library and a declaration to 
solve its namespace:

```cpp
#include <bmt.h>

using namespace Bmt;
using namespace Bmt::Timer;
```


## Handling Multiple Targets

Since the example can be tested in three different STM32 boards an 
include file is added, controlled by the build environment:


```cpp
#ifdef STM32F103xB
#	include "hal.f103.h"
#elif defined(STM32L432xx)
#	include "hal.l432.h"
#elif defined(STM32G431xx)
#	include "hal.g431.h"
#else
#error Unsupported configuration
#endif
```

Each include file specifies the following:
- Clock configuration
- The `SignalOut` data-type, which details the pin used as output. 
- The `InitPA`, `InitPB` and `InitPC` used to setup the GPIO.
- The `kPwmTimer` constant that specifies which timer is used to produce 
PWM output. 
- The `kPwmOutChannel` constant that specifies the Channel of the 
`kPwmTimer` timer where the PWM actually is implemented. 
- The `kUpdateTimer` constant that specifies which timer is used to 
control the rate that ECG samples are programmed into the PWM.
- The `IdDmaUpdate` constant that is used as DMA identification to 
resolve the correct DMA channel where ECG data will flow. 
- The `LedOn()`, `LedOff()` and `IsLedOn()` inline methods that allows 
the control of the LED. 

Then two contants are defined: a table containing the ECG samples and the count of elements on it:


## ECG Samples Table

```cpp
// This table contains an ECG sample using Absolute Offset Bytes format.
static constexpr uint8_t s_EcgTable[] =
{
	0x2D, 0x2D, 0x2F, 0x30, 0x31, 0x32, 0x34, 0x34,
	//...
	0x2D, 0x2D, 0x2C, 
};

// Size of the table containing ECG samples
constexpr uint32_t kTableSize = _countof(s_EcgTable);
```


## Data-types for the PWM Timer

The next step is to define data-types to setup the PWM timer, based on 
the information taken from the header file. 

```cpp
// Computes the prescaler for 1 MHz counter speed
typedef InternalClock_Hz <kPwmTimer, SysClk, 1000000> PwmFreq;
// PWM should quantize a byte (0-255), producing almost 4 kHz PWM sample rate
// A ~50 Hz low pass filter is required to produce the ECG signal
typedef Any<PwmFreq, Mode::kUpCounter, 255> Pwm;

// The output channel, attached to PWM timer
typedef AnyOutputChannel<Pwm
	, kPwmOutChannel
	, OutMode::kPWM1
	, Output::kEnabled
	, Output::kDisabled
	, true
	, true
> PwmOut;
```

The definitions establishes a PWM frequency of 1 MHz, and a PWM counting 
range between 0 and 255, corresponding exactly to 8 bits resolution. 
The third definition is used to program the timer channel to operate as 
output in PWM mode.


## Data-types for the Sample Rate Timer



# Testing the Example

The image blow shows a suggested breadboard montage for this example:

![06-dma-pwm_bb](images/06-dma-pwm_bb.png)

The resistor value is a **4k7** and the capacitor is **1µF**.

The orange wire is the Oscilloscope positive probe and black wire is the 
ground. 

The next image shows the oscilloscope capture for this case:

![ecg](images/ecg.png)


