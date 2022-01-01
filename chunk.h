#ifndef CHUNK_H
#define CHUNK_H

#include <cstdint>

#include "common.h"
#include "value.h"

enum class OpCode {
  CONSTANT,
  RETURN,
};

uint8_t to_uint8(OpCode code);

struct Chunk {
  uint32_t count;
  uint32_t capacity;
  uint8_t* code;
  ValueArray constants;
};

void init_chunk(Chunk* chunk);
void free_chunk(Chunk* chunk, Allocator& allocator);
void write_chunk(Chunk* chunk, OpCode op, Allocator& allocator);
void write_chunk(Chunk* chunk, uint8_t byte, Allocator& allocator);
uint32_t add_constant(Chunk* chunk, Value value, Allocator& allocator);

#endif /* CHUNK_H */