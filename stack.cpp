#include "stack.h"

Word Stack::get_page_offset(Byte page) {
  Word address = page * 0xFF;
  if (page > 0)
    address += 1;
  return address;
}

void Stack::init_memory() {
  memory = std::vector<Byte>(0xFFFF);
  on_write_callbacks = {};
}

Byte Stack::get_at(Word address) {
  return memory.at(address); }

void Stack::set_at(Word address, Byte value) {
  memory.at(address) = value;
  for (auto& cb : on_write_callbacks) {
    std::pair<Word, Byte> address_value{address, value};
    cb(address_value);
  }
}

Byte Stack::get_from_page(Byte page, Byte offset) {
  return get_at(get_page_offset(page) + offset); }

void Stack::set_on_page(Byte page, Byte offset, Byte value) {
  set_at(get_page_offset(page) + offset, value); }

void Stack::register_callback(std::function<void(std::pair<Word, Byte>)> callback) {
  on_write_callbacks.push_back(callback); }

void Stack::init_stack() {
  init_memory();
  sp = 0xFF;
}

void Stack::push(Byte value) {
  auto sp_val = sp;
  set_on_page(Stack::PAGE, sp_val, value);
  sp = sp_val + 1;
}

Byte Stack::pop() {
  auto sp_val = sp - 1;
  sp = sp_val;
  return get_from_page(Stack::PAGE, sp_val);
}

Stack::Stack(std::vector<Byte>& memory, Byte& sp) : memory(memory), sp(sp) {
  init_stack();
}

Stack::Stack() {
  init_stack();
}
