#include "chunk.h"

#include <cstdlib>

//-----------------------------------------------------------------------------
uint8_t to_uint8(OpCode code) { return static_cast<uint8_t>(code); }

//-----------------------------------------------------------------------------
void init_chunk(Chunk* chunk) {
  init_array(&chunk->code);
  init_array(&chunk->lines);
  init_array(&chunk->constants);
}

//-----------------------------------------------------------------------------
void free_chunk(Chunk* chunk, Allocator& allocator) {
  free_array(&chunk->code, allocator);
  free_array(&chunk->lines, allocator);
  free_array(&chunk->constants, allocator);
  init_chunk(chunk);
}

//-----------------------------------------------------------------------------
void write_chunk(Chunk* chunk, OpCode op, uint32_t line, Allocator& allocator) {
  write_chunk(chunk, to_uint8(op), line, allocator);
}

//-----------------------------------------------------------------------------
void write_chunk(Chunk* chunk, uint8_t byte, uint32_t line,
                 Allocator& allocator) {
  write_array(&chunk->code, byte, allocator);
  write_array(&chunk->lines, line, allocator);
}

//-----------------------------------------------------------------------------
uint32_t add_constant(Chunk* chunk, Value value, Allocator& allocator) {
  write_array(&chunk->constants, value, allocator);
  return chunk->constants.count - 1;
}
