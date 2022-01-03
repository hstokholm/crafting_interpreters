#include "compiler.h"

#include <cstdio>

#include "scanner.h"

//-----------------------------------------------------------------------------
void Compiler::compile(const char* source) {
  Scanner scanner;

  uint32_t line = -1;
  while (true) {
    const Token token = scanner.scan_token();
    if (token.line != line) {
      printf("%4d ", token.line);
      line = token.line;
    } else {
      printf("   | ");
    }
    printf("%2d '%.*s'\n", token.type, token.length, token.start);

    if (token.type == TokenType::END_OF_FILE) break;
  }
}
