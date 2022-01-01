#include <cstdio>
#include <iostream>

#include "chunk.h"
#include "common.h"
#include "debug.h"

//-----------------------------------------------------------------------------
int main(int argc, const char* argv[]) {
  Allocator allocator;
  Chunk chunk;
  uint32_t line = 1;
  init_chunk(&chunk);

  const uint32_t constant = add_constant(&chunk, 1.2, allocator);
  write_chunk(&chunk, OpCode::CONSTANT, line++, allocator);
  write_chunk(&chunk, static_cast<uint8_t>(constant), line++, allocator);

  write_chunk(&chunk, OpCode::RETURN, line++, allocator);
  debug::disassemble_chunk(&chunk, "test chunk");
  free_chunk(&chunk, allocator);

  // Allow the user to actually see the console output prior to quiting
  printf("Press Enter to exit...");
  getchar();
  return 0;
}