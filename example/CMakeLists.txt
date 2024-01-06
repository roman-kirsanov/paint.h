cmake_minimum_required(VERSION 3.27)

project(example)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

include_directories(${CMAKE_SOURCE_DIR}/../include)
link_libraries(${CMAKE_SOURCE_DIR}/../.build/libpaint.a)
add_compile_options(-Wall -Wno-missing-braces)

file(GLOB FILES src/*.c)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_compile_options(-fsanitize=address -g)
    add_link_options(-fsanitize=address)
endif()

if (${CMAKE_BUILD_TYPE} MATCHES "Release")
    add_compile_options(-O3)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(X11 REQUIRED IMPORTED_TARGET x11)
    link_libraries(${X11_LIBRARIES})
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

endif()

add_executable(example ${FILES})