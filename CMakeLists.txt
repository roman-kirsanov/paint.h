cmake_minimum_required(VERSION 3.27)

project(paint)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(INCLUDE ${CMAKE_SOURCE_DIR}/include)
set(COPTIONS -Wall -Wno-unused-value -Wno-missing-braces)

file(GLOB SOURCES src/*.c)

message(INFO ${CMAKE_BUILD_TYPE})

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(COPTIONS ${COPTIONS} -fsanitize=address -g)
endif()

if (${CMAKE_BUILD_TYPE} MATCHES "Release")
    set(COPTIONS ${COPTIONS} -O3)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    file(GLOB SOURCES ${SOURCES} src/windows/*.c)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    file(GLOB SOURCES ${SOURCES} src/linux/gtk4/*.c)

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)
    set(INCLUDE ${INCLUDE} ${GTK4_INCLUDE_DIRS})
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    file(GLOB SOURCES ${SOURCES} src/macos/*.c)
endif()

include_directories(${INCLUDE})
add_compile_options(${COPTIONS})
add_library(paint ${SOURCES})