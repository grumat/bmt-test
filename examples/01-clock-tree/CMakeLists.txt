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

