#include "cpu.h"

void CPU::reset() {
  PC = 0xFFFC;
  SP = 0x0100;
  CF = ZF = IDF = DMF = BCF = OFF = NF = 0x0;
  A = X = Y = 0x0;
}

/* IMPORTANT:
    Can't increase PC after returning, so PC-1, but real PC is at correct value */
Byte CPU::fetch_instruction(Memory& module) {
  PC++;
  std::cout << "Instruction @ PC[" << PC-1 << "]" << " -> ";
  //print_Byte(module.data[PC-1]);

  return module.data[PC-1];
}
