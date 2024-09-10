static inline int process_number_token(JSONRD_T *jsonrd, const char *chunk, size_t size, size_t offset) {
  int i;
  for (i = offset; i < size; i++) {
    switch (jsonrd->token.num_state) {
      case NS_BEGIN:
        if (chunk[i] == '-') {
          jsonrd->token.num_state = NS_LEADING_MINUS;
        } else if (chunk[i] == '0') {
          jsonrd->token.num_state = NS_LEADING_ZERO;
        } else if (chunk[i] > '0' && chunk[i] <= '9') {
          jsonrd->token.num_state = NS_LEADING_DIGITS;
        } else {
          jsonrd->token.type = TOK_ILLEGAL;
          jsonrd->token.state = TS_FOUND_TOKEN;
          return i + 1;
        }
        break;
      case NS_LEADING_MINUS:
        if (chunk[i] == '0') {
          jsonrd->token.num_state = NS_LEADING_ZERO;
        } else if (chunk[i] > '0' && chunk[i] <= '9') {
          jsonrd->token.num_state = NS_LEADING_DIGITS;
        } else {
          jsonrd->token.type = TOK_ILLEGAL;
          jsonrd->token.state = TS_FOUND_TOKEN;
          return i + 1;
        }
        break;
      case NS_LEADING_ZERO:
        if (chunk[i] == '.') {
          jsonrd->token.num_state = NS_DECIMAL_PLACE;
        } else if (chunk[i] == 'e' || chunk[i] == 'E') {
          jsonrd->token.num_state = NS_EXPONENT_CHAR;
        } else {
          jsonrd->token.value_number = strtold(str_internal(jsonrd->buf), NULL);
          jsonrd->token.state = TS_FOUND_TOKEN;
          return i;
        }
        break;
      case NS_LEADING_DIGITS:
        if (chunk[i] >= '0' && chunk[i] <= '9') {
          // keep current state
        } else if (chunk[i] == '.') {
          jsonrd->token.num_state = NS_DECIMAL_PLACE;
        } else if (chunk[i] == 'e' || chunk[i] == 'E') {
          jsonrd->token.num_state = NS_EXPONENT_CHAR;
        } else {
          jsonrd->token.value_number = strtold(str_internal(jsonrd->buf), NULL);
          jsonrd->token.state = TS_FOUND_TOKEN;
          return i;
        }
        break;
      case NS_DECIMAL_PLACE:
        if (chunk[i] >= '0' && chunk[i] <= '9') {
          jsonrd->token.num_state = NS_DECIMAL_DIGITS;
        } else {
          jsonrd->token.type = TOK_ILLEGAL;
          jsonrd->token.state = TS_FOUND_TOKEN;
          return i + 1;
        }
        break;
      case NS_DECIMAL_DIGITS:
        if (chunk[i] >= '0' && chunk[i] <= '9') {
          // keep current state
        } else if (chunk[i] == 'e' || chunk[i] == 'E') {
          jsonrd->token.num_state = NS_EXPONENT_CHAR;
        } else {
          jsonrd->token.value_number = strtold(str_internal(jsonrd->buf), NULL);
          jsonrd->token.state = TS_FOUND_TOKEN;
          return i;
        }
        break;
      case NS_EXPONENT_CHAR:
        if (chunk[i] == '+' || chunk[i] == '-') {
          jsonrd->token.num_state = NS_EXPONENT_SIGN;
        } else if (chunk[i] >= '0' && chunk[i] <= '9') {
          jsonrd->token.num_state = NS_EXPONENT_DIGITS;
        } else {
          jsonrd->token.type = TOK_ILLEGAL;
          jsonrd->token.state = TS_FOUND_TOKEN;
          return i + 1;
        }
        break;
      case NS_EXPONENT_SIGN:
        if (chunk[i] >= '0' && chunk[i] <= '9') {
          jsonrd->token.num_state = NS_EXPONENT_DIGITS;
        } else {
          jsonrd->token.type = TOK_ILLEGAL;
          jsonrd->token.state = TS_FOUND_TOKEN;
          return i + 1;
        }
        break;
      case NS_EXPONENT_DIGITS:
        if (chunk[i] >= '0' && chunk[i] <= '9') {
          // keep current state
        } else {
          jsonrd->token.value_number = strtold(str_internal(jsonrd->buf), NULL);
          jsonrd->token.state = TS_FOUND_TOKEN;
          return i;
        }
        break;
      default:
        die("Illegal state");
        return size;
    }
    str_append(jsonrd->buf, chunk+i, 1);
  }
  return size;
}