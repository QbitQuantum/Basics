void jslGetNextToken(JsLex *lex) {
  jslGetNextToken_start:
  // Skip whitespace
  while (isWhitespace(lex->currCh))
    jslGetNextCh(lex);
  // Search for comments
  if (lex->currCh=='/') {
    // newline comments
    if (jslNextCh(lex)=='/') {
      while (lex->currCh && lex->currCh!='\n') jslGetNextCh(lex);
      jslGetNextCh(lex);
      goto jslGetNextToken_start;
    }
    // block comments
    if (jslNextCh(lex)=='*') {
      while (lex->currCh && !(lex->currCh=='*' && jslNextCh(lex)=='/'))
        jslGetNextCh(lex);
      if (!lex->currCh) {
        lex->tk = LEX_UNFINISHED_COMMENT;
        return; /* an unfinished multi-line comment. When in interactive console,
                   detect this and make sure we accept new lines */
      }
      jslGetNextCh(lex);
      jslGetNextCh(lex);
      goto jslGetNextToken_start;
    }
  }
  lex->tk = LEX_EOF;
  lex->tokenl = 0; // clear token string
  if (lex->tokenValue) {
    jsvUnLock(lex->tokenValue);
    lex->tokenValue = 0;
  }
  // record beginning of this token
  lex->tokenLastStart = jsvStringIteratorGetIndex(&lex->tokenStart.it) - 1;
  /* we don't lock here, because we know that the string itself will be locked
   * because of lex->sourceVar */
  lex->tokenStart.it = lex->it;
  lex->tokenStart.currCh = lex->currCh;
  // tokens
  if (((unsigned char)lex->currCh) < jslJumpTableStart ||
      ((unsigned char)lex->currCh) > jslJumpTableEnd) {
    // if unhandled by the jump table, just pass it through as a single character
    jslSingleChar(lex);
  } else {
    switch(jslJumpTable[((unsigned char)lex->currCh) - jslJumpTableStart]) {
    case JSLJT_ID: {
      while (isAlpha(lex->currCh) || isNumeric(lex->currCh) || lex->currCh=='$') {
        jslTokenAppendChar(lex, lex->currCh);
        jslGetNextCh(lex);
      }
      lex->tk = LEX_ID;
      // We do fancy stuff here to reduce number of compares (hopefully GCC creates a jump table)
      switch (lex->token[0]) {
      case 'b': if (jslIsToken(lex,"break", 1)) lex->tk = LEX_R_BREAK;
      break;
      case 'c': if (jslIsToken(lex,"case", 1)) lex->tk = LEX_R_CASE;
      else if (jslIsToken(lex,"catch", 1)) lex->tk = LEX_R_CATCH;
      else if (jslIsToken(lex,"continue", 1)) lex->tk = LEX_R_CONTINUE;
      break;
      case 'd': if (jslIsToken(lex,"default", 1)) lex->tk = LEX_R_DEFAULT;
      else if (jslIsToken(lex,"delete", 1)) lex->tk = LEX_R_DELETE;
      else if (jslIsToken(lex,"do", 1)) lex->tk = LEX_R_DO;
      else if (jslIsToken(lex,"debugger", 1)) lex->tk = LEX_R_DEBUGGER;
      break;
      case 'e': if (jslIsToken(lex,"else", 1)) lex->tk = LEX_R_ELSE;
      break;
      case 'f': if (jslIsToken(lex,"false", 1)) lex->tk = LEX_R_FALSE;
      else if (jslIsToken(lex,"finally", 1)) lex->tk = LEX_R_FINALLY;
      else if (jslIsToken(lex,"for", 1)) lex->tk = LEX_R_FOR;
      else if (jslIsToken(lex,"function", 1)) lex->tk = LEX_R_FUNCTION;
      break;
      case 'i': if (jslIsToken(lex,"if", 1)) lex->tk = LEX_R_IF;
      else if (jslIsToken(lex,"in", 1)) lex->tk = LEX_R_IN;
      else if (jslIsToken(lex,"instanceof", 1)) lex->tk = LEX_R_INSTANCEOF;
      break;
      case 'n': if (jslIsToken(lex,"new", 1)) lex->tk = LEX_R_NEW;
      else if (jslIsToken(lex,"null", 1)) lex->tk = LEX_R_NULL;
      break;
      case 'r': if (jslIsToken(lex,"return", 1)) lex->tk = LEX_R_RETURN;
      break;
      case 's': if (jslIsToken(lex,"switch", 1)) lex->tk = LEX_R_SWITCH;
      break;
      case 't': if (jslIsToken(lex,"this", 1)) lex->tk = LEX_R_THIS;
      else if (jslIsToken(lex,"throw", 1)) lex->tk = LEX_R_THROW;
      else if (jslIsToken(lex,"true", 1)) lex->tk = LEX_R_TRUE;
      else if (jslIsToken(lex,"try", 1)) lex->tk = LEX_R_TRY;
      else if (jslIsToken(lex,"typeof", 1)) lex->tk = LEX_R_TYPEOF;
      break;
      case 'u': if (jslIsToken(lex,"undefined", 1)) lex->tk = LEX_R_UNDEFINED;
      break;
      case 'w': if (jslIsToken(lex,"while", 1)) lex->tk = LEX_R_WHILE;
      break;
      case 'v': if (jslIsToken(lex,"var", 1)) lex->tk = LEX_R_VAR;
      else if (jslIsToken(lex,"void", 1)) lex->tk = LEX_R_VOID;
      break;
      default: break;
      } break;
      case JSLJT_NUMBER: {
        // TODO: check numbers aren't the wrong format
        bool canBeFloating = true;
        if (lex->currCh=='.') {
          jslGetNextCh(lex);
          if (isNumeric(lex->currCh)) {
            // it is a float
            lex->tk = LEX_FLOAT;
            jslTokenAppendChar(lex, '.');
          } else {
            // it wasn't a number after all
            lex->tk = '.';
            break;
          }
        } else {
          if (lex->currCh=='0') {
            jslTokenAppendChar(lex, lex->currCh);
            jslGetNextCh(lex);
            if ((lex->currCh=='x' || lex->currCh=='X') ||
                (lex->currCh=='b' || lex->currCh=='B') ||
                (lex->currCh=='o' || lex->currCh=='O')) {
              canBeFloating = false;
              jslTokenAppendChar(lex, lex->currCh); jslGetNextCh(lex);
            }
          }
          lex->tk = LEX_INT;
          while (isNumeric(lex->currCh) || (!canBeFloating && isHexadecimal(lex->currCh))) {
            jslTokenAppendChar(lex, lex->currCh);
            jslGetNextCh(lex);
          }
          if (canBeFloating && lex->currCh=='.') {
            lex->tk = LEX_FLOAT;
            jslTokenAppendChar(lex, '.');
            jslGetNextCh(lex);
          }
        }
        // parse fractional part
        if (lex->tk == LEX_FLOAT) {
          while (isNumeric(lex->currCh)) {
            jslTokenAppendChar(lex, lex->currCh);
            jslGetNextCh(lex);
          }
        }
        // do fancy e-style floating point
        if (canBeFloating && (lex->currCh=='e'||lex->currCh=='E')) {
          lex->tk = LEX_FLOAT;
          jslTokenAppendChar(lex, lex->currCh); jslGetNextCh(lex);
          if (lex->currCh=='-' || lex->currCh=='+') { jslTokenAppendChar(lex, lex->currCh); jslGetNextCh(lex); }
          while (isNumeric(lex->currCh)) {
            jslTokenAppendChar(lex, lex->currCh); jslGetNextCh(lex);
          }
        }
      } break;
      case JSLJT_STRING:
      {
        char delim = lex->currCh;
        lex->tokenValue = jsvNewFromEmptyString();
        if (!lex->tokenValue) {
          lex->tk = LEX_EOF;
          return;
        }
        JsvStringIterator it;
        jsvStringIteratorNew(&it, lex->tokenValue, 0);
        // strings...
        jslGetNextCh(lex);
        while (lex->currCh && lex->currCh!=delim) {
          if (lex->currCh == '\\') {
            jslGetNextCh(lex);
            char ch = lex->currCh;
            switch (lex->currCh) {
            case 'n'  : ch = 0x0A; jslGetNextCh(lex); break;
            case 'b'  : ch = 0x08; jslGetNextCh(lex); break;
            case 'f'  : ch = 0x0C; jslGetNextCh(lex); break;
            case 'r'  : ch = 0x0D; jslGetNextCh(lex); break;
            case 't'  : ch = 0x09; jslGetNextCh(lex); break;
            case 'v'  : ch = 0x0B; jslGetNextCh(lex); break;
            case 'u' :
            case 'x' : { // hex digits
              char buf[5] = "0x??";
              if (lex->currCh == 'u') {
                // We don't support unicode, so we just take the bottom 8 bits
                // of the unicode character
                jslGetNextCh(lex);
                jslGetNextCh(lex);
              }
              jslGetNextCh(lex);
              buf[2] = lex->currCh; jslGetNextCh(lex);
              buf[3] = lex->currCh; jslGetNextCh(lex);
              ch = (char)stringToInt(buf);
            } break;
            default:
              if (lex->currCh>='0' && lex->currCh<='7') {
                // octal digits
                char buf[5] = "0";
                buf[1] = lex->currCh;
                int n=2;
                jslGetNextCh(lex);
                if (lex->currCh>='0' && lex->currCh<='7') {
                  buf[n++] = lex->currCh; jslGetNextCh(lex);
                  if (lex->currCh>='0' && lex->currCh<='7') {
                    buf[n++] = lex->currCh; jslGetNextCh(lex);
                  }
                }
                buf[n]=0;
                ch = (char)stringToInt(buf);
              } else {
                // for anything else, just push the character through
                jslGetNextCh(lex);
              }
              break;
            }
            jslTokenAppendChar(lex, ch);
            jsvStringIteratorAppend(&it, ch);
          } else {
            jslTokenAppendChar(lex, lex->currCh);
            jsvStringIteratorAppend(&it, lex->currCh);
            jslGetNextCh(lex);
          }
        }
        jsvStringIteratorFree(&it);
        jslGetNextCh(lex);
        lex->tk = LEX_STR;
      } break;
      case JSLJT_EXCLAMATION: jslSingleChar(lex);
      if (lex->currCh=='=') { // !=
        lex->tk = LEX_NEQUAL;
        jslGetNextCh(lex);
        if (lex->currCh=='=') { // !==
          lex->tk = LEX_NTYPEEQUAL;
          jslGetNextCh(lex);
        }
      } break;
      case JSLJT_PLUS: jslSingleChar(lex);
      if (lex->currCh=='=') {
        lex->tk = LEX_PLUSEQUAL;
        jslGetNextCh(lex);
      } else if (lex->currCh=='+') {
        lex->tk = LEX_PLUSPLUS;
        jslGetNextCh(lex);
      } break;
      case JSLJT_MINUS: jslSingleChar(lex);
      if (lex->currCh=='=') {
        lex->tk = LEX_MINUSEQUAL;
        jslGetNextCh(lex);
      } else if (lex->currCh=='-') {
        lex->tk = LEX_MINUSMINUS;
        jslGetNextCh(lex);
      } break;
      case JSLJT_AND: jslSingleChar(lex);
      if (lex->currCh=='=') {
        lex->tk = LEX_ANDEQUAL;
        jslGetNextCh(lex);
      } else if (lex->currCh=='&') {
        lex->tk = LEX_ANDAND;
        jslGetNextCh(lex);
      } break;
      case JSLJT_OR: jslSingleChar(lex);
      if (lex->currCh=='=') {
        lex->tk = LEX_OREQUAL;
        jslGetNextCh(lex);
      } else if (lex->currCh=='|') {
        lex->tk = LEX_OROR;
        jslGetNextCh(lex);
      } break;
      case JSLJT_TOPHAT: jslSingleChar(lex);
      if (lex->currCh=='=') {
        lex->tk = LEX_XOREQUAL;
        jslGetNextCh(lex);
      } break;
      case JSLJT_STAR: jslSingleChar(lex);
      if (lex->currCh=='=') {
        lex->tk = LEX_MULEQUAL;
        jslGetNextCh(lex);
      } break;
      case JSLJT_FORWARDSLASH: jslSingleChar(lex);
      if (lex->currCh=='=') {
        lex->tk = LEX_DIVEQUAL;
        jslGetNextCh(lex);
      } break;
      case JSLJT_PERCENT: jslSingleChar(lex);
      if (lex->currCh=='=') {
        lex->tk = LEX_MODEQUAL;
        jslGetNextCh(lex);
      } break;
      case JSLJT_EQUAL: jslSingleChar(lex);
      if (lex->currCh=='=') { // ==
        lex->tk = LEX_EQUAL;
        jslGetNextCh(lex);
        if (lex->currCh=='=') { // ===
          lex->tk = LEX_TYPEEQUAL;
          jslGetNextCh(lex);
        }
      } break;
      case JSLJT_LESSTHAN: jslSingleChar(lex);
      if (lex->currCh=='=') { // <=
        lex->tk = LEX_LEQUAL;
        jslGetNextCh(lex);
      } else if (lex->currCh=='<') { // <<
        lex->tk = LEX_LSHIFT;
        jslGetNextCh(lex);
        if (lex->currCh=='=') { // <<=
          lex->tk = LEX_LSHIFTEQUAL;
          jslGetNextCh(lex);
        }
      } break;
      case JSLJT_GREATERTHAN: jslSingleChar(lex);
      if (lex->currCh=='=') { // >=
        lex->tk = LEX_GEQUAL;
        jslGetNextCh(lex);
      } else if (lex->currCh=='>') { // >>
        lex->tk = LEX_RSHIFT;
        jslGetNextCh(lex);
        if (lex->currCh=='=') { // >>=
          lex->tk = LEX_RSHIFTEQUAL;
          jslGetNextCh(lex);
        } else if (lex->currCh=='>') { // >>>
          jslGetNextCh(lex);
          if (lex->currCh=='=') { // >>>=
            lex->tk = LEX_RSHIFTUNSIGNEDEQUAL;
            jslGetNextCh(lex);
          } else {
            lex->tk = LEX_RSHIFTUNSIGNED;
          }
        }
      } break;

      case JSLJT_SINGLECHAR: jslSingleChar(lex); break;
      default: assert(0);break;
    }
    }
  }
}