#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>

typedef unsigned char Byte;  // 1 byte
typedef unsigned short Word;  // 2 bytes
typedef unsigned int u32;

struct Memory
{
  static const u32 MAX = 1024 * 64;
  Byte data[MAX];

  void init() {
    for (u32 i = 0; i < MAX; i++) {
      data[i] = 0x0;
    }
  }

  Byte operator[](u32 address) const {
    // assert(address > MAX);
    return data[address];
  }
};

struct CPU
{
  /* points to next instruction to be executed. modified automatically as instructions are executed */
  Word PC;  // program counter

  /* 256byte stack between 0x0100 and 0x01FF of 1 byte strides, cannot detect overflow */
  Word SP;  // stack pointer

  /* all arithmetic and logical operations except inc++ or dec--. contents can be retrieved and stored
      in memory and stack. NOTE: most complex operations use this and efficient optimization is important */
  Byte A;  // register A (accumulator)

  /* holdes counters and offsets for accessing memory. can be loaded and saved in memory,
      compared with values in memory, inc++ or dec--. special fn: get a copy of SP or change its value */
  Byte X;  // register X

  /* similar to register X, except with no special functions */
  Byte Y;  // register Y

  bool CF;   // carry flag
  bool ZF;   // zero flag
  bool IDF;  // interrupt disable flag
  bool DMF;  // decimal mode flag
  bool BCF;  // break command flag
  bool OFF;  // overflow flag
  bool NF;   // negative flag

  /* instructions */
  static constexpr Byte
    CMP_IM = 0xC9,
    CMP_ZP = 0xC5,
    CMP_ZPX = 0xD5,
    CMP_ABS = 0xCD,
    CMP_ABSX = 0xDD,
    CMP_ABSY = 0xD9,
    CMP_INX = 0xC1,
    CMP_INY = 0xD1;

  void CMP() {
    ;
  }

  /* opcodes */
  static constexpr Byte
    LDA_IM   = 0xA9,
    LDA_ZP   = 0xA5,
    LDA_ZPX  = 0xB5,
    LDA_ABS  = 0xAD,
    LDA_ABSX = 0xBD,
    LDA_ABSY = 0xB9,
    LDA_INX  = 0xA1,
    LDA_INY  = 0xB1;

  void reset(Memory& module) {
    PC = 0xFFFC;
    SP = 0x0100;
    CF = ZF = IDF = DMF = BCF = OFF = NF = 0x0;
    A = X = Y = 0x0;
    module.init();
  }

  Byte fetch_byte(Memory& module, u32 cycles) {
    Byte data = module.data[PC];
    PC++;
    cycles--;
    return data;
  }

  void reg_cmp(Byte operand, Byte reg) {
    ;
  }

  void exe(Memory& module, u32 cycles) {
    while (cycles > 0) {
      Byte instr = fetch_byte(module, cycles);
      switch (instr) {
        case (LDA_IM):
          Byte operand = fetch_byte(module, cycles);
          reg_cmp(operand, A);
          break;
      }
      cycles--;
    }
  }
};



int main(void)
{
  Memory RAM;
  CPU CPU;
  CPU.reset(RAM);
  CPU.exe(RAM, 2);  // executes 2 instructions 

  std::cout << RAM.data[RAM.MAX-1] << '\n';
  std::cout << CPU.PC << '\n';

  int x;
  std::cin >> x;
  return 0;
}