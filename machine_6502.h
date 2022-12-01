#ifndef MACHINE_6502_H
#define MACHINE_6502_H

#include <iostream>
#include <vector>
#include <map>
#include <functional>

#include "cpu.h"
#include "memory.h"
#include "data.h"

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

    void inc(uint16_t address);
    void inc_zp(Machine_6502& machine);
    void inc_zpx(Machine_6502& machine);
    void inc_abs(Machine_6502& machine);
    void inc_absx(Machine_6502& machine);

    void dec(uint16_t address);
    void dec_zp(Machine_6502& machine);
    void dec_zpx(Machine_6502& machine);
    void dec_abs(Machine_6502& machine);
    void dec_absx(Machine_6502& machine);

    void _and(CPU& cpu, Byte value);
    void and_imm(Machine_6502& machine);
    void and_zp(Machine_6502& machine);
    void and_zpx(Machine_6502& machine);
    void and_abs(Machine_6502& machine);
    void and_absx(Machine_6502& machine);
    void and_absy(Machine_6502& machine);
    void and_inx(Machine_6502& machine);
    void and_iny(Machine_6502& machine);

    void eor(CPU& cpu, Byte value);
    void eor_imm(Machine_6502& machine);
    void eor_zp(Machine_6502& machine);
    void eor_zpx(Machine_6502& machine);
    void eor_abs(Machine_6502& machine);
    void eor_absx(Machine_6502& machine);
    void eor_absy(Machine_6502& machine);
    void eor_inx(Machine_6502& machine);
    void eor_iny(Machine_6502& machine);

    void ora(CPU& cpu, Byte value);
    void ora_imm(Machine_6502& machine);
    void ora_zp(Machine_6502& machine);
    void ora_zpx(Machine_6502& machine);
    void ora_abs(Machine_6502& machine);
    void ora_absx(Machine_6502& machine);
    void ora_absy(Machine_6502& machine);
    void ora_inx(Machine_6502& machine);
    void ora_iny(Machine_6502& machine);

    void lda(CPU& cpu, Byte value);
    void lda_imm(Machine_6502& machine);
    void lda_zp(Machine_6502& machine);
    void lda_zpx(Machine_6502& machine);
    void lda_abs(Machine_6502& machine);
    void lda_absx(Machine_6502& machine);
    void lda_absy(Machine_6502& machine);
    void lda_inx(Machine_6502& machine);
    void lda_iny(Machine_6502& machine);

    void ldx(CPU& cpu, Byte value);
    void ldx_imm(Machine_6502& machine);
    void ldx_zp(Machine_6502& machine);
    void ldx_zpy(Machine_6502& machine);
    void ldx_abs(Machine_6502& machine);
    void ldx_absy(Machine_6502& machine);

    void ldy(CPU& cpu, Byte value);
    void ldy_imm(Machine_6502& machine);
    void ldy_zp(Machine_6502& machine);
    void ldy_zpx(Machine_6502& machine);
    void ldy_abs(Machine_6502& machine);
    void ldy_absx(Machine_6502& machine);

    void cmp(CPU& cpu, Byte reg, Byte value);
    void cmp_imm(Machine_6502& machine);
    void cmp_zp(Machine_6502& machine);
    void cmp_zpx(Machine_6502& machine);
    void cmp_abs(Machine_6502& machine);
    void cmp_absx(Machine_6502& machine);
    void cmp_absy(Machine_6502& machine);
    void cmp_inx(Machine_6502& machine);
    void cmp_iny(Machine_6502& machine);

    uint8_t get_zpg_address();
    uint8_t get_zpgx_address();
    uint8_t get_zpgy_address();
    uint16_t get_abs_address();
    uint16_t get_absx_address();
    uint16_t get_absy_address();
    uint16_t get_ind_address();
    uint16_t get_indx_address();
    uint16_t get_indy_address();
};

#endif
