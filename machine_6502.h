#ifndef MACHINE_6502_H
#define MACHINE_6502_H

#include <iostream>
#include <vector>

#include "cpu.h"
#include "memory.h"
#include "data.h"

class Machine_6502 {
  private:
    CPU* m_cpu;
    Memory* m_module;

    Word m_instruction_address;
    Word m_instruction_size;

  public:
    Machine_6502();
    CPU& get_cpu();
    Memory& get_module();
    void load(const std::vector<Byte> instructions, Word address);
    bool eop();
    void run();
    void reset();
};

#endif
