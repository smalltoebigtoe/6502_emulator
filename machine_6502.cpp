#include "machine_6502.h"

#include "debug.h"

Machine_6502::Machine_6502()
  : m_instruction_address{ 0 }, m_instruction_size{ 0 } {
  CPU cpu;
  Memory memory;
  Stack stack;
  cpu.reset();
  memory.reset();
  stack.init_stack();
  m_cpu = &cpu;
  m_module = &memory;
  m_stack = &stack;
  init_handlers();
}

using namespace std::placeholders;
void Machine_6502::init_handlers() {
  /* BRANCH INSTRUCTIONS */
  std::function<void(Machine_6502& machine)> bcs =
    std::bind(&Machine_6502::bcs, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> bcc =
    std::bind(&Machine_6502::bcc, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> beq =
    std::bind(&Machine_6502::beq, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> bne =
    std::bind(&Machine_6502::bne, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> bpl =
    std::bind(&Machine_6502::bpl, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> bmi =
    std::bind(&Machine_6502::bmi, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> bvs =
    std::bind(&Machine_6502::bvs, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> bvc =
    std::bind(&Machine_6502::bvc, this, std::placeholders::_1);

  /* OTHER INSTRUCTIONS */
  std::function<void(Machine_6502& machine)> brk_imp =
    std::bind(&Machine_6502::brk_imp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> nop_imp =
    std::bind(&Machine_6502::nop_imp, this, std::placeholders::_1);

  /* STACK INSTRUCTIONS */
  std::function<void(Machine_6502& machine)> pha =
    std::bind(&Machine_6502::pha, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> php =
    std::bind(&Machine_6502::php, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> txs =
    std::bind(&Machine_6502::txs, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> pla =
    std::bind(&Machine_6502::pla, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> tsx =
    std::bind(&Machine_6502::tsx, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> plp =
    std::bind(&Machine_6502::plp, this, std::placeholders::_1);

  /* JUMP INSTRUCTIONS */
  std::function<void(Machine_6502& machine)> jmp_abs =
    std::bind(&Machine_6502::jmp_abs, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> jmp_in =
    std::bind(&Machine_6502::jmp_in, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> jsr_abs =
    std::bind(&Machine_6502::jsr_abs, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> rts_imp =
    std::bind(&Machine_6502::rts_imp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> rti_imp =
    std::bind(&Machine_6502::rti_imp, this, std::placeholders::_1);

  /* COMPARE INSTRUCTIONS */
  std::function<void(Machine_6502& machine)> bit_zp =
    std::bind(&Machine_6502::bit_zp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> bit_abs =
    std::bind(&Machine_6502::bit_abs, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> cmp_imm =
    std::bind(&Machine_6502::cmp_imm, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> cmp_zp =
    std::bind(&Machine_6502::cmp_zp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> cmp_zpx =
    std::bind(&Machine_6502::cmp_zpx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> cmp_abs =
    std::bind(&Machine_6502::cmp_abs, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> cmp_absx =
    std::bind(&Machine_6502::cmp_absx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> cmp_absy =
    std::bind(&Machine_6502::cmp_absy, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> cmp_inx =
    std::bind(&Machine_6502::cmp_inx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> cmp_iny =
    std::bind(&Machine_6502::cmp_iny, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> cmpx_imm =
    std::bind(&Machine_6502::cmpx_imm, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> cmpx_zp =
    std::bind(&Machine_6502::cmpx_zp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> cmpx_abs =
    std::bind(&Machine_6502::cmpx_abs, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> cmpy_imm =
    std::bind(&Machine_6502::cmpy_imm, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> cmpy_zp =
    std::bind(&Machine_6502::cmpy_zp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> cmpy_abs =
    std::bind(&Machine_6502::cmpy_abs, this, std::placeholders::_1);

  /* MATH INSTRUCTIONS */
  std::function<void(Machine_6502& machine)> adc_imm =
    std::bind(&Machine_6502::adc_imm, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> adc_zp =
    std::bind(&Machine_6502::adc_zp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> adc_zpx =
    std::bind(&Machine_6502::adc_zpx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> adc_abs =
    std::bind(&Machine_6502::adc_abs, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> adc_absx =
    std::bind(&Machine_6502::adc_absx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> adc_absy =
    std::bind(&Machine_6502::adc_absy, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> adc_inx =
    std::bind(&Machine_6502::adc_inx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> adc_iny =
    std::bind(&Machine_6502::adc_iny, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> sbc_imm =
    std::bind(&Machine_6502::sbc_imm, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> sbc_zp =
    std::bind(&Machine_6502::sbc_zp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> sbc_zpx =
    std::bind(&Machine_6502::sbc_zpx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> sbc_abs =
    std::bind(&Machine_6502::sbc_abs, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> sbc_absx =
    std::bind(&Machine_6502::sbc_absx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> sbc_absy =
    std::bind(&Machine_6502::sbc_absy, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> sbc_inx =
    std::bind(&Machine_6502::sbc_inx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> sbc_iny =
    std::bind(&Machine_6502::sbc_iny, this, std::placeholders::_1);

  /* FLAG INSTRUCTIONS */
  std::function<void(Machine_6502& machine)> clc =
    std::bind(&Machine_6502::clc, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> sec =
    std::bind(&Machine_6502::sec, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> cli =
    std::bind(&Machine_6502::cli, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> sei =
    std::bind(&Machine_6502::sei, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> clv =
    std::bind(&Machine_6502::clv, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> cld =
    std::bind(&Machine_6502::cld, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> sed =
    std::bind(&Machine_6502::sed, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> tax =
    std::bind(&Machine_6502::tax, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> txa =
    std::bind(&Machine_6502::txa, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> dex =
    std::bind(&Machine_6502::dex, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> inx =
    std::bind(&Machine_6502::inx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> tay =
    std::bind(&Machine_6502::tay, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> tya =
    std::bind(&Machine_6502::tya, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> dey =
    std::bind(&Machine_6502::dey, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> iny =
    std::bind(&Machine_6502::iny, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> lsr_a =
    std::bind(&Machine_6502::lsr_a, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> lsr_zp =
    std::bind(&Machine_6502::lsr_zp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> lsr_zpx =
    std::bind(&Machine_6502::lsr_zpx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> lsr_abs =
    std::bind(&Machine_6502::lsr_abs, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> lsr_absx =
    std::bind(&Machine_6502::lsr_absx, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> asl_a =
    std::bind(&Machine_6502::asl_a, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> asl_zp =
    std::bind(&Machine_6502::asl_zp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> asl_zpx =
    std::bind(&Machine_6502::asl_zpx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> asl_abs =
    std::bind(&Machine_6502::asl_abs, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> asl_absx =
    std::bind(&Machine_6502::asl_absx, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> rol_a =
    std::bind(&Machine_6502::rol_a, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> rol_zp =
    std::bind(&Machine_6502::rol_zp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> rol_zpx =
    std::bind(&Machine_6502::rol_zpx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> rol_abs =
    std::bind(&Machine_6502::rol_abs, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> rol_absx =
    std::bind(&Machine_6502::rol_absx, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> ror_a =
    std::bind(&Machine_6502::ror_a, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> ror_zp =
    std::bind(&Machine_6502::ror_zp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> ror_zpx =
    std::bind(&Machine_6502::ror_zpx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> ror_abs =
    std::bind(&Machine_6502::ror_abs, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> ror_absx =
    std::bind(&Machine_6502::ror_absx, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> inc_zp =
    std::bind(&Machine_6502::inc_zp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> inc_zpx =
    std::bind(&Machine_6502::inc_zpx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> inc_abs =
    std::bind(&Machine_6502::inc_abs, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> inc_absx =
    std::bind(&Machine_6502::inc_absx, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> dec_zp =
    std::bind(&Machine_6502::dec_zp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> dec_zpx =
    std::bind(&Machine_6502::dec_zpx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> dec_abs =
    std::bind(&Machine_6502::dec_abs, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> dec_absx =
    std::bind(&Machine_6502::dec_absx, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> and_imm =
    std::bind(&Machine_6502::and_imm, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> and_zp =
    std::bind(&Machine_6502::and_zp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> and_zpx =
    std::bind(&Machine_6502::and_zpx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> and_abs =
    std::bind(&Machine_6502::and_abs, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> and_absx =
    std::bind(&Machine_6502::and_absx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> and_absy =
    std::bind(&Machine_6502::and_absy, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> and_inx =
    std::bind(&Machine_6502::and_inx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> and_iny =
    std::bind(&Machine_6502::and_iny, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> eor_imm =
    std::bind(&Machine_6502::eor_imm, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> eor_zp =
    std::bind(&Machine_6502::eor_zp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> eor_zpx =
    std::bind(&Machine_6502::eor_zpx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> eor_abs =
    std::bind(&Machine_6502::eor_abs, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> eor_absx =
    std::bind(&Machine_6502::eor_absx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> eor_absy =
    std::bind(&Machine_6502::eor_absy, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> eor_inx =
    std::bind(&Machine_6502::eor_inx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> eor_iny =
    std::bind(&Machine_6502::eor_iny, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> ora_imm =
    std::bind(&Machine_6502::ora_imm, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> ora_zp =
    std::bind(&Machine_6502::ora_zp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> ora_zpx =
      std::bind(&Machine_6502::ora_zpx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> ora_abs =
      std::bind(&Machine_6502::ora_abs, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> ora_absx =
      std::bind(&Machine_6502::ora_absx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> ora_absy =
      std::bind(&Machine_6502::ora_absy, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> ora_inx =
      std::bind(&Machine_6502::ora_inx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> ora_iny =
      std::bind(&Machine_6502::ora_iny, this, std::placeholders::_1);

  /* MEMORY INSTRUCTIONS */
  std::function<void(Machine_6502& machine)> lda_imm =
    std::bind(&Machine_6502::lda_imm, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> lda_zp =
    std::bind(&Machine_6502::lda_zp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> lda_zpx =
    std::bind(&Machine_6502::lda_zpx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> lda_abs =
    std::bind(&Machine_6502::lda_abs, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> lda_absx =
    std::bind(&Machine_6502::lda_absx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> lda_absy =
    std::bind(&Machine_6502::lda_absy, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> lda_inx =
    std::bind(&Machine_6502::lda_inx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> lda_iny =
    std::bind(&Machine_6502::lda_iny, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> ldx_imm =
    std::bind(&Machine_6502::ldx_imm, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> ldx_zp =
    std::bind(&Machine_6502::ldx_zp, this, std::placeholders::_1);
   std::function<void(Machine_6502& machine)> ldx_zpy =
    std::bind(&Machine_6502::ldx_zpy, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> ldx_abs =
    std::bind(&Machine_6502::ldx_abs, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> ldx_absy =
    std::bind(&Machine_6502::ldx_absy, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> ldy_imm =
    std::bind(&Machine_6502::ldy_imm, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> ldy_zp =
    std::bind(&Machine_6502::ldy_zp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> ldy_zpx =
    std::bind(&Machine_6502::ldy_zpx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> ldy_abs =
    std::bind(&Machine_6502::ldy_abs, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> ldy_absx =
    std::bind(&Machine_6502::ldy_absx, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> sta_zp =
    std::bind(&Machine_6502::sta_zp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> sta_zpx =
    std::bind(&Machine_6502::sta_zpx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> sta_abs =
    std::bind(&Machine_6502::sta_abs, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> sta_absx =
    std::bind(&Machine_6502::sta_absx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> sta_absy =
    std::bind(&Machine_6502::sta_absy, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> sta_inx =
    std::bind(&Machine_6502::sta_inx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> sta_iny =
    std::bind(&Machine_6502::sta_iny, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> stx_zp =
    std::bind(&Machine_6502::stx_zp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> stx_zpy =
    std::bind(&Machine_6502::stx_zpy, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> stx_abs =
    std::bind(&Machine_6502::stx_abs, this, std::placeholders::_1);

  std::function<void(Machine_6502& machine)> sty_zp =
    std::bind(&Machine_6502::sty_zp, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> sty_zpx =
    std::bind(&Machine_6502::sty_zpx, this, std::placeholders::_1);
  std::function<void(Machine_6502& machine)> sty_abs =
    std::bind(&Machine_6502::sty_abs, this, std::placeholders::_1);

  /* BRANCH INSTRUCTIONS */
  handlers.insert(std::make_pair(0xB0, bcs));
  handlers.insert(std::make_pair(0x90, bcc));

  handlers.insert(std::make_pair(0xF0, beq));
  handlers.insert(std::make_pair(0xD0, bne));

  handlers.insert(std::make_pair(0x10, bpl));
  handlers.insert(std::make_pair(0x30, bmi));

  handlers.insert(std::make_pair(0x70, bvs));
  handlers.insert(std::make_pair(0x50, bvc));

  /* OTHER INSTRUCTIONS */
  handlers.insert(std::make_pair(0x00, brk_imp));
  handlers.insert(std::make_pair(0xEA, nop_imp));

  /* STACK INSTRUCTIONS */
  handlers.insert(std::make_pair(0x48, pha));
  handlers.insert(std::make_pair(0x08, php));
  handlers.insert(std::make_pair(0x9A, txs));

  handlers.insert(std::make_pair(0x68, pla));
  handlers.insert(std::make_pair(0xBA, tsx));

  handlers.insert(std::make_pair(0x28, plp));

  /* JUMP INSTRUCTIONS */
  handlers.insert(std::make_pair(0x4C, jmp_abs));
  handlers.insert(std::make_pair(0x6C, jmp_in));

  handlers.insert(std::make_pair(0x20, jsr_abs));
  handlers.insert(std::make_pair(0x60, rts_imp));
  handlers.insert(std::make_pair(0x40, rti_imp));

  /* COMPARE INSTRUCTIONS */
  handlers.insert(std::make_pair(0x24, bit_zp));
  handlers.insert(std::make_pair(0x2C, bit_abs));

  handlers.insert(std::make_pair(0xC9, cmp_imm));
  handlers.insert(std::make_pair(0xC5, cmp_zp));
  handlers.insert(std::make_pair(0xD5, cmp_zpx));
  handlers.insert(std::make_pair(0xCD, cmp_abs));
  handlers.insert(std::make_pair(0xDD, cmp_absx));
  handlers.insert(std::make_pair(0xD9, cmp_absy));
  handlers.insert(std::make_pair(0xC1, cmp_inx));
  handlers.insert(std::make_pair(0xD1, cmp_iny));

  handlers.insert(std::make_pair(0xE0, cmpx_imm));
  handlers.insert(std::make_pair(0xE4, cmpx_zp));
  handlers.insert(std::make_pair(0xEC, cmpx_abs));

  handlers.insert(std::make_pair(0xC0, cmpy_imm));
  handlers.insert(std::make_pair(0xC4, cmpy_zp));
  handlers.insert(std::make_pair(0xCC, cmpy_abs));

  /* MATH INSTRUCTIONS */
  handlers.insert(std::make_pair(0x69, adc_imm));
  handlers.insert(std::make_pair(0x65, adc_zp));
  handlers.insert(std::make_pair(0x75, adc_zpx));
  handlers.insert(std::make_pair(0x6D, adc_abs));
  handlers.insert(std::make_pair(0x7D, adc_absx));
  handlers.insert(std::make_pair(0x79, adc_absy));
  handlers.insert(std::make_pair(0x61, adc_inx));
  handlers.insert(std::make_pair(0x71, adc_iny));

  handlers.insert(std::make_pair(0xE9, sbc_imm));
  handlers.insert(std::make_pair(0xE5, sbc_zp));
  handlers.insert(std::make_pair(0xF5, sbc_zpx));
  handlers.insert(std::make_pair(0xED, sbc_abs));
  handlers.insert(std::make_pair(0xFD, sbc_absx));
  handlers.insert(std::make_pair(0xF9, sbc_absy));
  handlers.insert(std::make_pair(0xE1, sbc_inx));
  handlers.insert(std::make_pair(0xF1, sbc_iny));

  /* BITWISE INSTRUCTIONS */
  handlers.insert(std::make_pair(0x18, clc));
  handlers.insert(std::make_pair(0x38, sec));
  handlers.insert(std::make_pair(0x58, cli));
  handlers.insert(std::make_pair(0x78, sei));
  handlers.insert(std::make_pair(0xB8, clv));
  handlers.insert(std::make_pair(0xD8, cld));
  handlers.insert(std::make_pair(0xF8, sed));

  handlers.insert(std::make_pair(0xAA, tax));
  handlers.insert(std::make_pair(0x8A, txa));
  handlers.insert(std::make_pair(0xCA, dex));
  handlers.insert(std::make_pair(0xE8, inx));
  handlers.insert(std::make_pair(0xA8, tay));
  handlers.insert(std::make_pair(0x98, tya));
  handlers.insert(std::make_pair(0x88, dey));
  handlers.insert(std::make_pair(0xC8, iny));

  handlers.insert(std::make_pair(0x4A, lsr_a));
  handlers.insert(std::make_pair(0x46, lsr_zp));
  handlers.insert(std::make_pair(0x56, lsr_zpx));
  handlers.insert(std::make_pair(0x4E, lsr_abs));
  handlers.insert(std::make_pair(0x5E, lsr_absx));

  handlers.insert(std::make_pair(0x0A, asl_a));
  handlers.insert(std::make_pair(0x06, asl_zp));
  handlers.insert(std::make_pair(0x16, asl_zpx));
  handlers.insert(std::make_pair(0x0E, asl_abs));
  handlers.insert(std::make_pair(0x1E, asl_absx));

  handlers.insert(std::make_pair(0x2A, rol_a));
  handlers.insert(std::make_pair(0x26, rol_zp));
  handlers.insert(std::make_pair(0x36, rol_zpx));
  handlers.insert(std::make_pair(0x2E, rol_abs));
  handlers.insert(std::make_pair(0x3E, rol_absx));

  handlers.insert(std::make_pair(0x6A, ror_a));
  handlers.insert(std::make_pair(0x66, ror_zp));
  handlers.insert(std::make_pair(0x76, ror_zpx));
  handlers.insert(std::make_pair(0x6E, ror_abs));
  handlers.insert(std::make_pair(0x7E, ror_absx));

  handlers.insert(std::make_pair(0x29, and_imm));
  handlers.insert(std::make_pair(0x25, and_zp));
  handlers.insert(std::make_pair(0x35, and_zpx));
  handlers.insert(std::make_pair(0x2D, and_abs));
  handlers.insert(std::make_pair(0x3D, and_absx));
  handlers.insert(std::make_pair(0x39, and_absy));
  handlers.insert(std::make_pair(0x21, and_inx));
  handlers.insert(std::make_pair(0x31, and_iny));

  handlers.insert(std::make_pair(0x49, eor_imm));
  handlers.insert(std::make_pair(0x45, eor_zp));
  handlers.insert(std::make_pair(0x55, eor_zpx));
  handlers.insert(std::make_pair(0x4D, eor_abs));
  handlers.insert(std::make_pair(0x5D, eor_absx));
  handlers.insert(std::make_pair(0x59, eor_absy));
  handlers.insert(std::make_pair(0x41, eor_inx));
  handlers.insert(std::make_pair(0x51, eor_iny));

  handlers.insert(std::make_pair(0x09, ora_imm));
  handlers.insert(std::make_pair(0x05, ora_zp));
  handlers.insert(std::make_pair(0x15, ora_zpx));
  handlers.insert(std::make_pair(0x0D, ora_abs));
  handlers.insert(std::make_pair(0x1D, ora_absx));
  handlers.insert(std::make_pair(0x19, ora_absy));
  handlers.insert(std::make_pair(0x01, ora_inx));
  handlers.insert(std::make_pair(0x11, ora_iny));

  /* MEMORY INSTRUCTIONS */
  handlers.insert(std::make_pair(0xA9, lda_imm));
  handlers.insert(std::make_pair(0xA5, lda_zp));
  handlers.insert(std::make_pair(0xB5, lda_zpx));
  handlers.insert(std::make_pair(0xAD, lda_abs));
  handlers.insert(std::make_pair(0xBD, lda_absx));
  handlers.insert(std::make_pair(0xB9, lda_absy));
  handlers.insert(std::make_pair(0xA1, lda_inx));
  handlers.insert(std::make_pair(0xB1, lda_iny));

  handlers.insert(std::make_pair(0xA2, ldx_imm));
  handlers.insert(std::make_pair(0xA6, ldx_zp));
  handlers.insert(std::make_pair(0xB6, ldx_zpy));
  handlers.insert(std::make_pair(0xAE, ldx_abs));
  handlers.insert(std::make_pair(0xBE, ldx_absy));

  handlers.insert(std::make_pair(0xA0, ldy_imm));
  handlers.insert(std::make_pair(0xA4, ldy_zp));
  handlers.insert(std::make_pair(0xB4, ldy_zpx));
  handlers.insert(std::make_pair(0xAC, ldy_abs));
  handlers.insert(std::make_pair(0xBC, ldy_absx));

  handlers.insert(std::make_pair(0xE6, inc_zp));
  handlers.insert(std::make_pair(0xF6, inc_zpx));
  handlers.insert(std::make_pair(0xEE, inc_abs));
  handlers.insert(std::make_pair(0xFE, inc_absx));

  handlers.insert(std::make_pair(0xC6, dec_zp));
  handlers.insert(std::make_pair(0xD6, dec_zpx));
  handlers.insert(std::make_pair(0xCE, dec_abs));
  handlers.insert(std::make_pair(0xDE, dec_absx));

  handlers.insert(std::make_pair(0x85, sta_zp));
  handlers.insert(std::make_pair(0x95, sta_zpx));
  handlers.insert(std::make_pair(0x8D, sta_abs));
  handlers.insert(std::make_pair(0x9D, sta_absx));
  handlers.insert(std::make_pair(0x99, sta_absy));
  handlers.insert(std::make_pair(0x81, sta_inx));
  handlers.insert(std::make_pair(0x91, sta_iny));

  handlers.insert(std::make_pair(0x86, stx_zp));
  handlers.insert(std::make_pair(0x96, stx_zpy));
  handlers.insert(std::make_pair(0x8E, stx_abs));

  handlers.insert(std::make_pair(0x84, sty_zp));
  handlers.insert(std::make_pair(0x94, sty_zpx));
  handlers.insert(std::make_pair(0x8C, sty_abs));
}

/* BRANCH INSTRUCTIONS */
void Machine_6502::bcs(Machine_6502& machine) {
  auto jump = machine.read_program_byte();
  if (machine.get_cpu().CF)
    machine.get_cpu().PC += jump;
}
void Machine_6502::bcc(Machine_6502& machine) {
  auto jump = machine.read_program_byte();
  if (!machine.get_cpu().CF)
    machine.get_cpu().PC += jump;
}
void Machine_6502::beq(Machine_6502& machine) {
  auto jump = machine.read_program_byte();
  if (machine.get_cpu().ZF)
    machine.get_cpu().PC += jump;
}
void Machine_6502::bne(Machine_6502& machine) {
  auto jump = machine.read_program_byte();
  if (!machine.get_cpu().NF)
    machine.get_cpu().PC += jump;
}
void Machine_6502::bpl(Machine_6502& machine) {
  auto jump = machine.read_program_byte();
  if (!machine.get_cpu().NF)
    machine.get_cpu().PC += jump;
}
void Machine_6502::bmi(Machine_6502& machine) {
  auto jump = machine.read_program_byte();
  if (machine.get_cpu().NF)
    machine.get_cpu().PC += jump;
}
void Machine_6502::bvs(Machine_6502& machine) {
  auto jump = machine.read_program_byte();
  if (machine.get_cpu().OFF)
    machine.get_cpu().PC += jump;
}
void Machine_6502::bvc(Machine_6502& machine) {
  auto jump = machine.read_program_byte();
  if (!machine.get_cpu().OFF)
    machine.get_cpu().PC += jump;
}

/* OTHER INSTRUCTIONS */
void Machine_6502::brk_imp(Machine_6502& machine) {
  machine.get_cpu().BCF = true;
  machine.get_cpu().PC++;
}
void Machine_6502::nop_imp(Machine_6502& machine) {;}

/* STACK INSTRUCTIONS */
void Machine_6502::pha(Machine_6502& machine) {
  machine.get_stack().push(machine.get_cpu().A); }
void Machine_6502::php(Machine_6502& machine) {
  machine.get_stack().push(machine.get_cpu().processor_status); }
void Machine_6502::txs(Machine_6502& machine) {
  auto value = machine.get_cpu().X;
  machine.get_cpu().processor_status = value;
  // does not change ZF, NF flags
}
void Machine_6502::pla(Machine_6502& machine) {
  auto value = machine.get_stack().pop();
  machine.get_cpu().A = value;
  machine.get_cpu().ZF = (value == 0);
  machine.get_cpu().NF = ((value & 0x80) == 0x80);
}
void Machine_6502::tsx(Machine_6502& machine) {
  auto value = machine.get_cpu().SP;
  machine.get_cpu().X = value;
  machine.get_cpu().ZF = (value == 0);
  machine.get_cpu().NF = ((value & 0x80) == 0x80);
}
void Machine_6502::plp(Machine_6502& machine) {
  machine.get_cpu().processor_status = machine.get_stack().pop(); }

/* JUMP INSTRUCTIONS */
void Machine_6502::jmp_abs(Machine_6502& machine) {
  uint16_t address = machine.get_abs_address();
  machine.get_cpu().PC = address;
}
void Machine_6502::jmp_in(Machine_6502& machine) {
  uint16_t address = machine.get_ind_address();
  machine.get_cpu().PC = address;
}

void Machine_6502::jsr_abs(Machine_6502& machine) {
  uint16_t address = machine.get_abs_address();
  uint16_t pc = machine.get_cpu().PC;
  machine.get_stack().push(pc >> 8);
  machine.get_stack().push(pc);
  machine.get_cpu().PC = address;
}
void Machine_6502::rts_imp(Machine_6502& machine) {
  auto low_byte = machine.get_stack().pop();
  auto high_byte = machine.get_stack().pop();
  uint16_t ret_adr = (high_byte << 8) + low_byte;
  machine.get_cpu().PC = ret_adr;
}
void Machine_6502::rti_imp(Machine_6502& machine) {
  ;
}

/* COMPARE INSTRUCTIONS */
void Machine_6502::bit(Machine_6502& machine, uint16_t address) {
  auto cpu_a = machine.get_cpu().A;
  auto mem = machine.get_module().get_at(address);
  machine.get_cpu().ZF = ((cpu_a & mem) == 0);
  machine.get_cpu().NF = ((mem & 0x80) == 0x80);
  machine.get_cpu().OFF = ((mem & 0x40) == 0x40);
}
void Machine_6502::bit_zp(Machine_6502& machine) {
  bit(machine, get_zpg_address()); }
void Machine_6502::bit_abs(Machine_6502& machine) {
  bit(machine, get_abs_address()); }

void Machine_6502::cmp(Machine_6502& machine, Byte value) {
  Byte reg_val = machine.get_cpu().A;
  uint8_t result = reg_val - value;
  machine.get_cpu().CF = false;
  machine.get_cpu().ZF = false;
  if (reg_val >= value)
    machine.get_cpu().CF = true;
  if (reg_val == value)
    machine.get_cpu().ZF = true;
  if ((result & 0x80) == 0x80)
    machine.get_cpu().NF = true;
}
void Machine_6502::cmp_imm(Machine_6502& machine) {
  cmp(machine, machine.read_program_byte()); }
void Machine_6502::cmp_zp(Machine_6502& machine) {
  cmp(machine, machine.get_module().get_at(machine.get_zpg_address())); }
void Machine_6502::cmp_zpx(Machine_6502& machine) {
  cmp(machine, machine.get_module().get_at(machine.get_zpgx_address())); }
void Machine_6502::cmp_abs(Machine_6502& machine) {
  cmp(machine, machine.get_module().get_at(machine.get_abs_address())); }
void Machine_6502::cmp_absx(Machine_6502& machine) {
  cmp(machine, machine.get_module().get_at(machine.get_absx_address())); }
void Machine_6502::cmp_absy(Machine_6502& machine) {
  cmp(machine, machine.get_module().get_at(machine.get_absy_address())); }
void Machine_6502::cmp_inx(Machine_6502& machine) {
  cmp(machine, machine.get_module().get_at(machine.get_indx_address())); }
void Machine_6502::cmp_iny(Machine_6502& machine) {
  cmp(machine, machine.get_module().get_at(machine.get_indy_address())); }

void Machine_6502::cmpx(Machine_6502& machine, Byte value) {
  Byte reg_val = machine.get_cpu().X;
  uint8_t result = reg_val - value;
  machine.get_cpu().CF = false;
  machine.get_cpu().ZF = false;
  if (reg_val >= value)
    machine.get_cpu().CF = true;
  if (reg_val == value)
    machine.get_cpu().ZF = true;
  if ((result & 0x80) == 0x80)
    machine.get_cpu().NF = true;
}
void Machine_6502::cmpx_imm(Machine_6502& machine) {
  cmp(machine, machine.read_program_byte()); }
void Machine_6502::cmpx_zp(Machine_6502& machine) {
  cmp(machine, machine.get_module().get_at(machine.get_zpg_address())); }
void Machine_6502::cmpx_abs(Machine_6502& machine) {
  cmp(machine, machine.get_module().get_at(machine.get_abs_address())); }

void Machine_6502::cmpy(Machine_6502& machine, Byte value) {
  Byte reg_val = machine.get_cpu().Y;
  uint8_t result = reg_val - value;
  machine.get_cpu().CF = false;
  machine.get_cpu().ZF = false;
  if (reg_val >= value)
    machine.get_cpu().CF = true;
  if (reg_val == value)
    machine.get_cpu().ZF = true;
  if ((result & 0x80) == 0x80)
    machine.get_cpu().NF = true;
}
void Machine_6502::cmpy_imm(Machine_6502& machine) {
  cmp(machine, machine.read_program_byte()); }
void Machine_6502::cmpy_zp(Machine_6502& machine) {
  cmp(machine, machine.get_module().get_at(machine.get_zpg_address())); }
void Machine_6502::cmpy_abs(Machine_6502& machine) {
  cmp(machine, machine.get_module().get_at(machine.get_abs_address())); }

/* MATH INSTRUCTIONS */
void Machine_6502::adc(Machine_6502& machine, Byte value) {
  auto init_a = machine.get_cpu().A;
  // can go above 8 bits
  uint16_t result = init_a + value;
  if (machine.get_cpu().CF)
    result += 1;

  machine.get_cpu().A = result;
  auto a = machine.get_cpu().A;

  machine.get_cpu().ZF = (a == 0);
  machine.get_cpu().NF = ((a & 0x80) == 0x80);
  machine.get_cpu().CF = (result > 0xFF);
  machine.get_cpu().OFF = (
    (value < 0x7F && init_a < 0x7F && a > 0x7F) ||
    (value > 0x7F && init_a > 0x7F && a < 0x7F));
}
void Machine_6502::adc_imm(Machine_6502& machine) {
  adc(machine, read_program_byte()); }
void Machine_6502::adc_zp(Machine_6502& machine) {
  adc(machine, get_zpg_address()); }
void Machine_6502::adc_zpx(Machine_6502& machine) {
  adc(machine, get_zpgx_address()); }
void Machine_6502::adc_abs(Machine_6502& machine) {
  adc(machine, get_abs_address()); }
void Machine_6502::adc_absx(Machine_6502& machine) {
  adc(machine, get_absx_address()); }
void Machine_6502::adc_absy(Machine_6502& machine) {
  adc(machine, get_absy_address()); }
void Machine_6502::adc_inx(Machine_6502& machine) {
  adc(machine, get_indx_address()); }
void Machine_6502::adc_iny(Machine_6502& machine) {
  adc(machine, get_indy_address()); }

void Machine_6502::sbc(Machine_6502& machine, uint16_t address) {
  auto value = machine.get_module().get_at(address);
  uint8_t add = machine.get_cpu().CF ? 0 : 1;
  adc(machine, (0xFF ^ value) + add);
}
void Machine_6502::sbc_imm(Machine_6502& machine) {
  sbc(machine, machine.read_program_byte()); }
void Machine_6502::sbc_zp(Machine_6502& machine) {
  sbc(machine, machine.get_zpg_address()); }
void Machine_6502::sbc_zpx(Machine_6502& machine) {
  sbc(machine, machine.get_zpgx_address()); }
void Machine_6502::sbc_abs(Machine_6502& machine) {
  sbc(machine, machine.get_abs_address()); }
void Machine_6502::sbc_absx(Machine_6502& machine) {
  sbc(machine, machine.get_absx_address()); }
void Machine_6502::sbc_absy(Machine_6502& machine) {
  sbc(machine, machine.get_absy_address()); }
void Machine_6502::sbc_inx(Machine_6502& machine) {
  sbc(machine, machine.get_indx_address()); }
void Machine_6502::sbc_iny(Machine_6502& machine) {
  sbc(machine, machine.get_indy_address()); }

/* PROCESSOR STATUS (FLAG) INSTRUCTIONS */
void Machine_6502::clc(Machine_6502& machine) {
  machine.get_cpu().CF = false; }
void Machine_6502::sec(Machine_6502& machine) {
  machine.get_cpu().CF = true; }
void Machine_6502::cli(Machine_6502& machine) {
  machine.get_cpu().IDF = false; }
void Machine_6502::sei(Machine_6502& machine) {
  machine.get_cpu().IDF = true; }
void Machine_6502::clv(Machine_6502& machine) {
  machine.get_cpu().OFF = false; }
void Machine_6502::cld(Machine_6502& machine) {
  machine.get_cpu().DMF = false; }
void Machine_6502::sed(Machine_6502& machine) {
  machine.get_cpu().DMF = true; }

void Machine_6502::tax(Machine_6502& machine) {
  machine.get_cpu().X = machine.get_cpu().A; }
void Machine_6502::txa(Machine_6502& machine) {
  machine.get_cpu().A = machine.get_cpu().X; }
void Machine_6502::dex(Machine_6502& machine) {
  machine.get_cpu().X--; }
void Machine_6502::inx(Machine_6502& machine) {
  machine.get_cpu().X++; }
void Machine_6502::tay(Machine_6502& machine) {
  machine.get_cpu().Y = machine.get_cpu().A; }
void Machine_6502::tya(Machine_6502& machine) {
  machine.get_cpu().A = machine.get_cpu().Y; }
void Machine_6502::dey(Machine_6502& machine) {
  machine.get_cpu().Y--; }
void Machine_6502::iny(Machine_6502& machine) {
  machine.get_cpu().Y++; }

void Machine_6502::lsr(uint16_t address) {
  Byte value = m_module->get_at(address);
  bool shifted_out_bit = ((value & 0x01) != 0);
  shifted_out_bit >>= 1;
  m_cpu->CF = shifted_out_bit;

  Byte result = (m_module->get_at(address) >> 1);
  m_cpu->ZF = (result == 0);
  m_cpu->NF = ((result & 0x80) == 0x80);
  m_module->set_at(address, result);
}
void Machine_6502::lsr_a(Machine_6502& machine) {
  Byte value = m_cpu->A;
  bool shifted_out_bit = ((value & 0x01) != 0);
  shifted_out_bit >>= 1;
  m_cpu->CF = shifted_out_bit;

  Byte result = (m_cpu->A >> 1);
  m_cpu->ZF = (result == 0);
  m_cpu->NF = ((result & 0x80) == 0x80);
  m_cpu->A = result;
}
void Machine_6502::lsr_zp(Machine_6502& machine) {
  lsr(machine.get_zpg_address()); }
void Machine_6502::lsr_zpx(Machine_6502& machine) {
  lsr(machine.get_zpg_address()); }
void Machine_6502::lsr_abs(Machine_6502& machine) {
  lsr(machine.get_zpg_address()); }
void Machine_6502::lsr_absx(Machine_6502& machine) {
  lsr(machine.get_zpg_address()); }

void Machine_6502::_and(CPU& cpu, Byte value) {
  Byte result = (cpu.A & value);
  cpu.ZF = (result == 0);
  cpu.NF = ((value & 0x80) == 0x80);
  cpu.A = result;
}
void Machine_6502::and_imm(Machine_6502& machine) {
  _and(machine.get_cpu(), machine.get_module().get_at(machine.read_program_byte())); }
void Machine_6502::and_zp(Machine_6502& machine) {
  _and(machine.get_cpu(), machine.get_module().get_at(machine.get_zpg_address())); }
void Machine_6502::and_zpx(Machine_6502& machine) {
  _and(machine.get_cpu(), machine.get_module().get_at(machine.get_zpgx_address())); }
void Machine_6502::and_abs(Machine_6502& machine) {
  _and(machine.get_cpu(), machine.get_module().get_at(machine.get_absx_address())); }
void Machine_6502::and_absx(Machine_6502& machine) {
  _and(machine.get_cpu(), machine.get_module().get_at(machine.get_absy_address())); }
void Machine_6502::and_absy(Machine_6502& machine) {
  _and(machine.get_cpu(), machine.get_module().get_at(machine.get_indx_address())); }
void Machine_6502::and_inx(Machine_6502& machine) {
  _and(machine.get_cpu(), machine.get_module().get_at(machine.get_indx_address())); }
void Machine_6502::and_iny(Machine_6502& machine) {
  _and(machine.get_cpu(), machine.get_module().get_at(machine.get_indy_address())); }

void Machine_6502::eor(CPU& cpu, Byte value) {
  Byte result = (cpu.A ^ value);
  cpu.ZF = (result == 0);
  cpu.NF = ((value & 0x80) == 0x80);
  cpu.A = result;
}
void Machine_6502::eor_imm(Machine_6502& machine) {
  eor(machine.get_cpu(), machine.get_module().get_at(machine.read_program_byte())); }
void Machine_6502::eor_zp(Machine_6502& machine) {
  eor(machine.get_cpu(), machine.get_module().get_at(machine.get_zpg_address())); }
void Machine_6502::eor_zpx(Machine_6502& machine) {
  eor(machine.get_cpu(), machine.get_module().get_at(machine.get_zpgx_address())); }
void Machine_6502::eor_abs(Machine_6502& machine) {
  eor(machine.get_cpu(), machine.get_module().get_at(machine.get_absx_address())); }
void Machine_6502::eor_absx(Machine_6502& machine) {
  eor(machine.get_cpu(), machine.get_module().get_at(machine.get_absy_address())); }
void Machine_6502::eor_absy(Machine_6502& machine) {
  eor(machine.get_cpu(), machine.get_module().get_at(machine.get_indx_address())); }
void Machine_6502::eor_inx(Machine_6502& machine) {
  eor(machine.get_cpu(), machine.get_module().get_at(machine.get_indx_address())); }
void Machine_6502::eor_iny(Machine_6502& machine) {
  eor(machine.get_cpu(), machine.get_module().get_at(machine.get_indy_address())); }

void Machine_6502::ora(CPU& cpu, Byte value) {
  Byte result = (cpu.A || value);
  cpu.ZF = (result == 0);
  cpu.NF = ((value & 0x80) == 0x80);
  cpu.A = result;
}
void Machine_6502::ora_imm(Machine_6502& machine) {
  ora(machine.get_cpu(), machine.get_module().get_at(machine.read_program_byte())); }
void Machine_6502::ora_zp(Machine_6502& machine) {
  ora(machine.get_cpu(), machine.get_module().get_at(machine.get_zpg_address())); }
void Machine_6502::ora_zpx(Machine_6502& machine) {
  ora(machine.get_cpu(), machine.get_module().get_at(machine.get_zpgx_address())); }
void Machine_6502::ora_abs(Machine_6502& machine) {
  ora(machine.get_cpu(), machine.get_module().get_at(machine.get_absx_address())); }
void Machine_6502::ora_absx(Machine_6502& machine) {
  ora(machine.get_cpu(), machine.get_module().get_at(machine.get_absy_address())); }
void Machine_6502::ora_absy(Machine_6502& machine) {
  ora(machine.get_cpu(), machine.get_module().get_at(machine.get_indx_address())); }
void Machine_6502::ora_inx(Machine_6502& machine) {
  ora(machine.get_cpu(), machine.get_module().get_at(machine.get_indx_address())); }
void Machine_6502::ora_iny(Machine_6502& machine) {
  ora(machine.get_cpu(), machine.get_module().get_at(machine.get_indy_address())); }

void Machine_6502::asl(Machine_6502& machine, uint16_t address) {
  uint16_t result = machine.get_module().get_at(address) << 1;
  machine.get_cpu().A = result;
  machine.get_cpu().CF = ((result & 0x100) == 0x100);
  machine.get_cpu().ZF = (result == 0);
  machine.get_cpu().NF = ((result & 0x80) == 0x80);
}
void Machine_6502::asl_a(Machine_6502& machine) {
  uint16_t result = machine.get_cpu().A << 1;
  machine.get_cpu().A = result;
  machine.get_cpu().CF = ((result & 0x100) == 0x100);
  machine.get_cpu().ZF = (result == 0);
  machine.get_cpu().NF = ((result & 0x80) == 0x80);
}
void Machine_6502::asl_zp(Machine_6502& machine) {
  asl(machine, machine.get_zpg_address()); }
void Machine_6502::asl_zpx(Machine_6502& machine) {
  asl(machine, machine.get_zpgx_address()); }
void Machine_6502::asl_abs(Machine_6502& machine) {
  asl(machine, machine.get_abs_address()); }
void Machine_6502::asl_absx(Machine_6502& machine) {
  asl(machine, machine.get_absx_address()); }

void Machine_6502::rol(Machine_6502& machine, uint16_t address) {
  uint16_t result = machine.get_module().get_at(address) << 1;
  // if (m_cpu.carry) result += 1;
  result += 1;
  machine.get_module().set_at(address, result);
  machine.get_cpu().CF = ((result & 0x100) == 0x100);
  machine.get_cpu().ZF = (result == 0);
  machine.get_cpu().NF = ((result & 0x80) == 0x80);
}
void Machine_6502::rol_a(Machine_6502& machine) {
  uint16_t result = machine.get_cpu().A << 1;
  result += 1;
  machine.get_cpu().A = result;
  machine.get_cpu().CF = ((result & 0x100) == 0x100);
  machine.get_cpu().ZF = (result == 0);
  machine.get_cpu().NF = ((result & 0x80) == 0x80);
}
void Machine_6502::rol_zp(Machine_6502& machine) {
  rol(machine, machine.get_zpg_address()); }
void Machine_6502::rol_zpx(Machine_6502& machine) {
  rol(machine, machine.get_zpgx_address()); }
void Machine_6502::rol_abs(Machine_6502& machine) {
  rol(machine, machine.get_abs_address()); }
void Machine_6502::rol_absx(Machine_6502& machine) {
  rol(machine, machine.get_absx_address()); }

void Machine_6502::ror(Machine_6502& machine, uint16_t address) {
  uint8_t orig_val = machine.get_module().get_at(address);
  uint8_t result = orig_val >> 1;
  // if (m_cpu->is_carry) result += 0x80;
  result += 0x80;
  machine.get_module().set_at(address, result);
  machine.get_cpu().CF = ((orig_val & 1) == 1);
  machine.get_cpu().ZF = (result == 0);
  machine.get_cpu().NF = ((result & 0x80) == 0x80);
}
void Machine_6502::ror_a(Machine_6502& machine) {
  uint8_t orig_val = machine.get_cpu().A;
  uint8_t result = orig_val >> 1;
  // if (m_cpu->is_carry) result += 0x80;
  result += 0x80;
  machine.get_cpu().A = result;
  machine.get_cpu().CF = ((orig_val & 1) == 1);
  machine.get_cpu().ZF = (result == 0);
  machine.get_cpu().NF = ((result & 0x80) == 0x80);
}
void Machine_6502::ror_zp(Machine_6502& machine) {
  ror(machine, machine.get_zpg_address()); }
void Machine_6502::ror_zpx(Machine_6502& machine) {
  ror(machine, machine.get_zpgx_address()); }
void Machine_6502::ror_abs(Machine_6502& machine) {
  ror(machine, machine.get_abs_address()); }
void Machine_6502::ror_absx(Machine_6502& machine) {
  ror(machine, machine.get_absx_address()); }

/* MEMORY INSTRUCTIONS */
void Machine_6502::lda(CPU& cpu, Byte value) {
  cpu.A = value;
  cpu.NF = ((value & 0x80) == 0x80);
  cpu.ZF = (value == 0);
}
void Machine_6502::lda_imm(Machine_6502& machine) {
  lda(machine.get_cpu(), machine.read_program_byte()); }
void Machine_6502::lda_zp(Machine_6502& machine) {
  lda(machine.get_cpu(), machine.get_module().get_at(get_zpg_address())); }
void Machine_6502::lda_zpx(Machine_6502& machine) {
  lda(machine.get_cpu(), machine.get_module().get_at(get_zpgx_address())); }
void Machine_6502::lda_abs(Machine_6502& machine) {
  lda(machine.get_cpu(), machine.get_module().get_at(get_abs_address())); }
void Machine_6502::lda_absx(Machine_6502& machine) {
  lda(machine.get_cpu(), machine.get_module().get_at(get_absx_address())); }
void Machine_6502::lda_absy(Machine_6502& machine) {
  lda(machine.get_cpu(), machine.get_module().get_at(get_absy_address())); }
void Machine_6502::lda_inx(Machine_6502& machine) {
  lda(machine.get_cpu(), machine.get_module().get_at(get_indx_address())); }
void Machine_6502::lda_iny(Machine_6502& machine) {
  lda(machine.get_cpu(), machine.get_module().get_at(get_indy_address())); }

void Machine_6502::ldx(CPU& cpu, Byte value) {
  cpu.X = value;
  cpu.NF = ((value & 0x80) == 0x80);
  cpu.ZF = (value == 0);
}
void Machine_6502::ldx_imm(Machine_6502& machine) {
  ldx(machine.get_cpu(), machine.read_program_byte()); }
void Machine_6502::ldx_zp(Machine_6502& machine) {
  ldx(machine.get_cpu(), machine.get_module().get_at(get_zpg_address())); }
void Machine_6502::ldx_zpy(Machine_6502& machine) {
  ldx(machine.get_cpu(), machine.get_module().get_at(get_zpgy_address())); }
void Machine_6502::ldx_abs(Machine_6502& machine) {
  ldx(machine.get_cpu(), machine.get_module().get_at(get_abs_address())); }
void Machine_6502::ldx_absy(Machine_6502& machine) {
  ldx(machine.get_cpu(), machine.get_module().get_at(get_absy_address())); }

void Machine_6502::ldy(CPU& cpu, Byte value) {
  cpu.Y = value;
  cpu.NF = ((value & 0x80) == 0x80);
  cpu.ZF = (value == 0);
}
void Machine_6502::ldy_imm(Machine_6502& machine) {
  ldy(machine.get_cpu(), machine.read_program_byte()); }
void Machine_6502::ldy_zp(Machine_6502& machine) {
  ldy(machine.get_cpu(), machine.get_module().get_at(get_zpg_address())); }
void Machine_6502::ldy_zpx(Machine_6502& machine) {
  ldy(machine.get_cpu(), machine.get_module().get_at(get_zpgx_address())); }
void Machine_6502::ldy_abs(Machine_6502& machine) {
  ldy(machine.get_cpu(), machine.get_module().get_at(get_abs_address())); }
void Machine_6502::ldy_absx(Machine_6502& machine) {
  ldy(machine.get_cpu(), machine.get_module().get_at(get_absx_address())); }

void Machine_6502::inc(uint16_t address) {
  Byte result = m_module->get_at(address) + 1;
  m_module->set_at(address, result);
  m_cpu->ZF = (result == 0);
  m_cpu->NF = ((result & 0x80) == 0x80);
}
void Machine_6502::inc_zp(Machine_6502& machine) {
  inc(machine.get_zpg_address()); }
void Machine_6502::inc_zpx(Machine_6502& machine) {
  inc(machine.get_zpgx_address()); }
void Machine_6502::inc_abs(Machine_6502& machine) {
  inc(machine.get_abs_address()); }
void Machine_6502::inc_absx(Machine_6502& machine) {
  inc(machine.get_absx_address()); }

void Machine_6502::dec(uint16_t address) {
  Byte result = m_module->get_at(address) - 1;
  m_module->set_at(address, result);
  m_cpu->ZF = (result == 0);
  m_cpu->NF = ((result & 0x80) == 0x80);
}
void Machine_6502::dec_zp(Machine_6502& machine) {
  dec(machine.get_zpg_address()); }
void Machine_6502::dec_zpx(Machine_6502& machine) {
  dec(machine.get_zpgx_address()); }
void Machine_6502::dec_abs(Machine_6502& machine) {
  dec(machine.get_abs_address()); }
void Machine_6502::dec_absx(Machine_6502& machine) {
  dec(machine.get_absx_address()); }

void Machine_6502::sta(Machine_6502& machine, Word address, Byte reg_val) {
  machine.get_module().set_at(address, reg_val); }
void Machine_6502::sta_zp(Machine_6502& machine) {
  sta(machine, machine.get_zpg_address(), machine.get_cpu().A); }
void Machine_6502::sta_zpx(Machine_6502& machine) {
  sta(machine, machine.get_zpgx_address(), machine.get_cpu().A); }
void Machine_6502::sta_abs(Machine_6502& machine) {
  sta(machine, machine.get_abs_address(), machine.get_cpu().A); }
void Machine_6502::sta_absx(Machine_6502& machine) {
  sta(machine, machine.get_absx_address(), machine.get_cpu().A); }
void Machine_6502::sta_absy(Machine_6502& machine) {
  sta(machine, machine.get_absy_address(), machine.get_cpu().A); }
void Machine_6502::sta_inx(Machine_6502& machine) {
  sta(machine, machine.get_indx_address(), machine.get_cpu().A); }
void Machine_6502::sta_iny(Machine_6502& machine) {
  sta(machine, machine.get_indy_address(), machine.get_cpu().A); }

// void Machine_6502::stx(Machine_6502& machine, Word address, Byte reg_val) { cpu.X = value; }
void Machine_6502::stx_zp(Machine_6502& machine) {
  sta(machine, machine.get_zpg_address(), machine.get_cpu().X); }
void Machine_6502::stx_zpy(Machine_6502& machine) {
  sta(machine, machine.get_zpgy_address(), machine.get_cpu().X); }
void Machine_6502::stx_abs(Machine_6502& machine) {
  sta(machine, machine.get_abs_address(), machine.get_cpu().X); }

//void Machine_6502::sty(CPU& cpu, Byte value) { cpu.Y = value; }
void Machine_6502::sty_zp(Machine_6502& machine) {
  sta(machine, machine.get_zpg_address(), machine.get_cpu().Y); }
void Machine_6502::sty_zpx(Machine_6502& machine) {
  sta(machine, machine.get_zpgx_address(), machine.get_cpu().Y); }
void Machine_6502::sty_abs(Machine_6502& machine) {
  sta(machine, machine.get_abs_address(), machine.get_cpu().Y); }

CPU& Machine_6502::get_cpu() {
  return *m_cpu; }

Memory& Machine_6502::get_module() {
  return *m_module; }

Stack& Machine_6502::get_stack() {
  return *m_stack; }

void Machine_6502::load(const std::vector<Byte> instructions, Word address) {
  m_instruction_address = address;
  m_instruction_size = instructions.size();

  if (m_instruction_size > m_module->MAX)
    throw std::runtime_error("Instructions too large to fit in memory");

  for (auto i = 0; i < instructions.size(); i++) {
    m_module->data[address+i] = instructions.at(i);
  }
  m_cpu->PC = address;
}

bool Machine_6502::is_eop() {
  return (m_cpu->PC >= (m_instruction_address + m_instruction_size)); }

void Machine_6502::execute(Machine_6502& machine) {
  while (!is_eop()) {
    auto byte = read_program_byte();
    auto Fn = handlers.find(byte);
    if (Fn == handlers.end())
      throw std::runtime_error("Tried executing a nonexistent opcode.");
    Fn->second(machine);
  }
}

Byte Machine_6502::read_program_byte() {
  if (is_eop())
    throw std::runtime_error("passed end of program.");
  Byte byte = m_module->data[m_cpu->PC];
  m_cpu->PC++;
  return byte;
}

void Machine_6502::reset() {
  m_cpu->reset();
  m_module->reset();
  m_instruction_address = 0;
  m_instruction_size = 0;
}

uint8_t Machine_6502::get_zpg_address() {
  return read_program_byte(); }

uint8_t Machine_6502::get_zpgx_address() {
    return read_program_byte() + m_cpu->X; }

uint8_t Machine_6502::get_zpgy_address() {
  return read_program_byte() + m_cpu->Y; }

uint16_t Machine_6502::get_abs_address() {
    auto low_byte = read_program_byte();
    auto high_byte = read_program_byte();
    uint16_t address = (high_byte << 8) + low_byte;
    return address;
}

uint16_t Machine_6502::get_absx_address() {
    auto low_byte = read_program_byte();
    auto high_byte = read_program_byte();
    uint16_t address = (high_byte << 8) + low_byte + m_cpu->X;
    return address;
}

uint16_t Machine_6502::get_absy_address() {
    auto low_byte = read_program_byte();
    auto high_byte = read_program_byte();
    uint16_t address = (high_byte << 8) + low_byte + m_cpu->Y;
    return address;
}

uint16_t Machine_6502::get_ind_address() {
    auto low_byte = read_program_byte();
    auto high_byte = read_program_byte();
    uint16_t paddress = (high_byte << 8) + low_byte;

    auto low = m_module->data[paddress];
    auto high = m_module->data[paddress + 1];
    uint16_t address = (high << 8) + low;
    return address;
}

uint16_t Machine_6502::get_indx_address() {
    uint8_t paddress = m_cpu->X + read_program_byte();
    auto low = m_module->data[paddress];
    auto high = m_module->data[paddress + 1];
    uint16_t address = (high << 8) + low;
    return address;
}

uint16_t Machine_6502::get_indy_address() {
    auto offset = read_program_byte();
    auto low = m_module->data[offset];
    auto high = m_module->data[offset + 1];
    auto y = m_cpu->Y;
    uint16_t address = (high << 8) + low + y;
    return address;
}
