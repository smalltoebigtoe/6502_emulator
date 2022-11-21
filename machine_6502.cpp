#include "machine_6502.h"

Machine_6502::Machine_6502()
  : m_instruction_address{ 0 }, m_instruction_size{ 0 } {
  CPU cpu;
  Memory memory;
  cpu.reset();
  memory.reset();
  m_cpu = &cpu;
  m_module = &memory;
  std::cout << "6502 machine created..." << '\n';
}

CPU& Machine_6502::get_cpu() {
  return *m_cpu;
}

Memory& Machine_6502::get_module() {
  return *m_module;
}

void Machine_6502::load(const std::vector<Byte> instructions, Word address) {
  m_instruction_address = address;
  m_instruction_size = instructions.size();

  if (m_instruction_size > m_module->MAX)
    throw std::runtime_error("Instructions too large to fit in memory");

  for (auto i = 0; i < instructions.size(); i++) {
    m_module->data[address+i] = instructions.at(i);
  }
  m_cpu->PC = address;
  std::cout << "loaded instructions in memory." << '\n';
}

bool Machine_6502::eop() {
  return m_cpu->PC >= m_instruction_address + m_instruction_size;
}

void Machine_6502::run() {
  while (!eop()) {
    m_cpu->execute(*m_module);
  }
}

void Machine_6502::reset() {
  m_cpu->reset();
  m_module->reset();
  m_instruction_address = 0;
  m_instruction_size = 0;

  std::cout << "6502 machine restarted." << '\n';
}
