#include "debug.h"

#include <cstdio>

#include "chunk.h"

namespace debug {

namespace {
uint32_t simple_instruction(const char* name, uint32_t offset) {
  printf("%s\n", name);
  return offset + 1;
}
}  // namespace

//-----------------------------------------------------------------------------
void disassemble_chunk(Chunk* chunk, const char* name) {
  printf("== %s ==\n", name);

  for (int offset = 0; offset < chunk->count;) {
    offset = disassemble_instruction(chunk, offset);
  }
}

//-----------------------------------------------------------------------------
uint32_t disassemble_instruction(Chunk* chunk, int offset) {
  printf("%04d ", offset);

  uint8_t instruction = chunk->code[offset];
  switch (OpCode(instruction)) {
    case OpCode::RETURN:
      return simple_instruction("OP_RETURN", offset);
    default:
      printf("Unknown opcode %d\n", instruction);
      return offset + 1;
  }
}

};  // namespace debug
