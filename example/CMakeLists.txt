cmake_minimum_required(VERSION 3.27)

project(example)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(INCLUDE ${CMAKE_SOURCE_DIR}/../include)
set(LIBRARIES ${CMAKE_SOURCE_DIR}/../.build/libpaint.a)
set(COPTIONS -Wall -Wno-missing-braces)

file(GLOB SOURCES src/*.c)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(COPTIONS ${COPTIONS} -fsanitize=address -g)
    set(LOPTIONS -fsanitize=address)
endif()

if (${CMAKE_BUILD_TYPE} MATCHES "Release")
    set(COPTIONS ${COPTIONS} -O3)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(X11 REQUIRED IMPORTED_TARGET x11)

    set(LIBRARIES ${LIBRARIES} ${X11_LIBRARIES})
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

endif()

include_directories(${INCLUDE})
add_compile_options(${COPTIONS})
add_link_options(${LOPTIONS})
link_libraries(${LIBRARIES})
add_executable(example ${SOURCES})