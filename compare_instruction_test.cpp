#include <catch2/catch_test_macros.hpp>

#include "machine_6502.h"
#include "debug.h"

#define LOAD_INS 0x0600

/* NF register not yet tested */
TEST_CASE("Compare Immediate", "[machine_6502]") {
  Machine_6502 machine;

  SECTION("==") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_IM, 0xAA};  
    machine.get_cpu().A = 0xAA;
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == true);
    REQUIRE(machine.get_cpu().ZF == true);
  } machine.reset();
  SECTION(">") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_IM, 0xAA}; 
    machine.get_cpu().A = 0xFF;
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == true);
    REQUIRE(machine.get_cpu().ZF == false);
  } machine.reset();
  SECTION("<") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_IM, 0xFF}; 
    machine.get_cpu().A = 0xAA;
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == false);
    REQUIRE(machine.get_cpu().ZF == false);
  } machine.reset();
}

TEST_CASE("Compare Zero Page", "[machine_6502]") {
  Machine_6502 machine;

  SECTION("==") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_ZP, 0xAA};  
    machine.get_cpu().A = 0xFF;
    machine.get_module().set_at(0xAA, 0xFF);
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == true);
    REQUIRE(machine.get_cpu().ZF == true);
  } machine.reset();
  SECTION(">") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_ZP, 0xAA};  
    machine.get_cpu().A = 0xFF;
    machine.get_module().set_at(0xAA, 0xCC);
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == true);
    REQUIRE(machine.get_cpu().ZF == false);
  } machine.reset();
  SECTION("<") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_ZP, 0xAA};  
    machine.get_cpu().A = 0xCC;
    machine.get_module().set_at(0xAA, 0xFF);
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == false);
    REQUIRE(machine.get_cpu().ZF == false);
  } machine.reset(); 
}

TEST_CASE("Compare Zero Page X", "[machine_6502]") {
  Machine_6502 machine;

  SECTION("==") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_ZPX, 0x10};
    machine.get_cpu().A = 0xCC;
    machine.get_cpu().X = 0x01;
    machine.get_module().set_at(0x11, 0xCC);
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == true);
    REQUIRE(machine.get_cpu().ZF == true);
  } machine.reset();
  SECTION(">") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_ZPX, 0x10};
    machine.get_cpu().A = 0xCC;
    machine.get_cpu().X = 0x01;
    machine.get_module().set_at(0x11, 0xBB);
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == true);
    REQUIRE(machine.get_cpu().ZF == false);
  } machine.reset();
  SECTION("<") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_ZPX, 0x10};
    machine.get_cpu().A = 0xCC;
    machine.get_cpu().X = 0x01;
    machine.get_module().set_at(0x11, 0xEE);
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == false);
    REQUIRE(machine.get_cpu().ZF == false);
  } machine.reset();
}

TEST_CASE("Compare Absolute", "[machine_6502]") {
  Machine_6502 machine;

  SECTION("==") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_ABS, 0xFF, 0xAA}; 
    machine.get_cpu().A = 0xAA;
    machine.load(binary_instructions, LOAD_INS);
    machine.get_module().set_at(0xAAFF, 0xAA);
    machine.execute(machine);

    REQUIRE(machine.get_cpu().CF == true);
    REQUIRE(machine.get_cpu().ZF == true);
  } machine.reset();
  SECTION(">") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_ABS, 0xFF, 0xAA}; 
    machine.get_cpu().A = 0xFF;
    machine.load(binary_instructions, LOAD_INS);
    machine.get_module().set_at(0xAAFF, 0xAA);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == true);
    REQUIRE(machine.get_cpu().ZF == false);
  } machine.reset();
  SECTION("<") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_ABS, 0xFF, 0xAA};
    machine.get_cpu().A = 0xAA;
    machine.load(binary_instructions, LOAD_INS);
    machine.get_module().set_at(0xAAFF, 0xFF);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == false);
    REQUIRE(machine.get_cpu().ZF == false);
  } machine.reset();
}

TEST_CASE("Compare Absolute X", "[machine_6502]") {
  Machine_6502 machine;

  SECTION("==") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_ABSX, 0xFF, 0xAA};
    machine.get_cpu().A = 0xAA;
    machine.load(binary_instructions, LOAD_INS);
    machine.get_module().set_at(0xAAFF + machine.get_cpu().X, 0xAA);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == true);
    REQUIRE(machine.get_cpu().ZF == true);
  } machine.reset();
  SECTION(">") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_ABSX, 0xFF, 0xAA};
    machine.get_cpu().A = 0xFF;
    machine.load(binary_instructions, LOAD_INS);
    machine.get_module().set_at(0xAAFF + machine.get_cpu().X, 0xAA);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == true);
    REQUIRE(machine.get_cpu().ZF == false);
  } machine.reset();
  SECTION("<") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_ABSX, 0xFF, 0xAA};
    machine.get_cpu().A = 0xAA;
    machine.load(binary_instructions, LOAD_INS);
    machine.get_module().set_at(0xAAFF + machine.get_cpu().X, 0xFF);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == false);
    REQUIRE(machine.get_cpu().ZF == false);
  } machine.reset();
}

TEST_CASE("Compare Absolute Y", "[machine_6502]") {
  Machine_6502 machine;

  SECTION("==") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_ABSY, 0xFF, 0xAA};
    machine.get_cpu().A = 0xAA;
    machine.load(binary_instructions, LOAD_INS);
    machine.get_module().set_at(0xAAFF + machine.get_cpu().Y, 0xAA);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == true);
    REQUIRE(machine.get_cpu().ZF == true);
  } machine.reset();
  SECTION(">") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_ABSY, 0xFF, 0xAA};
    machine.get_cpu().A = 0xFF;
    machine.load(binary_instructions, LOAD_INS);
    machine.get_module().set_at(0xAAFF + machine.get_cpu().Y, 0xAA);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == true);
    REQUIRE(machine.get_cpu().ZF == false);
  } machine.reset();
  SECTION("<") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_ABSY, 0xFF, 0xAA};
    machine.get_cpu().A = 0xAA;
    machine.load(binary_instructions, LOAD_INS);
    machine.get_module().set_at(0xAAFF + machine.get_cpu().Y, 0xFF);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == false);
    REQUIRE(machine.get_cpu().ZF == false);
  } machine.reset();
}

TEST_CASE("Compare Indirect X", "[machine_6502]") {
  Machine_6502 machine;

  SECTION("==") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_INX, 0x01};
    machine.get_cpu().A = 0xCC;
    machine.get_cpu().X = 0x10;
    machine.get_module().set_at(0x11, 0xBC);
    machine.get_module().set_at(0x12, 0xDE);
    machine.get_module().set_at(0xDEBC, 0xCC);
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == true);
    REQUIRE(machine.get_cpu().ZF == true);
  } machine.reset();
  SECTION(">") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_INX, 0x01};
    machine.get_cpu().A = 0xCC;
    machine.get_cpu().X = 0x10;
    machine.get_module().set_at(0x11, 0xBC);
    machine.get_module().set_at(0x12, 0xDE);
    machine.get_module().set_at(0xDEBC, 0xAA);
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == true);
    REQUIRE(machine.get_cpu().ZF == false);
  } machine.reset();
  SECTION("<") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_INX, 0x01};
    machine.get_cpu().A = 0xCC;
    machine.get_cpu().X = 0x10;
    machine.get_module().set_at(0x11, 0xBC);
    machine.get_module().set_at(0x12, 0xDE);
    machine.get_module().set_at(0xDEBC, 0xFF);
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == false);
    REQUIRE(machine.get_cpu().ZF == false);
  } machine.reset();
}

TEST_CASE("Compare Indirect Y", "[machine_6502]") {
  Machine_6502 machine;

  SECTION("==") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_INY, 0xB4};
    machine.get_cpu().A = 0xCC;
    machine.get_cpu().Y = 0x06;
    machine.get_module().set_at(0xB4, 0xEE);
    machine.get_module().set_at(0xB5, 0x12);
    machine.get_module().set_at(0x12EE + 0x06, 0xCC);
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == true);
    REQUIRE(machine.get_cpu().ZF == true);
  } machine.reset();
  SECTION(">") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_INY, 0xB4};
    machine.get_cpu().A = 0xCC;
    machine.get_cpu().Y = 0x06;
    machine.get_module().set_at(0xB4, 0xEE);
    machine.get_module().set_at(0xB5, 0x12);
    machine.get_module().set_at(0x12EE + 0x06, 0xAA);
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == true);
    REQUIRE(machine.get_cpu().ZF == false);
  } machine.reset();
  SECTION("<") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_INY, 0xB4};
    machine.get_cpu().A = 0xAA;
    machine.get_cpu().Y = 0x06;
    machine.get_module().set_at(0xB4, 0xEE);
    machine.get_module().set_at(0xB5, 0x12);
    machine.get_module().set_at(0x12EE + 0x06, 0xFF);
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == false);
    REQUIRE(machine.get_cpu().ZF == false);
  } machine.reset();
}
