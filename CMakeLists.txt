cmake_minimum_required(VERSION 3.27)

project(paint)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_compile_options(-Wall -Wno-unused-value -Wno-missing-braces)

file(GLOB FILES src/*.c)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_compile_options(-fsanitize=address -g)
endif()

if (${CMAKE_BUILD_TYPE} MATCHES "Release")
    add_compile_options(-fsanitize=address -O3)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    file(GLOB FILES ${FILES} src/windows/*.c)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    file(GLOB FILES ${FILES} src/linux/x11/*.c)

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(X11 REQUIRED IMPORTED_TARGET x11)
    include_directories(${X11_INCLUDE_DIRS})
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    file(GLOB FILES ${FILES} src/macos/*.c)
endif()

add_library(paint ${FILES})