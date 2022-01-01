#ifndef CHUNK_H
#define CHUNK_H

#include <cstdint>

#include "common.h"
#include "value.h"

enum class OpCode {
  CONSTANT,
  NEGATE,
  ADD,
  SUBTRACT,
  MULTIPLY,
  DIVIDE,
  RETURN,
};

uint8_t to_uint8(OpCode code);

struct Chunk {
  ByteArray code;
  UIntArray lines;
  ValueArray constants;
};

void init_chunk(Chunk* chunk);
void free_chunk(Chunk* chunk, Allocator& allocator);
void write_chunk(Chunk* chunk, OpCode op, uint32_t line, Allocator& allocator);
void write_chunk(Chunk* chunk, uint8_t byte, uint32_t line,
                 Allocator& allocator);
uint32_t add_constant(Chunk* chunk, Value value, Allocator& allocator);

#endif /* CHUNK_H */