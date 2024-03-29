#ifndef CPU_H
#define CPU_H

#include <iostream>

#include "memory.h"

struct CPU
{
  Word PC;  // program counter
  Word SP;  // stack pointer
  Byte A;  // register A (accumulator)
  Byte X;  // register X
  Byte Y;  // register Y
  Byte processor_status;

  bool CF;   // carry flag
  bool ZF;   // zero flag
  bool IDF;  // interrupt disable flag
  bool DMF;  // decimal mode flag
  bool BCF;  // break command flag
  bool OFF;  // overflow flag
  bool NF;   // negative flag

  static constexpr Byte
    CMP_IMM = 0xC9,
    CMP_ZP = 0xC5,
    CMP_ZPX = 0xD5,
    CMP_ABS = 0xCD,
    CMP_ABSX = 0xDD,
    CMP_ABSY = 0xD9,
    CMP_INX = 0xC1,
    CMP_INY = 0xD1;

  static constexpr Byte
    LDA_IMM   = 0xA9,
    LDA_ZP   = 0xA5,
    LDA_ZPX  = 0xB5,
    LDA_ABS  = 0xAD,
    LDA_ABSX = 0xBD,
    LDA_ABSY = 0xB9,
    LDA_INX  = 0xA1,
    LDA_INY  = 0xB1;

  void reset();
  Byte fetch_instruction(Memory& module);
};

#endif
