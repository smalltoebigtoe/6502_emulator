#include "memory.h"

uint16_t Memory::get_page_offset(uint8_t page) {
  uint16_t address = page * 0xFF;
  if (page > 0)
    address++;
  return address;
}

Byte Memory::get_at(uint16_t address) {
  return data[address];
}
void Memory::set_at(uint16_t address, Byte input) {
  data[address] = input;
}

Byte Memory::get_at_page(uint8_t page, Byte offset) {
  return get_at(get_page_offset(page) + offset);
}

void Memory::set_at_page(uint8_t page, Byte offset, Byte input) {
  set_at(get_page_offset(page) + offset, input);
}

void Memory::reset() {
  for (u32 i = 0; i < MAX; i++) {
    data[i] = 0x0;
  }
}
