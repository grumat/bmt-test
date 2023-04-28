cmake_minimum_required(VERSION 3.0.0)
project(bmt-test LANGUAGES C CXX ASM VERSION 0.1.0)

# Use Unix makefile with tis option to inspect command line, since I appreciate 
# my time and won't continue looking for similar solution in Ninja
set(CMAKE_VERBOSE_MAKEFILE TRUE)

# Set tis to true to use the BSP provided with VisualGDB; if not, then CubeMX should have all BSP installed
set(OPT_USE_VISUALGDB false)

# Configure CPU flag according to target MCU
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=${CPU_FLAG}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcpu=${CPU_FLAG}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -mcpu=${CPU_FLAG}")

set(BMT_PATH ${PROJECT_SOURCE_DIR}/bmt/include)
string (TOLOWER ${TARGET_MCU} TARGET_MCU_LOWER)
if (${OPT_USE_VISUALGDB})
	file(TO_CMAKE_PATH "$ENV{LOCALAPPDATA}" LOCALAPPDATA)
	# Device names are not well standardized in this environment. we shall add an extra 'xx' on the path. Although, not for every location...
	set(BSP_PATH ${LOCALAPPDATA}/VisualGDB/EmbeddedBSPs/arm-eabi/com.sysprogs.arm.stm32/${DEVICE_SUPPORT}xx)
	set(STARTUP_FILE ${BSP_PATH}/StartupFiles/startup_${TARGET_MCU_LOWER}.c)
	include_directories (${BSP_PATH}/CMSIS_HAL/Device/ST/${DEVICE_SUPPORT}/Include)
	include_directories (${BSP_PATH}/CMSIS_HAL/Include)
else ()
	file(TO_CMAKE_PATH "$ENV{USERPROFILE}" USERPROFILE)
	set(BSP_PATH ${USERPROFILE}/STM32Cube/Repository/${CUBE_MX}/Drivers)
	set(STARTUP_FILE ${BSP_PATH}/CMSIS/Device/ST/${DEVICE_SUPPORT}/Source/Templates/gcc/startup_${TARGET_MCU_LOWER}.s)
	include_directories (${BSP_PATH}/CMSIS/Device/ST/${DEVICE_SUPPORT}/Include)
	include_directories (${BSP_PATH}/CMSIS/Include)
endif()


include_directories (${BMT_PATH})
add_compile_definitions(${TARGET_MCU})

add_subdirectory(examples/01-clock-tree)
