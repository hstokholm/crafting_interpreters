#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

namespace {

//-----------------------------------------------------------------------------
InterpretResult interpret(const char* line) {
  return InterpretResult::COMPILE_ERROR;
}

//-----------------------------------------------------------------------------
void repl() {
  char line[1024];
  while (true) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }
    interpret(line);
  }
}

//-----------------------------------------------------------------------------
void run_file(const char* path, Allocator& allocator) {
  FILE* file = fopen(path, "rb");
  fseek(file, 0L, SEEK_END);
  const size_t file_size = ftell(file);
  fseek(file, 0L, SEEK_SET);
  char* source = (char*)allocator.alloc(file_size + 1);
  const size_t bytes_read = fread(source, sizeof(char), file_size, file);
  source[bytes_read] = '\0';

  fclose(file);

  const InterpretResult result = interpret(source);
  allocator.free(source);

  if (result == InterpretResult::COMPILE_ERROR) exit(65);
  if (result == InterpretResult::RUNTIME_ERROR) exit(70);
}

}  // namespace

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