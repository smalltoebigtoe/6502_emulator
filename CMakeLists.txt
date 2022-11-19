cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(6502_emulator VERSION 0.1)
include_directories(${PROJECT_SOURCE_DIR})
add_executable(6502_emulator main.cpp cpu.cpp memory.cpp machine_6502.cpp)
