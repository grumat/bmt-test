# <big>bmt-test</big> &ndash; Test and Examples for bmt Library

These are a collection of test projects for the **bmt library**.
Besides helping newcomers, these projects are also used to validate
template classes for the proposed targets.


## Supported Hardware

### Bluepill (STM32F103)

![Bluepill-Pinout.png](images/Bluepill-Pinout.png)


### Nucleo32 L432KC (STM32L432KC)

![nucleo_l432kc-pinout.png](images/nucleo_l432kc-pinout.png)


### Nucleo32 G431KB (STM32G431KB)

![nucleo-g431kb-pinout.png](images/nucleo-g431kb-pinout.png)


# 01 &ndash; Clock Setup

A minimal project and a good starting point, demonstrating how to setup 
the system clock.

[Follow this link.](examples/01-clock-tree/README.md)


# 02 &ndash; System Tick and Delay

In this project we demonstrate how to use the Cortex System Tick timer 
to produce different ways of delays.

[Follow this link.](examples/02-systick-delay/README.md)


# 03 &ndash; Using GPIO (Control the LCD1602 Display)

GPIO is one of the most flexible and powerful interface of a MCU. This 
example demonstrate a couple of interesting available features:

[Follow this link.](examples/03-gpio-lcd1602/README.md)


# 04 &ndash; Basic Use of Timers for Delays

STM32 Timers are packed with many features to control time-sensitive 
devices. This example demonstrates how to setup a STM32 timer and to 
couple delay classes and produce delays ensuring portable code.

[Follow this link.](examples/04-timer-delay/README.md)


# 05 &ndash; Using Timer as a PWM (RGB LED Blink)

Timers can be configured as PWM to efficiently control intensity of 
electro-mechanic devices, interfacing with simple electronic on/off 
switches.  
This example controls an RGB LED using a single timer and 3 compare 
channels. 

[Follow this link.](examples/05-pwm/README.md)


# 06 &ndash; Using DMA and PWM to Produce a Wave (ECG Simulator)

Two timer, one producing PWM and the other feeding sample values to 
module the PWM ratio, producing an Analog wave.  
This example implements a simple ECG simulator, with some basic feature, like heart rate and sample rate.

[Follow this link.](examples/06-dma-pwm/README.md)


