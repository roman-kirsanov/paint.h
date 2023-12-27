cmake_minimum_required(VERSION 3.27)

project(example)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(INCLUDE ${CMAKE_SOURCE_DIR}/../include)
set(LIBRARIES ${CMAKE_SOURCE_DIR}/../.build/libpaint.a)
set(OPTIONS -Wall -Wno-missing-braces)

file(GLOB SOURCES src/*.c)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(OPTIONS ${OPTIONS} -fsanitize=address -g)
endif()

if (${CMAKE_BUILD_TYPE} MATCHES "Release")
    set(OPTIONS ${OPTIONS} -O3)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

    set(LIBRARIES ${LIBRARIES} ${GTK4_LIBRARIES})
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

endif()

include_directories(${INCLUDE})
add_compile_options(${OPTIONS})
link_libraries(${LIBRARIES})
add_executable(example ${SOURCES})