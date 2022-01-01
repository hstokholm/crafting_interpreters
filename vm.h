#ifndef VM_H
#define VM_H

#include <cstdint>

#include "value.h"

struct Chunk;

enum class InterpretResult { OK, COMPILE_ERROR, RUNTIME_ERROR };

class VM {
 public:
  InterpretResult interpret(Chunk* chunk);

 private:
  uint8_t read_byte();
  Value read_constant();

  void push(Value value);
  Value pop();

  uint8_t* ip = nullptr;
  Chunk* chunk = nullptr;

  Value stack[STACK_MAX];
  Value* stack_top = nullptr;
};

#endif /* VM_H */