/// Map Farsi keyboard when in fkmap mode.
int fkmap(int c)
{
  int tempc;
  static int revins;

  if (IS_SPECIAL(c)) {
    return c;
  }

  if (VIM_ISDIGIT(c)
      || (((c == '.')
           || (c == '+')
           || (c == '-')
           || (c == '^')
           || (c == '%')
           || (c == '#')
           || (c == '='))
          && revins)) {
    if (!revins) {
      if (curwin->w_cursor.col) {
        if (!p_ri) {
          dec_cursor();
        }

        chg_c_toX_orX();
        chg_l_toXor_X();
        if (!p_ri) {
          inc_cursor();
        }
      }
    }

    arrow_used = TRUE;
    (void)stop_arrow();

    if (!curwin->w_p_rl && revins) {
      inc_cursor();
    }

    revins++;
    p_ri = 1;
  } else {
    if (revins) {
      arrow_used = TRUE;
      (void)stop_arrow();

      revins = 0;
      if (curwin->w_p_rl) {
        while ((F_isdigit(gchar_cursor())
                || (gchar_cursor() == F_PERIOD
                    || gchar_cursor() == F_PLUS
                    || gchar_cursor() == F_MINUS
                    || gchar_cursor() == F_MUL
                    || gchar_cursor() == F_DIVIDE
                    || gchar_cursor() == F_PERCENT
                    || gchar_cursor() == F_EQUALS))
                && gchar_cursor() != '\0') {
          curwin->w_cursor.col++;
        }
      } else {
        if (curwin->w_cursor.col) {
          while ((F_isdigit(gchar_cursor())
                 || (gchar_cursor() == F_PERIOD
                     || gchar_cursor() == F_PLUS
                     || gchar_cursor() == F_MINUS
                     || gchar_cursor() == F_MUL
                     || gchar_cursor() == F_DIVIDE
                     || gchar_cursor() == F_PERCENT
                     || gchar_cursor() == F_EQUALS))
                 && --curwin->w_cursor.col) {
          }
        }

        if (!F_isdigit(gchar_cursor())) {
          ++curwin->w_cursor.col;
        }
      }
    }
  }

  if (!revins) {
    if (curwin->w_p_rl) {
      p_ri = 0;
    }

    if (!curwin->w_p_rl) {
      p_ri = 1;
    }
  }

  if ((c < 0x100) &&
      (isalpha(c) ||
       (c == '&') ||
       (c == '^') ||
       (c == ';') ||
       (c == '\'') ||
       (c == ',') ||
       (c == '[') ||
       (c == ']') ||
       (c == '{') ||
       (c == '}'))) {
    chg_r_to_Xor_X_();
  }

  tempc = 0;
  switch (c) {
    case '`':
    case ' ':
    case '.':
    case '!':
    case '"':
    case '$':
    case '%':
    case '^':
    case '&':
    case '/':
    case '(':
    case ')':
    case '=':
    case '\\':
    case '?':
    case '+':
    case '-':
    case '_':
    case '*':
    case ':':
    case '#':
    case '~':
    case '@':
    case '<':
    case '>':
    case '{':
    case '}':
    case '|':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case 'B':
    case 'E':
    case 'F':
    case 'H':
    case 'I':
    case 'K':
    case 'L':
    case 'M':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'T':
    case 'U':
    case 'W':
    case 'Y':
    case  NL:
    case  TAB:
      if (p_ri && (c == NL) && curwin->w_cursor.col) {
        // If the char before the cursor is _X_ or X_ do not change
        // the one under the cursor with X type.

        dec_cursor();
        if (F_isalpha(gchar_cursor())) {
          inc_cursor();
          return NL;
        }
        inc_cursor();
      }

      if (!p_ri) {
        if (!curwin->w_cursor.col) {
          switch (c) {
            case '0':
              return FARSI_0;

            case '1':
              return FARSI_1;

            case '2':
              return FARSI_2;

            case '3':
              return FARSI_3;

            case '4':
              return FARSI_4;

            case '5':
              return FARSI_5;

            case '6':
              return FARSI_6;

            case '7':
              return FARSI_7;

            case '8':
              return FARSI_8;

            case '9':
              return FARSI_9;

            case 'B':
              return F_PSP;

            case 'E':
              return JAZR_N;

            case 'F':
              return ALEF_D_H;

            case 'H':
              return ALEF_A;

            case 'I':
              return TASH;

            case 'K':
              return F_LQUOT;

            case 'L':
              return F_RQUOT;

            case 'M':
              return HAMZE;

            case 'O':
              return '[';

            case 'P':
              return ']';

            case 'Q':
              return OO;

            case 'R':
              return MAD_N;

            case 'T':
              return OW;

            case 'U':
              return MAD;

            case 'W':
              return OW_OW;

            case 'Y':
              return JAZR;

            case '`':
              return F_PCN;

            case '!':
              return F_EXCL;

            case '@':
              return F_COMMA;

            case '#':
              return F_DIVIDE;

            case '$':
              return F_CURRENCY;

            case '%':
              return F_PERCENT;

            case '^':
              return F_MUL;

            case '&':
              return F_BCOMMA;

            case '*':
              return F_STAR;

            case '(':
              return F_LPARENT;

            case ')':
              return F_RPARENT;

            case '-':
              return F_MINUS;

            case '_':
              return F_UNDERLINE;

            case '=':
              return F_EQUALS;

            case '+':
              return F_PLUS;

            case '\\':
              return F_BSLASH;

            case '|':
              return F_PIPE;

            case ':':
              return F_DCOLON;

            case '"':
              return F_SEMICOLON;

            case '.':
              return F_PERIOD;

            case '/':
              return F_SLASH;

            case '<':
              return F_LESS;

            case '>':
              return F_GREATER;

            case '?':
              return F_QUESTION;

            case ' ':
              return F_BLANK;
          }
          break;
        }
      }

      if (!p_ri) {
        dec_cursor();
      }

      switch ((tempc = gchar_cursor())) {
        case _BE:
        case _PE:
        case _TE:
        case _SE:
        case _JIM:
        case _CHE:
        case _HE_J:
        case _XE:
        case _SIN:
        case _SHIN:
        case _SAD:
        case _ZAD:
        case _FE:
        case _GHAF:
        case _KAF:
        case _KAF_H:
        case _GAF:
        case _LAM:
        case _MIM:
        case _NOON:
        case _HE:
        case _HE_:
        case _TA:
        case _ZA:
          put_curr_and_l_to_X(toF_TyA(tempc));
          break;

        case _AYN:
        case _AYN_:
          if (!p_ri) {
            if (!curwin->w_cursor.col) {
              put_curr_and_l_to_X(AYN);
              break;
            }
          }

          if (p_ri) {
            inc_cursor();
          } else {
            dec_cursor();
          }

          if (F_is_TyB_TyC_TyD(SRC_EDT, AT_CURSOR)) {
            tempc = AYN_;
          } else {
            tempc = AYN;
          }

          if (p_ri) {
            dec_cursor();
          } else {
            inc_cursor();
          }

          put_curr_and_l_to_X(tempc);
          break;

        case _GHAYN:
        case _GHAYN_:

          if (!p_ri) {
            if (!curwin->w_cursor.col) {
              put_curr_and_l_to_X(GHAYN);
              break;
            }
          }

          if (p_ri) {
            inc_cursor();
          } else {
            dec_cursor();
          }

          if (F_is_TyB_TyC_TyD(SRC_EDT, AT_CURSOR)) {
            tempc = GHAYN_;
          } else {
            tempc = GHAYN;
          }

          if (p_ri) {
            dec_cursor();
          } else {
            inc_cursor();
          }

          put_curr_and_l_to_X(tempc);
          break;

        case _YE:
        case _IE:
        case _YEE:

          if (!p_ri) {
            if (!curwin->w_cursor.col) {
              put_curr_and_l_to_X((tempc == _YE ? YE :
                                   (tempc == _IE ? IE : YEE)));
              break;
            }
          }

          if (p_ri) {
            inc_cursor();
          } else {
            dec_cursor();
          }

          if (F_is_TyB_TyC_TyD(SRC_EDT, AT_CURSOR)) {
            tempc = (tempc == _YE ? YE_ :
                     (tempc == _IE ? IE_ : YEE_));
          } else {
            tempc = (tempc == _YE ? YE :
                     (tempc == _IE ? IE : YEE));
          }

          if (p_ri) {
            dec_cursor();
          } else {
            inc_cursor();
          }

          put_curr_and_l_to_X(tempc);
          break;
      }

      if (!p_ri) {
        inc_cursor();
      }

      tempc = 0;

      switch (c) {
        case '0':
          return FARSI_0;

        case '1':
          return FARSI_1;

        case '2':
          return FARSI_2;

        case '3':
          return FARSI_3;

        case '4':
          return FARSI_4;

        case '5':
          return FARSI_5;

        case '6':
          return FARSI_6;

        case '7':
          return FARSI_7;

        case '8':
          return FARSI_8;

        case '9':
          return FARSI_9;

        case 'B':
          return F_PSP;

        case 'E':
          return JAZR_N;

        case 'F':
          return ALEF_D_H;

        case 'H':
          return ALEF_A;

        case 'I':
          return TASH;

        case 'K':
          return F_LQUOT;

        case 'L':
          return F_RQUOT;

        case 'M':
          return HAMZE;

        case 'O':
          return '[';

        case 'P':
          return ']';

        case 'Q':
          return OO;

        case 'R':
          return MAD_N;

        case 'T':
          return OW;

        case 'U':
          return MAD;

        case 'W':
          return OW_OW;

        case 'Y':
          return JAZR;

        case '`':
          return F_PCN;

        case '!':
          return F_EXCL;

        case '@':
          return F_COMMA;

        case '#':
          return F_DIVIDE;

        case '$':
          return F_CURRENCY;

        case '%':
          return F_PERCENT;

        case '^':
          return F_MUL;

        case '&':
          return F_BCOMMA;

        case '*':
          return F_STAR;

        case '(':
          return F_LPARENT;

        case ')':
          return F_RPARENT;

        case '-':
          return F_MINUS;

        case '_':
          return F_UNDERLINE;

        case '=':
          return F_EQUALS;

        case '+':
          return F_PLUS;

        case '\\':
          return F_BSLASH;

        case '|':
          return F_PIPE;

        case ':':
          return F_DCOLON;

        case '"':
          return F_SEMICOLON;

        case '.':
          return F_PERIOD;

        case '/':
          return F_SLASH;

        case '<':
          return F_LESS;

        case '>':
          return F_GREATER;

        case '?':
          return F_QUESTION;

        case ' ':
          return F_BLANK;
      }
      break;

    case 'a':
      tempc = _SHIN;
      break;

    case 'A':
      tempc = WAW_H;
      break;

    case 'b':
      tempc = ZAL;
      break;

    case 'c':
      tempc = ZE;
      break;

    case 'C':
      tempc = JE;
      break;

    case 'd':
      tempc = _YE;
      break;

    case 'D':
      tempc = _YEE;
      break;

    case 'e':
      tempc = _SE;
      break;

    case 'f':
      tempc = _BE;
      break;

    case 'g':
      tempc = _LAM;
      break;

    case 'G':
      if (!curwin->w_cursor.col && STRLEN(ml_get_curline())) {
        if (gchar_cursor() == _LAM) {
          chg_c_toX_orX();
        } else if (p_ri) {
          chg_c_to_X_or_X();
        }
      }

      if (!p_ri) {
        if (!curwin->w_cursor.col) {
          return ALEF_U_H;
        }
      }

      if (!p_ri) {
        dec_cursor();
      }

      if (gchar_cursor() == _LAM) {
        chg_c_toX_orX();
        chg_l_toXor_X();
        tempc = ALEF_U_H;
      } else if (F_is_TyB_TyC_TyD(SRC_EDT, AT_CURSOR)) {
        tempc = ALEF_U_H_;
        chg_l_toXor_X();
      } else {
        tempc = ALEF_U_H;
      }

      if (!p_ri) {
        inc_cursor();
      }

      return tempc;

    case 'h':
      if (!curwin->w_cursor.col && STRLEN(ml_get_curline())) {
        if (p_ri) {
          chg_c_to_X_or_X();
        }
      }

      if (!p_ri) {
        if (!curwin->w_cursor.col) {
          return ALEF;
        }
      }

      if (!p_ri) {
        dec_cursor();
      }

      if (gchar_cursor() == _LAM) {
        chg_l_toXor_X();
        del_char(FALSE);
        AppendCharToRedobuff(K_BS);

        if (!p_ri) {
          dec_cursor();
        }

        tempc = LA;
      } else {
        if (F_is_TyB_TyC_TyD(SRC_EDT, AT_CURSOR)) {
          tempc = ALEF_;
          chg_l_toXor_X();
        } else {
          tempc = ALEF;
        }
      }

      if (!p_ri) {
        inc_cursor();
      }

      return tempc;

    case 'i':

      if (!curwin->w_cursor.col && STRLEN(ml_get_curline())) {
        if (!p_ri && !F_is_TyE(tempc)) {
          chg_c_to_X_orX_();
        }

        if (p_ri) {
          chg_c_to_X_or_X();
        }
      }

      if (!p_ri && !curwin->w_cursor.col) {
        return _HE;
      }

      if (!p_ri) {
        dec_cursor();
      }

      if (F_is_TyB_TyC_TyD(SRC_EDT, AT_CURSOR)) {
        tempc = _HE_;
      } else {
        tempc = _HE;
      }

      if (!p_ri) {
        inc_cursor();
      }
      break;

    case 'j':
      tempc = _TE;
      break;

    case 'J':

      if (!curwin->w_cursor.col && STRLEN(ml_get_curline())) {
        if (p_ri) {
          chg_c_to_X_or_X();
        }
      }

      if (!p_ri) {
        if (!curwin->w_cursor.col) {
          return TEE;
        }
      }

      if (!p_ri) {
        dec_cursor();
      }

      if (F_is_TyB_TyC_TyD(SRC_EDT, AT_CURSOR)) {
        tempc = TEE_;
        chg_l_toXor_X();
      } else {
        tempc = TEE;
      }

      if (!p_ri) {
        inc_cursor();
      }

      return tempc;

    case 'k':
      tempc = _NOON;
      break;

    case 'l':
      tempc = _MIM;
      break;

    case 'm':
      tempc = _PE;
      break;

    case 'n':
    case 'N':
      tempc = DAL;
      break;

    case 'o':
      tempc = _XE;
      break;

    case 'p':
      tempc = _HE_J;
      break;

    case 'q':
      tempc = _ZAD;
      break;

    case 'r':
      tempc = _GHAF;
      break;

    case 's':
      tempc = _SIN;
      break;

    case 'S':
      tempc = _IE;
      break;

    case 't':
      tempc = _FE;
      break;

    case 'u':
      if (!curwin->w_cursor.col && STRLEN(ml_get_curline())) {
        if (!p_ri && !F_is_TyE(tempc)) {
          chg_c_to_X_orX_();
        }

        if (p_ri) {
          chg_c_to_X_or_X();
        }
      }

      if (!p_ri && !curwin->w_cursor.col) {
        return _AYN;
      }

      if (!p_ri) {
        dec_cursor();
      }

      if (F_is_TyB_TyC_TyD(SRC_EDT, AT_CURSOR)) {
        tempc = _AYN_;
      } else {
        tempc = _AYN;
      }

      if (!p_ri) {
        inc_cursor();
      }
      break;

    case 'v':
    case 'V':
      tempc = RE;
      break;

    case 'w':
      tempc = _SAD;
      break;

    case 'x':
    case 'X':
      tempc = _TA;
      break;

    case 'y':
      if (!curwin->w_cursor.col && STRLEN(ml_get_curline())) {
        if (!p_ri && !F_is_TyE(tempc)) {
          chg_c_to_X_orX_();
        }

        if (p_ri) {
          chg_c_to_X_or_X();
        }
      }

      if (!p_ri && !curwin->w_cursor.col) {
        return _GHAYN;
      }

      if (!p_ri) {
        dec_cursor();
      }

      if (F_is_TyB_TyC_TyD(SRC_EDT, AT_CURSOR)) {
        tempc = _GHAYN_;
      } else {
        tempc = _GHAYN;
      }

      if (!p_ri) {
        inc_cursor();
      }

      break;

    case 'z':
      tempc = _ZA;
      break;

    case 'Z':
      tempc = _KAF_H;
      break;

    case ';':
      tempc = _KAF;
      break;

    case '\'':
      tempc = _GAF;
      break;

    case ',':
      tempc = WAW;
      break;

    case '[':
      tempc = _JIM;
      break;

    case ']':
      tempc = _CHE;
      break;
  }

  if ((F_isalpha(tempc) || F_isdigit(tempc))) {
    if (!curwin->w_cursor.col && STRLEN(ml_get_curline())) {
      if (!p_ri && !F_is_TyE(tempc)) {
        chg_c_to_X_orX_();
      }

      if (p_ri) {
        chg_c_to_X_or_X();
      }
    }

    if (curwin->w_cursor.col) {
      if (!p_ri) {
        dec_cursor();
      }

      if (F_is_TyE(tempc)) {
        chg_l_toXor_X();
      } else {
        chg_l_to_X_orX_();
      }

      if (!p_ri) {
        inc_cursor();
      }
    }
  }

  if (tempc) {
    return tempc;
  }
  return c;
}