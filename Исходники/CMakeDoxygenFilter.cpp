  int getToken()
  {
    // skip whitespace
    while (isspace(_lastChar) && _lastChar != '\r' && _lastChar != '\n')
    {
      _lastChar = getChar();
    }

    if (isalpha(_lastChar) || _lastChar == '_')
    {
      _identifier = _lastChar;
      while (isalnum(_lastChar = getChar()) || _lastChar == '-' || _lastChar == '_')
      {
        _identifier += _lastChar;
      }

      if (_identifier == "set")
        return TOK_SET;
      if (_identifier == "function")
        return TOK_FUNCTION;
      if (_identifier == "macro")
        return TOK_MACRO;
      if (_identifier == "endfunction")
        return TOK_ENDFUNCTION;
      if (_identifier == "endmacro")
        return TOK_ENDMACRO;
      return TOK_IDENTIFIER;
    }

    if (isdigit(_lastChar))
    {
      // very lax!! number detection
      _identifier = _lastChar;
      while (isalnum(_lastChar = getChar()) || _lastChar == '.' || _lastChar == ',')
      {
        _identifier += _lastChar;
      }
      return TOK_NUMBER_LITERAL;
    }

    if (_lastChar == '#')
    {
      _lastChar = getChar();
      if (_lastChar == '!')
      {
        // found a doxygen comment marker
        _identifier.clear();

        _lastChar = getChar();
        while (_lastChar != EOF && _lastChar != '\n' && _lastChar != '\r')
        {
          _identifier += _lastChar;
          _lastChar = getChar();
        }
        return TOK_DOXYGEN_COMMENT;
      }

      // skip the comment
      while (_lastChar != EOF && _lastChar != '\n' && _lastChar != '\r')
      {
        _lastChar = getChar();
      }
    }

    if (_lastChar == '"')
    {
      _lastChar = getChar();
      _identifier.clear();
      while (_lastChar != EOF && _lastChar != '"')
      {
        _identifier += _lastChar;
        _lastChar = getChar();
      }

      // eat the closing "
      _lastChar = getChar();
      return TOK_STRING_LITERAL;
    }

    // don't eat the EOF
    if (_lastChar == EOF)
      return TOK_EOF;

    // don't eat the EOL
    if (_lastChar == '\r' || _lastChar == '\n')
    {
      if (_lastChar == '\r')
        _lastChar = getChar();
      if (_lastChar == '\n')
        _lastChar = getChar();
      return TOK_EOL;
    }

    // return the character as its ascii value
    int thisChar = _lastChar;
    _lastChar = getChar();
    return thisChar;
  }