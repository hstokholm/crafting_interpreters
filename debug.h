#ifndef DEBUG_H
#define DEBUG_H

#include <cstdint>

class Chunk;

namespace debug {

void disassemble_chunk(Chunk* chunk, const char* name);
uint32_t disassemble_instruction(Chunk* chunk, int offset);

};  // namespace debug

#endif /* DEBUG_H */