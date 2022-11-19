#ifndef MEMORY_H
#define MEMORY

#include "data.h"

struct Memory
{
  static const u32 MAX = 1024 * 64;
  Byte data[MAX];

  void init();
  Byte operator[](u32 address) const;
};

#endif
