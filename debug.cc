#include "debug.h"

#include <cstdio>

#include "chunk.h"

namespace debug {

namespace {
//-----------------------------------------------------------------------------
uint32_t simple_instruction(const char* name, uint32_t offset) {
  printf("%s\n", name);
  return offset + 1;
}

//-----------------------------------------------------------------------------
uint32_t constant_instruction(const char* name, Chunk* chunk, uint32_t offset) {
  uint8_t constant = chunk->code.data[offset + 1];
  printf("%-16s %4d '", name, constant);
  print_value(chunk->constants.data[constant]);
  printf("'\n");
  return offset + 2;
}

}  // namespace

//-----------------------------------------------------------------------------
void disassemble_chunk(Chunk* chunk, const char* name) {
  printf("== %s ==\n", name);

  for (int offset = 0; offset < chunk->code.count;) {
    offset = disassemble_instruction(chunk, offset);
  }
}

//-----------------------------------------------------------------------------
uint32_t disassemble_instruction(Chunk* chunk, int offset) {
  printf("%04d ", offset);

  if (offset > 0 &&
      chunk->lines.data[offset] == chunk->lines.data[offset - 1]) {
    printf("   | ");
  } else {
    printf("%4d ", chunk->lines.data[offset]);
  }

  uint8_t instruction = chunk->code.data[offset];
  switch (OpCode(instruction)) {
    case OpCode::CONSTANT:
      return constant_instruction("OP_CONSTANT", chunk, offset);
    case OpCode::RETURN:
      return simple_instruction("OP_RETURN", offset);
    case OpCode::ADD:
      return simple_instruction("OP_ADD", offset);
    case OpCode::SUBTRACT:
      return simple_instruction("OP_SUBTRACT", offset);
    case OpCode::MULTIPLY:
      return simple_instruction("OP_MULTIPLY", offset);
    case OpCode::DIVIDE:
      return simple_instruction("OP_DIVIDE", offset);
    case OpCode::NEGATE:
      return simple_instruction("OP_NEGATE", offset);
    default:
      printf("Unknown opcode %d\n", instruction);
      return offset + 1;
  }
}

};  // namespace debug
