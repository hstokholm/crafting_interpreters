#include <cstdio>
#include <iostream>

#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

//-----------------------------------------------------------------------------
int main(int argc, const char* argv[]) {
  Allocator allocator;

  VM vm;

  Chunk chunk;
  uint32_t line = 1;
  init_chunk(&chunk);

  uint32_t constant = add_constant(&chunk, 1.2, allocator);
  write_chunk(&chunk, OpCode::CONSTANT, line++, allocator);
  write_chunk(&chunk, static_cast<uint8_t>(constant), line++, allocator);

  constant = add_constant(&chunk, 3.4, allocator);
  write_chunk(&chunk, OpCode::CONSTANT, 123, allocator);
  write_chunk(&chunk, constant, 123, allocator);

  write_chunk(&chunk, OpCode::ADD, 123, allocator);

  constant = add_constant(&chunk, 5.6, allocator);
  write_chunk(&chunk, OpCode::CONSTANT, 123, allocator);
  write_chunk(&chunk, constant, 123, allocator);

  write_chunk(&chunk, OpCode::DIVIDE, 123, allocator);

  write_chunk(&chunk, OpCode::NEGATE, line++, allocator);
  write_chunk(&chunk, OpCode::RETURN, line++, allocator);

  vm.interpret(&chunk);

  free_chunk(&chunk, allocator);

  // Allow the user to actually see the console output prior to quiting
  printf("Press Enter to exit...");
  getchar();
  return 0;
}