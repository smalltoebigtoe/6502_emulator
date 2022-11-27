#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <bitset>

/* NOTE: does not work for single bytes */
template< typename T >
std::string int_to_hex( T i );

void print_Byte(unsigned char byte, const char* name=NULL);

#endif
