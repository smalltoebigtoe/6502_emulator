#ifndef MEMORY_H
#define MEMORY_H

#include "data.h"
#include <stdexcept>

/*
There is 64KB of memory and this is broken into

0x0000 - 0x00FF - Free (Zero Page)
0x0100 - 0x01FF - Stack
0x0200 - 0x05FF - Free
0x0600 - 0xDFFF - Program - always make sure to assemble programs for this address
0xF002 - 0xFFFF - Free        */

struct Memory
{
  static const int MAX = 65535;
  Byte data[MAX];

  uint16_t get_page_offset(uint16_t page);

  void set_at(uint16_t address, Byte input);
  Byte get_at(uint16_t address);

  void set_at_page(uint16_t page, Byte offset, Byte input);
  Byte get_at_page(uint16_t page, Byte offset);

  void reset();
};

#endif
