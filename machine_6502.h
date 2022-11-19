#ifndef MACHINE_6502_H
#define MACHINE_6502_H

#include <iostream>
#include <vector>

#include "cpu.h"
#include "memory.h"

class Machine_6502 {
  private:
    CPU m_cpu {};
    Memory m_module {};

  public:
    Machine_6502(CPU& cpu, Memory& module);
    void load(std::vector<Byte> instructions);
    void reset();
};

#endif
