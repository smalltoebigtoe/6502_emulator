#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <functional>
#include <vector>

#include "data.h"

class Stack {
  public:
    std::vector<Byte> memory;
    std::vector<std::function<void(std::pair<Word, Byte>)>> on_write_callbacks;
  
    uint16_t get_page_offset(Byte page);
    Byte get_at(Word address);
    void set_at(Word address, Byte value);
    Byte get_from_page(Byte page, Byte offset);
    void set_on_page(Byte page, Byte offset, Byte value);
    void register_callback(std::function<void(std::pair<Word, Byte>)> callback);
    void init_memory();

    const Byte PAGE = 1;
    Byte sp;
    void init_stack();
    void push(Byte value);
    Byte pop();
    Stack(std::vector<Byte>& memory, Byte& sp);
    Stack();
};

#endif
