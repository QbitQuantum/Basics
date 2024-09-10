  void ByteSink::Vprintf(const char * format, va_list & ap)
  {
    MFM_API_ASSERT_NONNULL(format);

    u8 p;
    Format::Type type;
    bool alt;
    s32 fieldWidth;
    u8 padChar;
    while ((p = *format++)) {
      if (p != '%') {
        if (p == '\n')          // '\n's _in_the_format_string_ are
          Println();            // treated as packet delimiters!
        else
          Print(p,Format::BYTE);
        continue;
      }

    alt = false;
    fieldWidth = -1;
    padChar = ' ';
  again:
    switch (p = *format++) {
    case '#': alt = true; goto again;

    case '0':
      if (fieldWidth < 0) {
        padChar = '0';
        fieldWidth = 0;
      } else fieldWidth *= 10;
      goto again;

    case '1': case '2': case '3': case '4': case '5':
    case '6': case '7': case '8': case '9':
      if (fieldWidth < 0) fieldWidth = 0;
      fieldWidth = fieldWidth * 10 + (p - '0');
      goto again;

    case 'c':
      {
        u32 ch = va_arg(ap,int);
        if (!alt || IsPrint(ch)) Print(ch,Format::BYTE);
        else {
          Print('[',Format::BYTE);
          if (ch < 0x10)
            Print('0', Format::BYTE);
          Print(ch, Format::HEX);
          Print(']', Format::BYTE);
        }
      }
      break;

    case '<':  // Print the rest of a given &ByteSource
      {
        ByteSource * bs = va_arg(ap,ByteSource*);
        if (!bs) Print("(null)");
        else Copy(*bs);
      }
      break;

    case '@':
      {
        s32 argument = 0;
        if (alt) argument = va_arg(ap,s32);
        ByteSerializable * bs = va_arg(ap,ByteSerializable*);
        if (!bs) Print("(null)");
        else Print(*bs, argument);
      }
      break;

    case 'q':
      Print(va_arg(ap,u64), Format::BEU64);
      break;
    case 'H': type = Format::LEXHD; goto print;
    case 'h': type = Format::BEU16; goto print;
    case 'l': type = Format::BEU32; goto print;

    case 'b': type = Format::BIN; goto printbase;
    case 'o': type = Format::OCT; goto printbase;
    case 'u': type = Format::DEC; goto printbase;
    case 'd':
      if (alt) {
        type = Format::DEC;
        goto printbase;
      } else {
        Print(va_arg(ap,s32), fieldWidth, padChar);
        break;
      }
    case 'x': type = Format::HEX; goto printbase;
    case 't': type = Format::B36; goto printbase;

    case 'D': type = Format::LEX32; goto print;
    case 'X': type = Format::LXX32; goto print;

    printbase:
      PrintInBase(va_arg(ap,u32), type, fieldWidth, padChar);
      break;
    print:
      Print(va_arg(ap,u32),type, fieldWidth, padChar);
      break;

    case 'f': 
    {
      FAIL(INCOMPLETE_CODE);
      /*
      double v =  va_arg(ap,double);
      ByteSink::Print(face,v);
      break;
      */
    }

    /* %Z: Print a null-terminated string INCLUDING a trailing NULL */
    case 'Z': 
    {
      const char * s = va_arg(ap,const char *);
      if (!s) Print("(null)", fieldWidth, padChar);
      else Print(s, fieldWidth, padChar);
    }
    /* FALL THROUGH */
    /* %z: Print a null byte.  Consumes no args */
    case 'z': 
      WriteByte('\0');
      break;

    case 's': {
      const char * s = va_arg(ap,const char *);
      if (!s) Print("(null)", fieldWidth, padChar);
      else Print(s, fieldWidth, padChar);
      break;
    }

    case 'S': {
      const char * s = va_arg(ap,const char *);
      if (!s) Print("(null)", fieldWidth, padChar);
      else PrintDoubleQuotedCStringWithLength(s);
      break;
    }

    case 'p': {
      const void * p = va_arg(ap,void *);
      if (!p) Print("(nullp)");
      else {
        Print("0x");
        Print((uptr) p, Format::HEX);
      }
      break;
    }

    case '%':
      Print(p, Format::BYTE);
      break;

    default:                    // Either I don't know that code, or you're bogus.
      FAIL(BAD_FORMAT_ARG);     // Either way, I die.  You're welcome.
    }
    }
  }