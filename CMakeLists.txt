cmake_minimum_required(VERSION 3.27)

project(paint)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(INCLUDE ${CMAKE_SOURCE_DIR}/include)
set(OPTIONS, -Wall -Wno-unused-value)

file(GLOB SOURCES src/*.c)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(OPTIONS, ${OPTIONS} -fsanitize=address -g)
endif()

if (${CMAKE_BUILD_TYPE} MATCHES "Release")
    set(OPTIONS, ${OPTIONS} -O3)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    file(GLOB SOURCES ${SOURCES} src/windows/*.c)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    file(GLOB SOURCES ${SOURCES} src/linux/*.c)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    file(GLOB SOURCES ${SOURCES} src/macos/*.c)
endif()

include_directories(${INCLUDE})
add_compile_options(${OPTIONS})
add_library(boom ${SOURCES})