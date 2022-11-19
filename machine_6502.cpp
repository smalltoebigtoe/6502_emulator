#include "machine_6502.h"

Machine_6502::Machine_6502(CPU& cpu, Memory& module) {
  m_cpu = cpu;
  m_module = module;
  std::cout << "6502 machine created..." << '\n';
}

void Machine_6502::load(std::vector<Byte> instructions) {
  ;
}

void Machine_6502::reset() {
  m_cpu.reset();
  m_module.reset();
  std::cout << "6502 machine restarted." << '\n';
}
