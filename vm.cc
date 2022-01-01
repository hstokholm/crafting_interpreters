#include "vm.h"

#include <cstdio>

#include "chunk.h"
#include "debug.h"

//-----------------------------------------------------------------------------
InterpretResult VM::interpret(Chunk* chunk) {
  ip = &chunk->code.data[0];
  this->chunk = chunk;
  stack_top = stack;

  while (true) {
#if DEBUG_TRACE_EXECUTION
    printf("          ");
    for (Value* slot = stack; slot < stack_top; slot++) {
      printf("[ ");
      print_value(*slot);
      printf(" ]");
    }
    printf("\n");

    debug::disassemble_instruction(chunk, (int)(ip - chunk->code.data));
#endif

    switch (OpCode(read_byte())) {
      case OpCode::RETURN: {
        print_value(pop());
        printf("\n");
        return InterpretResult::OK;
      }
      case OpCode::NEGATE: {
        push(-pop());
        break;
      }
      case OpCode::CONSTANT: {
        push(read_constant());
        break;
      }
    }
  }
}

//-----------------------------------------------------------------------------
uint8_t VM::read_byte() { return (*ip++); }

//-----------------------------------------------------------------------------
Value VM::read_constant() { return chunk->constants.data[read_byte()]; }

//-----------------------------------------------------------------------------
void VM::push(Value value) {
  *stack_top = value;
  stack_top++;
}

//-----------------------------------------------------------------------------
Value VM::pop() {
  stack_top--;
  return *stack_top;
}