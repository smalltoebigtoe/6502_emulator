#include "cpu.h"

void CPU::reset() {
  PC = 0xFFFC;
  SP = 0x0100;
  CF = ZF = IDF = DMF = BCF = OFF = NF = 0x0;
  A = X = Y = 0x0;
}

Byte CPU::fetch_byte(Memory& module, u32 cycles) {
  Byte data = module.data[PC];
  PC++;
  cycles--;
  return data;
}

void CPU::reg_cmp(Byte operand, Byte reg) {
  ;
}

void CPU::exe(Memory& module, u32 cycles) {
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
