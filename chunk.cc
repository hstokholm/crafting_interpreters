#include "chunk.h"

#include <cstdlib>

//-----------------------------------------------------------------------------
uint8_t to_uint8(OpCode code) { return static_cast<uint8_t>(code); }

//-----------------------------------------------------------------------------
void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = nullptr;
}

//-----------------------------------------------------------------------------
void freeChunk(Chunk* chunk, Allocator& allocator) {
  allocator.free(chunk->code);
  initChunk(chunk);
}

//-----------------------------------------------------------------------------
void writeChunk(Chunk* chunk, uint8_t byte, Allocator& allocator) {
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
