#ifndef CHUNK_H
#define CHUNK_H

#include "common.h"

#include <cstdint>

enum class OpCode {
  RETURN,
};

uint8_t to_uint8(OpCode code);

struct Chunk {
  uint32_t count;
  uint32_t capacity;
  uint8_t* code;
};

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk, Allocator& allocator);
void writeChunk(Chunk* chunk, uint8_t byte, Allocator& allocator);

#endif /* CHUNK_H */