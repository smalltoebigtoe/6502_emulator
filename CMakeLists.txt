cmake_minimum_required(VERSION 3.7)

if (${CMAKE_VERSION} VERSION_LESS 3.25)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.25)
endif()

project(6502_emulator VERSION 0.1
                      DESCRIPTION "very nice project"
                      LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-g -O0 -Wall -Werror -std=c++1z)
set(CPP_FILES "main.cpp;cpu.cpp;memory.cpp;machine_6502.cpp")

include_directories(${PROJECT_SOURCE_DIR})
add_executable(6502_emulator ${CPP_FILES})
