#include <cstdio>
#include <iostream>

#include "chunk.h"
#include "common.h"
#include "debug.h"

//-----------------------------------------------------------------------------
int main(int argc, const char* argv[]) {
  Allocator allocator;
  Chunk chunk;
  initChunk(&chunk);
  writeChunk(&chunk, to_uint8(OpCode::RETURN), allocator);
  debug::disassemble_chunk(&chunk, "test chunk");
  freeChunk(&chunk, allocator);

  // Allow the user to actually see the console output prior to quiting
  printf("Press Enter to exit...");
  getchar();
  return 0;
}