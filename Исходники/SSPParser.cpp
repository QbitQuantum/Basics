int SSPParser::getNextToken(void *Val) {
  YYSTYPE *Value = static_cast<YYSTYPE*>(Val);

  StringRef    BufferData = Buf->getBuffer();
  const char  *Data       = BufferData.data();
  const char*  CurCh      = Data+CurPos;

  while (CurPos < BufferData.size()                         &&
         (*CurCh == '\t' || *CurCh == ' ' || *CurCh == '\r' ||
          *CurCh == '\n')) {
    CurPos++;
    CurCh         = Data+CurPos;
  }
  
  if (CurPos >= BufferData.size())
    return 0;                   // EOF

  if (*CurCh == '+') {
    CurPos++;
    return PLUS;
  } else if (*CurCh == '-') {
    CurPos++;
    return MINUS;
  } else if (*CurCh == '*') {
    CurPos++;
    return ASTERISK;
  } else if (*CurCh == '/') {
    CurPos++;
    return SLASH;
  } else if (*CurCh == '$') {
    CurPos++;
    return DOLLAR;
  } else if (*CurCh == '@') {
    CurPos++;
    return AT;
  } else if (IsAlpha(*CurCh)) {
    const char *Start  = CurCh;
    size_t      Length = 0;
    
    do {
      Length++;
      CurPos++;
      CurCh = Data+CurPos;

    } while (CurPos < BufferData.size() && (IsAlphaOrDigit(*CurCh) || *CurCh == '_'));

    StringRef *Str = new StringRef(Start, Length);

    // Check for keywords
    if (Str->compare("double")   == 0) {
      return DOUBLE;
    } else if (Str->compare("field")    == 0) {
      return FIELD;
    } else if (Str->compare("float")    == 0) {
      return FLOAT;
    } else if (Str->compare("grid")     == 0) {
      return GRID;
    } else if (Str->compare("in")       == 0) {
      return IN;
    } else if (Str->compare("inout")    == 0) {
      return INOUT;
    } else if (Str->compare("is")       == 0) {
      return IS;
    } else if (Str->compare("let")      == 0) {
      return LET;
    } else if (Str->compare("out")      == 0) {
      return OUT;
    } else if (Str->compare("param")    == 0) {
      return PARAM;
    } else if (Str->compare("program")  == 0) {
      return PROGRAM;
    }

    // Not a keyword
    InternedStrings.push_back(Str);
    Value->Ident        = Str;
    return IDENT;
  } else if (IsDigit(*CurCh)) {
    const char *Start   = CurCh;
    size_t      Length  = 0;
    bool        IsFloat = false;
      
    do {
      if (*CurCh == '.') IsFloat = true;
      
      Length++;
      CurPos++;
      CurCh = Data+CurPos;
      
    } while (CurPos < BufferData.size() && (IsDigit(*CurCh) || *CurCh == '.'));

    if (CurPos < BufferData.size() && (*CurCh == 'e' || *CurCh == 'E')) {
      // Start of an exponent

      IsFloat = true;
      
      CurPos++;
      CurCh = Data+CurPos;
      Length++;
      
      if (CurPos == BufferData.size() || (!IsDigit(*CurCh) && *CurCh != '-')) {
        SrcMgr.PrintMessage(SMLoc::getFromPointer(Data+CurPos),
                            SourceMgr::DK_Error, "Missing exponent");
        return 0;
      }

      if (*CurCh == '-') {
        Length++;
        CurPos++;
        CurCh = Data+CurPos;

        if (CurPos == BufferData.size() || !IsDigit(*CurCh)) {
          SrcMgr.PrintMessage(SMLoc::getFromPointer(Data+CurPos),
                              SourceMgr::DK_Error, "Missing exponent");
          return 0;
        }
      }

      do {
        Length++;
        CurPos++;
        CurCh = Data+CurPos;
      
      } while (CurPos < BufferData.size() && IsDigit(*CurCh));

    }
    
    StringRef Str = StringRef(Start, Length);

    if (IsFloat) {
      APFloat DoubleValue = APFloat(APFloat::IEEEdouble, Str);
      Value->DoubleConst  = DoubleValue.convertToDouble();
      return DOUBLECONST;
    } else {
      long    IntValue    = atol(Str.data());
      Value->IntConst     = IntValue;
      return INTCONST;
    }
  } else if (*CurCh == '=') {
    CurPos++;
    return EQUALS;
  } else if (*CurCh == '(') {
    CurPos++;
    return OPENPARENS;
  } else if (*CurCh == ')') {
    CurPos++;
    return CLOSEPARENS;
  } else if (*CurCh == '[') {
    CurPos++;
    return OPENBRACE;
  } else if (*CurCh == ']') {
    CurPos++;
    return CLOSEBRACE;
  } else if (*CurCh == ',') {
    CurPos++;
    return COMMA;
  } else if (*CurCh == ':') {
    CurPos++;
    return COLON;
  }

  CurPos++;
  // If we get here, then we have no idea how to lex this!
  printError("Unknown symbol");
  
  return 0;
}