#ifndef SCANNER_H
#define SCANNER_H

#include <cstdint>

enum class TokenType {
  // single char
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,
  // one or two chars
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,
  // literals
  IDENTIFIER,
  STRING,
  NUMBER,
  // keywords
  AND,
  CLASS,
  ELSE,
  FALSE,
  FOR,
  FUN,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,
  // Misc
  ERROR,
  END_OF_FILE
};

struct Token {
  const char* start;
  uint32_t line;
  uint32_t length;
  TokenType type;
};

class Scanner {
 public:
  void init_scanner(const char* source);
  const Token scan_token();

 private:
  void skip_whitespace();
  const char peek() const;
  const char peek_next() const;
  const char advance();
  bool match(char expected);
  const Token make_token(TokenType type) const;
  const Token error_token(const char* message) const;
  bool is_at_end() const;

  const char* start;
  const char* current;
  uint32_t line;
};

#endif /* SCANNER_H */