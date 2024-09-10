static void ColouriseMSSQLDoc(unsigned int startPos, int length,
                              int initStyle, WordList *keywordlists[], Accessor &styler) {


  styler.StartAt(startPos);

  bool fold = styler.GetPropertyInt("fold") != 0;
  int lineCurrent = styler.GetLine(startPos);
  int spaceFlags = 0;

  int state = initStyle;
  int prevState = initStyle;
  char chPrev = ' ';
  char chNext = styler[startPos];
  styler.StartSegment(startPos);
  unsigned int lengthDoc = startPos + length;
  for (unsigned int i = startPos; i < lengthDoc; i++) {
    char ch = chNext;
    chNext = styler.SafeGetCharAt(i + 1);

    if ((ch == '\r' && chNext != '\n') || (ch == '\n')) {
      int indentCurrent = styler.IndentAmount(lineCurrent, &spaceFlags);
      int lev = indentCurrent;
      if (!(indentCurrent & SC_FOLDLEVELWHITEFLAG)) {
        // Only non whitespace lines can be headers
        int indentNext = styler.IndentAmount(lineCurrent + 1, &spaceFlags);
        if (indentCurrent < (indentNext & ~SC_FOLDLEVELWHITEFLAG)) {
          lev |= SC_FOLDLEVELHEADERFLAG;
        }
      }
      if (fold) {
        styler.SetLevel(lineCurrent, lev);
      }
    }

    if (styler.IsLeadByte(ch)) {
      chNext = styler.SafeGetCharAt(i + 2);
      chPrev = ' ';
      i += 1;
      continue;
    }

    // When the last char isn't part of the state (have to deal with it too)...
    if ( (state == SCE_MSSQL_IDENTIFIER) ||
                    (state == SCE_MSSQL_STORED_PROCEDURE) ||
                    (state == SCE_MSSQL_DATATYPE) ||
                    //~ (state == SCE_MSSQL_COLUMN_NAME) ||
                    (state == SCE_MSSQL_FUNCTION) ||
                    //~ (state == SCE_MSSQL_GLOBAL_VARIABLE) ||
                    (state == SCE_MSSQL_VARIABLE)) {
      if (!iswordchar(ch)) {
        int stateTmp;

                if ((state == SCE_MSSQL_VARIABLE) || (state == SCE_MSSQL_COLUMN_NAME)) {
                    styler.ColourTo(i - 1, state);
          stateTmp = state;
                } else
                    stateTmp = classifyWordSQL(styler.GetStartSegment(), i - 1, keywordlists, styler, state, prevState);

        prevState = state;

        if (stateTmp == SCE_MSSQL_IDENTIFIER || stateTmp == SCE_MSSQL_VARIABLE)
          state = SCE_MSSQL_DEFAULT_PREF_DATATYPE;
        else
          state = SCE_MSSQL_DEFAULT;
      }
    } else if (state == SCE_MSSQL_LINE_COMMENT) {
      if (ch == '\r' || ch == '\n') {
        styler.ColourTo(i - 1, state);
        prevState = state;
        state = SCE_MSSQL_DEFAULT;
      }
    } else if (state == SCE_MSSQL_GLOBAL_VARIABLE) {
      if ((ch != '@') && !iswordchar(ch)) {
        classifyWordSQL(styler.GetStartSegment(), i - 1, keywordlists, styler, state, prevState);
        prevState = state;
        state = SCE_MSSQL_DEFAULT;
      }
    }

    // If is the default or one of the above succeeded
    if (state == SCE_MSSQL_DEFAULT || state == SCE_MSSQL_DEFAULT_PREF_DATATYPE) {
      if (iswordstart(ch)) {
        styler.ColourTo(i - 1, SCE_MSSQL_DEFAULT);
        prevState = state;
        state = SCE_MSSQL_IDENTIFIER;
      } else if (ch == '/' && chNext == '*') {
        styler.ColourTo(i - 1, SCE_MSSQL_DEFAULT);
        prevState = state;
        state = SCE_MSSQL_COMMENT;
      } else if (ch == '-' && chNext == '-') {
        styler.ColourTo(i - 1, SCE_MSSQL_DEFAULT);
        prevState = state;
        state = SCE_MSSQL_LINE_COMMENT;
      } else if (ch == '\'') {
        styler.ColourTo(i - 1, SCE_MSSQL_DEFAULT);
        prevState = state;
        state = SCE_MSSQL_STRING;
      } else if (ch == '"') {
        styler.ColourTo(i - 1, SCE_MSSQL_DEFAULT);
        prevState = state;
        state = SCE_MSSQL_COLUMN_NAME;
      } else if (ch == '[') {
        styler.ColourTo(i - 1, SCE_MSSQL_DEFAULT);
        prevState = state;
        state = SCE_MSSQL_COLUMN_NAME_2;
      } else if (isoperator(ch)) {
        styler.ColourTo(i - 1, SCE_MSSQL_DEFAULT);
        styler.ColourTo(i, SCE_MSSQL_OPERATOR);
                //~ style = SCE_MSSQL_DEFAULT;
        prevState = state;
        state = SCE_MSSQL_DEFAULT;
      } else if (ch == '@') {
                styler.ColourTo(i - 1, SCE_MSSQL_DEFAULT);
        prevState = state;
                if (chNext == '@') {
                    state = SCE_MSSQL_GLOBAL_VARIABLE;
//                    i += 2;
                } else
                    state = SCE_MSSQL_VARIABLE;
            }


    // When the last char is part of the state...
    } else if (state == SCE_MSSQL_COMMENT) {
        if (ch == '/' && chPrev == '*') {
          if (((i > (styler.GetStartSegment() + 2)) || ((initStyle == SCE_MSSQL_COMMENT) &&
              (styler.GetStartSegment() == startPos)))) {
            styler.ColourTo(i, state);
            //~ state = SCE_MSSQL_COMMENT;
          prevState = state;
                        state = SCE_MSSQL_DEFAULT;
          }
        }
      } else if (state == SCE_MSSQL_STRING) {
        if (ch == '\'') {
          if ( chNext == '\'' ) {
            i++;
          ch = chNext;
          chNext = styler.SafeGetCharAt(i + 1);
          } else {
            styler.ColourTo(i, state);
          prevState = state;
            state = SCE_MSSQL_DEFAULT;
          //i++;
          }
        //ch = chNext;
        //chNext = styler.SafeGetCharAt(i + 1);
        }
      } else if (state == SCE_MSSQL_COLUMN_NAME) {
        if (ch == '"') {
          if (chNext == '"') {
            i++;
          ch = chNext;
          chNext = styler.SafeGetCharAt(i + 1);
        } else {
                    styler.ColourTo(i, state);
          prevState = state;
          state = SCE_MSSQL_DEFAULT_PREF_DATATYPE;
          //i++;
                }
                }
    } else if (state == SCE_MSSQL_COLUMN_NAME_2) {
      if (ch == ']') {
                styler.ColourTo(i, state);
        prevState = state;
                state = SCE_MSSQL_DEFAULT_PREF_DATATYPE;
                //i++;
      }
    }

    chPrev = ch;
  }
  styler.ColourTo(lengthDoc - 1, state);
}