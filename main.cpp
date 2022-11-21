#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

#include "data.h"
#include "machine_6502.h"

const char* BIN_INSTRUCTION_FILE_PATH = "add.txt";

std::vector<Byte> read_bin(const char* bin_instr)
{
    std::streampos bin_size;
    std::ifstream file(bin_instr, std::ios::binary);

    if (file.fail())
      throw std::runtime_error("Failed to open binary instruction file.");

    file.seekg(0, std::ios::end);
    bin_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<Byte> fileData(bin_size);
    file.read((char*) &fileData[0], bin_size);
    return fileData;
}

void useless(Byte a=0x0, Byte b=0x0, Byte c=0x0, Byte d=0x0, Byte e=0x0) {;};

//#include "debug.h"

int main()
{
  Machine_6502 machine;
  std::vector<Byte> binary_instructions =
    {machine.get_cpu().CMP_IM, machine.get_cpu().CMP_IM};  // 0xC9

  machine.load(binary_instructions, 0);

  machine.run();

  return 0;
}
