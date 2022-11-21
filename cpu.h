#ifndef CPU_H
#define CPU_H

#include <iostream>

#include "memory.h"

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

  void reset();
  void reg_cmp(Byte operand, Byte reg);
  Byte fetch_instruction(Memory& module);
  void execute(Memory& module);
  void CMP();

};

#endif
