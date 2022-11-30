#include <catch2/catch_test_macros.hpp>

#include "machine_6502.h"
#include "debug.h"

#define LOAD_INS 0x0600

/* NF register not yet tested */
TEST_CASE("Compare Immediate", "[machine_6502]") {
  Machine_6502 machine;

  SECTION("==") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_IMM, 0xAA};  
    machine.get_cpu().A = 0xAA;
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == true);
    REQUIRE(machine.get_cpu().ZF == true);
  } machine.reset();
  SECTION(">") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_IMM, 0xAA}; 
    machine.get_cpu().A = 0xFF;
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().CF == true);
    REQUIRE(machine.get_cpu().ZF == false);
  } machine.reset();
  SECTION("<") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().CMP_IMM, 0xFF}; 
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

TEST_CASE("Load", "[machine_6502]") {
  Machine_6502 machine;

  SECTION("Immediate") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().LDA_IMM, 0xCD};
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().A == 0xCD);
  } machine.reset();
  SECTION("Zero Page") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().LDA_ZP, 0xCD};
    machine.get_module().set_at(0xCD, 0xFA);
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().A == 0xFA);
  } machine.reset(); 
  SECTION("Zero Page X") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().LDA_ZPX, 0x10};
    machine.get_cpu().X = 0x01;
    machine.get_module().set_at(0x11, 0x1C);
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().A == 0x1C);
  } machine.reset();
  SECTION("Absolute") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().LDA_ABS, 0xAA, 0xAB};
    machine.get_module().set_at(0xABAA, 0xFA);
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().A == 0xFA);
  } machine.reset();
  SECTION("Absolute X") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().LDA_ABSX, 0xF4, 0x53};
    machine.get_cpu().X = 0x03;
    machine.get_module().set_at(0x53F7, 0xCD);
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().A == 0xCD);
  } machine.reset();
  SECTION("Absolute Y") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().LDA_ABSY, 0x44, 0x00};
    machine.get_cpu().Y = 0x05;
    machine.get_module().set_at(0x0049, 0xEE);
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().A == 0xEE);
  } machine.reset();
  SECTION("Indirect X") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().LDA_INX, 0xB4};
    machine.get_cpu().X = 0x06;
    machine.get_module().set_at(0xBA, 0x12);
    machine.get_module().set_at(0xBB, 0xEE);
    machine.get_module().set_at(0xEE12, 0x0A);
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().A == 0x0A);  // fail
  } machine.reset();
  SECTION("Indirect Y") {
    std::vector<Byte> binary_instructions = {machine.get_cpu().LDA_INY, 0xB4};
    machine.get_cpu().Y = 0x01;
    machine.get_module().set_at(0xB4, 0x04);
    machine.get_module().set_at(0xB5, 0x12);
    machine.get_module().set_at(0x1205, 0xDE);
    machine.load(binary_instructions, LOAD_INS);
    machine.execute(machine);
    REQUIRE(machine.get_cpu().A == 0xDE);
  } machine.reset();
}
