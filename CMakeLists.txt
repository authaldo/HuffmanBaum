cmake_minimum_required(VERSION 3.14)
project(HuffmanBaum)

set(CMAKE_CXX_STANDARD 14)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror -march=native -mtune=native") # Alle Warnings, optimierung für die akuelle Architektur
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer") # Address Sanitizer aktivieren
else()
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O3") # O3 für Release Builds
endif ()

add_executable(HuffmanBaum main.cpp HuffmanNode.cpp)