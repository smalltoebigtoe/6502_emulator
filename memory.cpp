#include "memory.h"

void Memory::reset() {
  for (u32 i = 0; i < MAX; i++) {
    data[i] = 0x0;
  }
}

Byte Memory::operator[](u32 address) const {
  // assert(address > MAX);
  return data[address];
}
