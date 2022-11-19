#include <iostream>

#include "memory.h"
#include "cpu.h"

int main(void)
{
  Memory RAM;
  CPU CPU;
  CPU.reset(RAM);
  CPU.exe(RAM, 2);  // executes 2 instructions 

  std::cout << RAM.data[RAM.MAX-1] << '\n';
  std::cout << CPU.PC << '\n';

  return 0;
}
