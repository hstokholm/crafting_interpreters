#include "scanner.h"

#include <cstring>

//-----------------------------------------------------------------------------
void Scanner::init_scanner(const char* source) {
  start = source;
  current = source;
  line = 1;
}

//-----------------------------------------------------------------------------
const Token Scanner::scan_token() {
  start = current;

  if (is_at_end()) return make_token(TokenType::END_OF_FILE);

  const char c = advance();
  switch (c) {
    // Single chars
    case '(':
      return make_token(TokenType::LEFT_PAREN);
    case ')':
      return make_token(TokenType::RIGHT_PAREN);
    case '{':
      return make_token(TokenType::LEFT_BRACE);
    case '}':
      return make_token(TokenType::RIGHT_BRACE);
    case ';':
      return make_token(TokenType::SEMICOLON);
    case ',':
      return make_token(TokenType::COMMA);
    case '.':
      return make_token(TokenType::DOT);
    case '-':
      return make_token(TokenType::MINUS);
    case '+':
      return make_token(TokenType::PLUS);
    case '/':
      return make_token(TokenType::SLASH);
    case '*':
      return make_token(TokenType::STAR);

      // One er two chars
    case '!':
      return make_token(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
    case '=':
      return make_token(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
    case '<':
      return make_token(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
    case '>':
      return make_token(match('=') ? TokenType::GREATER_EQUAL
                                   : TokenType::GREATER);
  }

  return error_token("Unexpected character.");
}

//-----------------------------------------------------------------------------
void Scanner::skip_whitespace() {
  while (true) {
    const char c = peek();
    switch (c) {
      case ' ':
      case '\r':
      case '\t':
        advance();
        break;
      case '\n':
        line++;
        advance();
        break;
      case '/':
        if (peek_next() == '/') {
          // A comment goes until the end of the line.
          while (peek() != '\n' && !is_at_end()) advance();
        } else {
          return;
        }
        break;
      default:
        return;
    }
  }
}

//-----------------------------------------------------------------------------
const char Scanner::peek() const { return *current; }

//-----------------------------------------------------------------------------
const char Scanner::peek_next() const {
  if (is_at_end()) return '\0';
  return current[1];
}

//-----------------------------------------------------------------------------
const char Scanner::advance() {
  current++;
  return current[-1];
}

//-----------------------------------------------------------------------------
bool Scanner::match(char expected) {
  if (is_at_end()) return false;
  if (*current != expected) return false;
  current++;
  return true;
}

//-----------------------------------------------------------------------------
const Token Scanner::make_token(TokenType type) const {
  Token token;
  token.type = type;
  token.start = start;
  token.length = static_cast<uint32_t>(current - start);
  token.line = line;
  return token;
}

//-----------------------------------------------------------------------------
const Token Scanner::error_token(const char* message) const {
  Token token;
  token.type = TokenType::ERROR;
  token.start = message;
  token.length = static_cast<uint32_t>(strlen(message));
  token.line = line;
  return token;
}

//-----------------------------------------------------------------------------
bool Scanner::is_at_end() const { return *current == '\0'; }
