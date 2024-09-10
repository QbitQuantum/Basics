Token DefaultLexer::readToken() {
  char c = lookChar();

  while (true) {
    // skip whitespace
    while (isWhiteSpace(c)) {
      skipChar();
      c = lookChar();
    }

    // newlines
    if (isNewline(c)) {
      readNewline(c);
      if (interactive_ && getCurrentBraceNesting() == 0)
        return Token(TK_Newline);
      c = lookChar();
      continue;
    }

    // treat line comments as newlines
    if (c == '/' && lookChar(1) == '/') {
      readLineComment();
      c = lookChar();
      continue;
    }
    break;
  }

  SourceLocation sloc = getCurrentLocation();

  // punctuation
  if (c == '(') {
    skipChar();
    signalOpenBrace(TK_LParen);
    return Token(TK_LParen, "(", sloc);
  }
  if (c == ')') {
    skipChar();
    signalCloseBrace(TK_LParen);
    return Token(TK_RParen, ")", sloc);
  }
  if (c == '{') {
    skipChar();
    signalOpenBrace(TK_LCurlyBrace);
    return Token(TK_LCurlyBrace, "{", sloc);
  }
  if (c == '}') {
    skipChar();
    signalCloseBrace(TK_LCurlyBrace);
    return Token(TK_RCurlyBrace, "}", sloc);
  }
  if (c == '[') {
    skipChar();
    signalOpenBrace(TK_LSquareBrace);
    return Token(TK_LSquareBrace, "[", sloc);
  }
  if (c == ']') {
    skipChar();
    signalCloseBrace(TK_LSquareBrace);
    return Token(TK_RSquareBrace, "]", sloc);
  }
  if (c == ',') {
    skipChar();
    return Token(TK_Comma, ",", sloc);
  }
  if (c == ';') {
    skipChar();
    return Token(TK_Semicolon, ";", sloc);
  }
  if (c == ':' && !isOperatorChar(lookChar(1))) {
    skipChar();
    return Token(TK_Colon, ":", sloc);
  }
  if (c == '.') {
    skipChar();
    return Token(TK_Period, ".", sloc);
  }

  // identifiers
  if (isLetter(c)) {
    readIdentifier(c);
    StringRef str = copyStr(finishToken());

    unsigned short keyid =
      static_cast<unsigned short>( lookupKeyword(str.c_str()) );
    if (keyid) {
      return Token(keyid, str, sloc);
    }
    return Token(TK_Identifier, str, sloc);
  }

  // generic operators
  if (isOperatorChar(c)) {
    readOperator(c);
    StringRef str = copyStr(finishToken());

    unsigned short keyid =
      static_cast<unsigned short>( lookupKeyword(str.c_str()) );
    if (keyid) {
      return Token(keyid, str, sloc);
    }
    return Token(TK_Operator, str, sloc);
  }

  // numbers
  if (isDigit(c)) {
    if (c == '0' && lookChar(1) == 'x') {
      putChar('0');
      skipChar();
      putChar('x');
      skipChar();
      readHexInteger();
      StringRef str = copyStr(finishToken());
      return Token(TK_LitInteger, str, sloc);
    }

    readInteger(c);
    char c2 = lookChar();
    if (c2 == '.') {
      readInteger(c2);
      c2 = lookChar();
      if (c2 == 'e' || c2 == 'E') {
        if (!readFloatExp(c2))
          signalLexicalError();
      }
      StringRef str = copyStr(finishToken());
      return Token(TK_LitFloat, str, sloc);
    }
    else if (c2 == 'e' || c2 == 'E') {
      if (!readFloatExp(c2))
        signalLexicalError();
      StringRef str = copyStr(finishToken());
      return Token(TK_LitFloat, str, sloc);
    }
    else {
      StringRef str = copyStr(finishToken());
      return Token(TK_LitInteger, str, sloc);
    }
  }

  // characters
  if (c == '\'') {
    if (!readCharacter())
      return Token(TK_Error);

    StringRef str = copyStr(finishToken());
    return Token(TK_LitCharacter, str, sloc);
  }

  // strings
  if (c == '\"') {
    if (!readString())
      return Token(TK_Error);

    StringRef str = copyStr(finishToken());
    return Token(TK_LitString, str, sloc);
  }

  // if we're out of buffer, put in an EOF token.
  if (c == 0 || stream_eof()) {
    return Token(TK_EOF, "", sloc);
  }

  // Can't get the next token -- signal an error and bail.
  signalLexicalError();
  return Token(TK_Error, "", sloc);
}