#include "chunk.h"

#include <cstdlib>

//-----------------------------------------------------------------------------
uint8_t to_uint8(OpCode code) { return static_cast<uint8_t>(code); }

//-----------------------------------------------------------------------------
void init_chunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = nullptr;
  init_array(&chunk->constants);
}

//-----------------------------------------------------------------------------
void free_chunk(Chunk* chunk, Allocator& allocator) {
  allocator.free(chunk->code);
  free_array(&chunk->constants, allocator);
  init_chunk(chunk);
}

//-----------------------------------------------------------------------------
void write_chunk(Chunk* chunk, uint8_t byte, Allocator& allocator) {
  // Do we need to reallocate array?
  if (chunk->capacity < chunk->count + 1) {
    const uint32_t old_capacity = chunk->capacity;
    chunk->capacity = ((chunk->capacity) < 8 ? 8 : (chunk->capacity) * 2);
    chunk->code =
        static_cast<uint8_t*>(allocator.realloc(chunk->code, chunk->capacity));
  }

  chunk->code[chunk->count] = byte;
  chunk->count++;
}

//-----------------------------------------------------------------------------
uint32_t add_constant(Chunk* chunk, Value value, Allocator& allocator) {
  write_array(&chunk->constants, value, allocator);
  return chunk->constants.count - 1;
}
