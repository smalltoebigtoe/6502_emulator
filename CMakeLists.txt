cmake_minimum_required(VERSION 3.14.0)
project(6502_emulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-g -O0 -Wall -Werror -std=c++1z)

set(CPP_FILES "main.cpp;cpu.cpp;memory.cpp;machine_6502.cpp;debug.cpp;stack.cpp")
add_executable(6502_emulator ${CPP_FILES})
set_target_properties(6502_emulator PROPERTIES CXX_EXTENSIONS OFF OUTPUT_NAME 6502_emulator)
target_compile_features(6502_emulator PUBLIC cxx_std_17)
target_compile_options(6502_emulator PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
include_directories(../)

if(BUILD_TESTING)
    find_package(Catch2 3 REQUIRED)
    add_executable(cmp_test
      compare_instruction_test.cpp
      machine_6502.cpp
      cpu.cpp
      memory.cpp
      stack.cpp
      debug.cpp
    )

    target_link_libraries(cmp_test PRIVATE Catch2::Catch2WithMain)

    add_test(NAME cmp_test COMMAND cmp_test)
endif()
