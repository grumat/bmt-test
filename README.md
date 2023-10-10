# <big>bmt-test</big> &ndash; Test and Examples for bmt Library

These are a collection of test projects for the **bmt library**.
Besides helping newcomers, these projects are also used to validate
template classes for the proposed targets.


## Supported Hardware

### Bluepill (STM32F103)

The bluepill is very common and easy to buy, although nowadays most of 
them contains clones of the STM32F103 part. Some deviation from the 
original part can happen and in the most cases it is not possible to 
identify the actual part that was mounted and this can cause issues. 

Thus, the bluepill is the most affordable option to start developing with 
the STM32 line of micro-controllers.  
In general, the following pinout is expected:

![Bluepill-Pinout.png](images/Bluepill-Pinout.png)


### Nucleo32 L432KC (STM32L432KC)

The Nucleo32 is an original kit, not so cheap as a bluepill, but still 
very affordable. It has also far more hardware mounted on it, 
specifically a STLink V2 debug unit.

This microcontroller line is more modern than the original STM32F1xx line 
and has considerably more performance per MHz and features a single 
precision float unit.

This is the pin-out:

![nucleo_l432kc-pinout.png](images/nucleo_l432kc-pinout.png)


### Nucleo32 G431KB (STM32G431KB)

The very recent line of low cost controllers, blows out every other 
supported option, also on an affordable board:

![nucleo-g431kb-pinout.png](images/nucleo-g431kb-pinout.png)

In this newer board generation, a STLink V3 is provided as debug unit. 


#### Board Setup

This board has many configurable jumpers and the default settings does 
not comply with the examples in this repository, which require the 
optional **24 MHz** crystal.  
For this, you should short the **SB9** and **SB10** jumpers.

For details check **UM2397 Rev 2** on page **15**.


# List of Examples

## 01 &ndash; Clock Setup

A minimal project and a good starting point, demonstrating how to setup 
the system clock.

[Follow this link.](examples/01-clock-tree/README.md)


## 02 &ndash; System Tick and Delay

In this project we demonstrate how to use the Cortex System Tick timer 
to produce different ways of delays.

[Follow this link.](examples/02-systick-delay/README.md)


## 03 &ndash; Using GPIO (Control the LCD1602 Display)

GPIO is one of the most flexible and powerful interface of a MCU. This 
example demonstrate a couple of interesting available features:

[Follow this link.](examples/03-gpio-lcd1602/README.md)


## 04 &ndash; Basic Use of Timers for Delays

STM32 Timers are packed with many features to control time-sensitive 
devices. This example demonstrates how to setup a STM32 timer and to 
couple delay classes and produce delays ensuring portable code.

[Follow this link.](examples/04-timer-delay/README.md)


## 05 &ndash; Using Timer as a PWM (RGB LED Blink)

Timers can be configured as PWM to efficiently control intensity of 
electro-mechanic devices, interfacing with simple electronic on/off 
switches.  
This example controls an RGB LED using a single timer and 3 compare 
channels. 

[Follow this link.](examples/05-pwm/README.md)


## 06 &ndash; ECG Simulator: Uses DMA and PWM to Produce a Wave 

Two timer, one producing PWM and the other feeding sample values to 
module the PWM ratio, producing an Analog wave.  
This example implements a simple ECG simulator, with some basic feature, 
like heart rate and sample rate.

[Follow this link.](examples/06-dma-pwm/README.md)


# Using VSCode as Development Platform

One of the challenge on Bare Metal development is a IDE capable of tuning 
all required parameter and paths for the build.

In this series we opt the use of free software, which is far from easy to 
setup. 

The repository uses the CMake as build environment, which is not trivial. 
In general you have to handle with so much stuff by yourself that it is 
almost impossible for a newcomer to develop embedded software. These are 
market options that I would never use it or recommend, except for the 
community argument, which is really the most important thing on free 
software. 

> **A bit of rant:**  
On the past I discovered what drives the complexity around the open 
source world and why things are done in such a cryptic way as I read the 
title of a chapter found on the RedHat Linux 9 Manual. The topic was 
titled something like " How to impress your friends using RPM". It is a 
pity that we have to handle with these egos...  
There are so many projects out there that are very functional and simple, 
but have no community, while having useless complexity grow up to 
standards. Egos...


## Specifying Compilers

Please check the `${workspaceFolder}/.vscode/cmake-kits.json` file. 
This file contains a list of possible compiler toolkit's. For instance, 
just a single compiler is specified and this is the distribution provided 
by **SysProgs** for the **VisualGDB** plugin. Even though the plugin is 
commercial software, the compilers can be freely installed. Please check 
the [https://gnutoolchains.com/download/](https://gnutoolchains.com/download/) 
website.

The mentioned file indicates that the configuration for the **SysProgs** 
distribution can be found on `${workspaceFolder}/cmake/arm-eabi.cmake`. 
This *yet-another-cryptic-file* contains instructions on how cmake will 
drive the toolkit.  
Looking in detail, you will notice that it has ways to 
specify paths to the compiler and command line options for the many 
possibilities we have during a build, like **debug** or **release** build 
and source code programming language (**ASM**, **C** or **C++**).


## Building for Multiple Targets

Since the **bmt** library supports 3 different STM32 generations, you 
have to specify the target for the scripts. VSCode has a feature for 
multiple configurations, when using cmake projects. You should put the
`${workspaceFolder}/cmake-variants.yaml` file on the project folder and 
this file contains information necessary for each variant.  
If you check the file, you will see that it specifies **debug** and 
**release** build types and all three different MCUs, the STM32F103, 
STM32L432 and the STM32G431. 

This file feeds a field in the bottom bar of the VSCode IDE, where you 
can select the desired target build.

Each option provides specific settings for the cmake build system, 
through the **`TARGET_MCU`**, **`DEVICE_SUPPORT`**, **`CPU_FLAG`**, 
**`CUBE_MX`** and **`LINKER_SCRIPT`** variables.


## The Root `CMakeLists.txt` File

At the root directory you will find the **`CMakeLists.txt`** file that is 
used as our main *make file* entry. It establishes the base values for 
a series of variables that will be shared among all example projects. 

The table below summarizes it:

| Variable               | Usage                                        |
|------------------------|----------------------------------------------|
| BMT_PATH               | Path to the *bmt library*.                   |
| BSP_PATH               | Path to the selected **BSP** directory.      |
| CMAKE_ASM_FLAGS        | Composes the final gcc options used to compile Assembly files |
| CMAKE_C_FLAGS          | Composes the final gcc options used to compile C files |
| CMAKE_CXX_FLAGS        | Composes the final gcc options used to compile C++ files |
| OPT_USE_VISUALGDB      | Choose wether you use VisualGDB BSP or CubeMX files |
| STARTUP_FILE           | The startup file contains the code to start executing programs for the specified MCU. |

After all variables are defined, the script instruct to include every 
path containing one example. When `cmake.exe` is executed all examples 
are compiled at once. 

> **cmake** is a quite complex, bloated and opaque. For a complete 
reference it is advised to check documentation in the 
[https://cmake.org/](https://cmake.org/) website. Far from ideal, a clear 
tendency is to find a solution to your problem in sites like the 
*Stack Overflow* and just copy and paste it into your script.


## Examples sub-make-files

Each example project has a respective **`CMakeLists.txt`** file with the 
instructions required to produce the executable.

```cmake
cmake_minimum_required(VERSION 3.5.0)

#[[
include(CTest)
enable_testing()
]]

set(APP_NAME 01-clock-tree-${TARGET_MCU}.elf)

message(STARTUP_FILE="${STARTUP_FILE}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_HOME_DIRECTORY}/LDS/${LINKER_SCRIPT}")
add_executable(${APP_NAME} ${STARTUP_FILE} main.cpp)

set_target_properties(${TARGET_NAME} PROPERTIES LINK_DEPENDS ${CMAKE_HOME_DIRECTORY}/LDS/${LINKER_SCRIPT})

add_custom_command(TARGET ${APP_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJDUMP} -h -z -S $<TARGET_FILE:${APP_NAME}> > ${APP_NAME}.lst
    VERBATIM)
```

The file consists of the following definitions:
- Definition of the application name, through the **`APP_NAME`** 
variable. 
- Definition of the **`CMAKE_EXE_LINKER_FLAGS`** linker flags.
- The list of files required to build the exe file with the output file 
name.
- Declaration of application dependency on the linker script file, so 
changes on this script will get applied to the executable.
- A final step that generates the assembly output after the application 
was build. I like to see assembly output when experimenting with code 
optimizations. 


# General Documentation

Take a look at some documentation resources:
- [**bmt** Installation Guide](bmt/docs/INSTALL.md)
- [Design Concepts](bmt/docs/CONCEPTS.md)
- [System Clock](bmt/docs/clocks.md)
- [GPIO](bmt/docs/gpio.md)
- [Timers](bmt/docs/timers.md)
- [DMA](bmt/docs/dma.md)


