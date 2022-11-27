#include <iostream>
#include <iomanip>
#include <sstream>
#include <bitset>

/* NOTE: does not work for single bytes */
template< typename T >
std::string int_to_hex( T i )
{
  std::stringstream stream;
  stream << "0x" 
        << std::setfill ('0') << std::setw(sizeof(T)*2) 
        << std::hex << i;
  return stream.str();
}

void print_Byte(unsigned char byte, const char* name=NULL) {
  if (name != NULL) 
    std::cout << name << " -> " << std::bitset<8>(byte) << " -> " <<
      int_to_hex((int)byte) << '\n';
  else
    std::cout << std::bitset<8>(byte) << " -> " << int_to_hex((int)byte) << '\n';
}
