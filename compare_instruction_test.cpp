#include <catch2/catch_test_macros.hpp>

#include "machine_6502.h"

TEST_CASE("Compare Instructions", "[machine_6502]") {
  Machine_6502 machine;

  SECTION("cmp: >=, ==, != 0x80") {
    std::vector<Byte> binary_instructions = {0xC5, 0xAA};  // CMP_IMM
    machine.get_cpu().A = 0xAA;
    machine.load(binary_instructions, 0);
    machine.execute(machine);

    REQUIRE(machine.get_cpu().CF == true);
    REQUIRE(machine.get_cpu().ZF == true);
    // need to test (result & 0x80) == 0x80
  }
}
