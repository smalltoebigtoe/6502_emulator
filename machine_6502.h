#ifndef MACHINE_6502_H
#define MACHINE_6502_H

#include <iostream>
#include <vector>
#include <map>
#include <functional>

#include "cpu.h"
#include "memory.h"
#include "data.h"
#include "debug.h"

class Machine_6502 {
  private:
    CPU* m_cpu;
    Memory* m_module;

    Word m_instruction_address;
    Word m_instruction_size;

    typedef std::function<void(Machine_6502&)> OpcodeFn;
    std::map<Byte, OpcodeFn> handlers;
  public:
    Machine_6502();

    void init_handlers();
    CPU& get_cpu();
    Memory& get_module();
    Byte read_program_byte();
    void load(const std::vector<Byte> instructions, Word address);
    void execute(Machine_6502& machine);
    void reset();
    bool is_eop();

    uint8_t get_zpg_address();
    uint8_t get_zpgx_address();
    uint8_t get_zpgy_address();

    uint16_t get_abs_address();
    uint16_t get_absx_address();
    uint16_t get_absy_address();

    uint16_t get_ind_address();
    uint16_t get_indx_address();
    uint16_t get_indy_address();

    void cmp(CPU& cpu, Byte reg, Byte value);
    void cmp_im(Machine_6502& machine);
    void cmp_zp(Machine_6502& machine);
    void cmp_zpx(Machine_6502& machine);
    void cmp_abs(Machine_6502& machine);
    void cmp_absx(Machine_6502& machine);
    void cmp_absy(Machine_6502& machine);
    void cmp_inx(Machine_6502& machine);
    void cmp_iny(Machine_6502& machine);
};

#endif
