#include "machine_6502.h"

Machine_6502::Machine_6502()
  : m_instruction_address{ 0 }, m_instruction_size{ 0 } {
  CPU cpu;
  Memory memory;
  cpu.reset();
  memory.reset();
  m_cpu = &cpu;
  m_module = &memory;
  init_handlers();
  std::cout << "6502 machine created..." << '\n';
}

using namespace std::placeholders;
void Machine_6502::init_handlers() {
  std::function<void(Machine_6502& machine)> cmp_im =
    std::bind(&Machine_6502::cmp_im, this, std::placeholders::_1);

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

  handlers.insert(std::make_pair(0xC9, cmp_im));
  handlers.insert(std::make_pair(0xC5, cmp_zp));
  handlers.insert(std::make_pair(0xD5, cmp_zpx));
  handlers.insert(std::make_pair(0xCD, cmp_abs));
  handlers.insert(std::make_pair(0xDD, cmp_absx));
  handlers.insert(std::make_pair(0xD9, cmp_absy));
  handlers.insert(std::make_pair(0xC1, cmp_inx));
  handlers.insert(std::make_pair(0xD1, cmp_iny));
}

void Machine_6502::cmp(CPU& cpu, Byte reg_val, Byte value) {
  Byte result = reg_val - value;
  cpu.CF = false;
  cpu.ZF = false;
  if (reg_val >= value)
    cpu.CF = true;
  if (reg_val == value)
    cpu.ZF = true;
  if ((result & 0x80) == 0x80)
    cpu.NF = true;
}

void Machine_6502::cmp_im(Machine_6502& machine) {
  cmp(machine.get_cpu(), machine.get_cpu().A, machine.read_program_byte()); }
void Machine_6502::cmp_zp(Machine_6502& machine) { /* zpg*/
  cmp(machine.get_cpu(), machine.get_cpu().A, machine.get_module().data[get_zpg_address()]); }
void Machine_6502::cmp_zpx(Machine_6502& machine) { /* zpgx*/
  cmp(machine.get_cpu(), machine.get_cpu().A, machine.get_module().data[get_zpgx_address()]); }
void Machine_6502::cmp_abs(Machine_6502& machine) { /* abs*/
  cmp(machine.get_cpu(), machine.get_cpu().A, machine.get_module().data[get_abs_address()]); }
void Machine_6502::cmp_absx(Machine_6502& machine) { /* absx*/
  cmp(machine.get_cpu(), machine.get_cpu().A, machine.get_module().data[get_absx_address()]); }
void Machine_6502::cmp_absy(Machine_6502& machine) { /* absy*/
  cmp(machine.get_cpu(), machine.get_cpu().A, machine.get_module().data[get_absy_address()]); }
void Machine_6502::cmp_inx(Machine_6502& machine) { /* indx */
  cmp(machine.get_cpu(), machine.get_cpu().A, machine.get_module().data[get_indx_address()]); }
void Machine_6502::cmp_iny(Machine_6502& machine) { /* indy*/
  cmp(machine.get_cpu(), machine.get_cpu().A, machine.get_module().data[get_indy_address()]); }

uint8_t Machine_6502::get_zpg_address() {
  return read_program_byte();
}

uint8_t Machine_6502::get_zpgx_address() {
    // expect wrap around
    return read_program_byte() + m_cpu->X;
}

uint8_t Machine_6502::get_zpgy_address() {
    // expect wrap around
    return read_program_byte() + m_cpu->Y;
}

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
  std::cout << "instructions with size " << instructions.size() << " loaded at " << address << '\n';
}

bool Machine_6502::is_eop() {
  bool yup = (m_cpu->PC >= (m_instruction_address + m_instruction_size));
  return yup;
}

void Machine_6502::execute(Machine_6502& machine) {
  while (!is_eop()) {
    auto byte = read_program_byte();
    auto Fn = handlers.find(byte);
    if (Fn == handlers.end())
      throw std::runtime_error("Tried executing a nonexistent opcode.");
    Fn->second(machine);
    std::cout << "executed a fn.\n";
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

  std::cout << "6502 machine restarted." << '\n';
}
