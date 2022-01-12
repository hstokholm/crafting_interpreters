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
  skip_whitespace();
  start = current;

  if (is_at_end()) return make_token(TokenType::END_OF_FILE);

  const char c = advance();
  if (is_alpha(c)) return identifier();
  if (is_digit(c)) return number();
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
    case '"':
      return string();
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
const Token Scanner::string() {
  while (peek() != '"' && !is_at_end()) {
    if (peek() == '\n') line++;
    advance();
  }

  if (is_at_end()) return error_token("Unterminated string.");

  // The closing quote.
  advance();
  return make_token(TokenType::STRING);
}

//-----------------------------------------------------------------------------
const Token Scanner::number() {
  while (is_digit(peek())) advance();

  // Look for a fractional part.
  if (peek() == '.' && is_digit(peek_next())) {
    // Consume the ".".
    advance();

    while (is_digit(peek())) advance();
  }

  return make_token(TokenType::NUMBER);
}

//-----------------------------------------------------------------------------
const Token Scanner::identifier() {
  while (is_alpha(peek()) || is_digit(peek())) advance();
  return make_token(identifier_type());
}

//-----------------------------------------------------------------------------
TokenType Scanner::identifier_type() const {
  switch (start[0]) {
    case 'a':
      return check_keyword(1, 2, "nd", TokenType::AND);
    case 'c':
      return check_keyword(1, 4, "lass", TokenType::CLASS);
    case 'e':
      return check_keyword(1, 3, "lse", TokenType::ELSE);
    case 'f':
      if (current - start > 1) {
        switch (start[1]) {
          case 'a':
            return check_keyword(2, 3, "lse", TokenType::FALSE);
          case 'o':
            return check_keyword(2, 1, "r", TokenType::FOR);
          case 'u':
            return check_keyword(2, 1, "n", TokenType::FUN);
        }
      }
      break;
    case 'i':
      return check_keyword(1, 1, "f", TokenType::IF);
    case 'n':
      return check_keyword(1, 2, "il", TokenType::NIL);
    case 'o':
      return check_keyword(1, 1, "r", TokenType::OR);
    case 'p':
      return check_keyword(1, 4, "rint", TokenType::PRINT);
    case 'r':
      return check_keyword(1, 5, "eturn", TokenType::RETURN);
    case 's':
      return check_keyword(1, 4, "uper", TokenType::SUPER);
    case 't':
      if (current - start > 1) {
        switch (start[1]) {
          case 'h':
            return check_keyword(2, 2, "is", TokenType::THIS);
          case 'r':
            return check_keyword(2, 2, "ue", TokenType::TRUE);
        }
      }
      break;
    case 'v':
      return check_keyword(1, 2, "ar", TokenType::VAR);
    case 'w':
      return check_keyword(1, 4, "hile", TokenType::WHILE);
  }

  return TokenType::IDENTIFIER;
}

//-----------------------------------------------------------------------------
TokenType Scanner::check_keyword(uint8_t start_, uint8_t length,
                                 const char* rest, TokenType type) const {
  if (current - start == start_ + length &&
      memcmp(start + start_, rest, length) == 0) {
    return type;
  }

  return TokenType::IDENTIFIER;
}

//-----------------------------------------------------------------------------
bool Scanner::is_at_end() const { return *current == '\0'; }

//-----------------------------------------------------------------------------
bool Scanner::is_digit(char c) const { return c >= '0' && c <= '9'; }

//-----------------------------------------------------------------------------
bool Scanner::is_alpha(char c) const {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}