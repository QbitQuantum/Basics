void InterpretEscSeq(void) {
    int  i;
    WORD attribut;
    CONSOLE_SCREEN_BUFFER_INFO Info;
    CONSOLE_CURSOR_INFO CursInfo;
    DWORD len, NumberOfCharsWritten;
    COORD Pos;
    SMALL_RECT Rect;
    CHAR_INFO  CharInfo;

    if (prefix == '[') {
        if (prefix2 == '?' && (suffix == 'h' || suffix == 'l')) {
            if (es_argc == 1 && es_argv[0] == 25) {
                GetConsoleCursorInfo(hConOut, &CursInfo);
                CursInfo.bVisible = (suffix == 'h');
                SetConsoleCursorInfo(hConOut, &CursInfo);
                return;
            }
        }
        // Ignore any other \e[? or \e[> sequences.
        if (prefix2 != 0)
            return;

        GetConsoleScreenBufferInfo(hConOut, &Info);
        switch (suffix) {
            case 'm':
                if (es_argc == 0) es_argv[es_argc++] = 0;
                for (i = 0; i < es_argc; i++) {
                    if (30 <= es_argv[i] && es_argv[i] <= 37)
                        grm.foreground = es_argv[i] - 30;
                    else if (40 <= es_argv[i] && es_argv[i] <= 47)
                        grm.background = es_argv[i] - 40;
                    else switch (es_argv[i]) {
                        case 0:
                        case 39:
                        case 49:
                        {
                                   TCHAR def[4];
                                   int   a;
                                   *def = '7'; def[1] = '\0';
                                   GetEnvironmentVariable(L"ANSICON_DEF", def, lenof(def));
                                   a = wcstol(def, NULL, 16);
                                   grm.reverse = FALSE;
                                   if (a < 0) {
                                       grm.reverse = TRUE;
                                       a = -a;
                                   }
                                   if (es_argv[i] != 49)
                                       grm.foreground = attr2ansi[a & 7];
                                   if (es_argv[i] != 39)
                                       grm.background = attr2ansi[(a >> 4) & 7];
                                   if (es_argv[i] == 0) {
                                       if (es_argc == 1) {
                                           grm.bold = a & FOREGROUND_INTENSITY;
                                           grm.underline = a & BACKGROUND_INTENSITY;
                                       } else {
                                           grm.bold = 0;
                                           grm.underline = 0;
                                       }
                                       grm.rvideo = 0;
                                       grm.concealed = 0;
                                   }
                        }
                            break;

                        case  1: grm.bold = FOREGROUND_INTENSITY; break;
                        case  5: // blink
                        case  4: grm.underline = BACKGROUND_INTENSITY; break;
                        case  7: grm.rvideo = 1; break;
                        case  8: grm.concealed = 1; break;
                        case 21: // oops, this actually turns on double underline
                        case 22: grm.bold = 0; break;
                        case 25:
                        case 24: grm.underline = 0; break;
                        case 27: grm.rvideo = 0; break;
                        case 28: grm.concealed = 0; break;
                    }
                }
                if (grm.concealed) {
                    if (grm.rvideo) {
                        attribut = foregroundcolor[grm.foreground]
                            | backgroundcolor[grm.foreground];
                        if (grm.bold)
                            attribut |= FOREGROUND_INTENSITY | BACKGROUND_INTENSITY;
                    } else {
                        attribut = foregroundcolor[grm.background]
                            | backgroundcolor[grm.background];
                        if (grm.underline)
                            attribut |= FOREGROUND_INTENSITY | BACKGROUND_INTENSITY;
                    }
                } else if (grm.rvideo) {
                    attribut = foregroundcolor[grm.background]
                        | backgroundcolor[grm.foreground];
                    if (grm.bold)
                        attribut |= BACKGROUND_INTENSITY;
                    if (grm.underline)
                        attribut |= FOREGROUND_INTENSITY;
                } else
                    attribut = foregroundcolor[grm.foreground] | grm.bold
                    | backgroundcolor[grm.background] | grm.underline;
                if (grm.reverse)
                    attribut = ((attribut >> 4) & 15) | ((attribut & 15) << 4);
                SetConsoleTextAttribute(hConOut, attribut);
                return;

            case 'J':
                if (es_argc == 0) es_argv[es_argc++] = 0; // ESC[J == ESC[0J
                if (es_argc != 1) return;
                switch (es_argv[0]) {
                    case 0:		// ESC[0J erase from cursor to end of display
                        len = (Info.dwSize.Y - Info.dwCursorPosition.Y - 1) * Info.dwSize.X
                            + Info.dwSize.X - Info.dwCursorPosition.X - 1;
                        FillConsoleOutputCharacter(hConOut, ' ', len,
                            Info.dwCursorPosition,
                            &NumberOfCharsWritten);
                        FillConsoleOutputAttribute(hConOut, Info.wAttributes, len,
                            Info.dwCursorPosition,
                            &NumberOfCharsWritten);
                        return;

                    case 1:		// ESC[1J erase from start to cursor.
                        Pos.X = 0;
                        Pos.Y = 0;
                        len = Info.dwCursorPosition.Y * Info.dwSize.X
                            + Info.dwCursorPosition.X + 1;
                        FillConsoleOutputCharacter(hConOut, ' ', len, Pos,
                            &NumberOfCharsWritten);
                        FillConsoleOutputAttribute(hConOut, Info.wAttributes, len, Pos,
                            &NumberOfCharsWritten);
                        return;

                    case 2:		// ESC[2J Clear screen and home cursor
                        Pos.X = 0;
                        Pos.Y = 0;
                        len = Info.dwSize.X * Info.dwSize.Y;
                        FillConsoleOutputCharacter(hConOut, ' ', len, Pos,
                            &NumberOfCharsWritten);
                        FillConsoleOutputAttribute(hConOut, Info.wAttributes, len, Pos,
                            &NumberOfCharsWritten);
                        SetConsoleCursorPosition(hConOut, Pos);
                        return;

                    default:
                        return;
                }

            case 'K':
                if (es_argc == 0) es_argv[es_argc++] = 0; // ESC[K == ESC[0K
                if (es_argc != 1) return;
                switch (es_argv[0]) {
                    case 0:		// ESC[0K Clear to end of line
                        len = Info.dwSize.X - Info.dwCursorPosition.X + 1;
                        FillConsoleOutputCharacter(hConOut, ' ', len,
                            Info.dwCursorPosition,
                            &NumberOfCharsWritten);
                        FillConsoleOutputAttribute(hConOut, Info.wAttributes, len,
                            Info.dwCursorPosition,
                            &NumberOfCharsWritten);
                        return;

                    case 1:		// ESC[1K Clear from start of line to cursor
                        Pos.X = 0;
                        Pos.Y = Info.dwCursorPosition.Y;
                        FillConsoleOutputCharacter(hConOut, ' ',
                            Info.dwCursorPosition.X + 1, Pos,
                            &NumberOfCharsWritten);
                        FillConsoleOutputAttribute(hConOut, Info.wAttributes,
                            Info.dwCursorPosition.X + 1, Pos,
                            &NumberOfCharsWritten);
                        return;

                    case 2:		// ESC[2K Clear whole line.
                        Pos.X = 0;
                        Pos.Y = Info.dwCursorPosition.Y;
                        FillConsoleOutputCharacter(hConOut, ' ', Info.dwSize.X, Pos,
                            &NumberOfCharsWritten);
                        FillConsoleOutputAttribute(hConOut, Info.wAttributes,
                            Info.dwSize.X, Pos,
                            &NumberOfCharsWritten);
                        return;

                    default:
                        return;
                }

            case 'X':                 // ESC[#X Erase # characters.
                if (es_argc == 0) es_argv[es_argc++] = 1; // ESC[X == ESC[1X
                if (es_argc != 1) return;
                FillConsoleOutputCharacter(hConOut, ' ', es_argv[0],
                    Info.dwCursorPosition,
                    &NumberOfCharsWritten);
                FillConsoleOutputAttribute(hConOut, Info.wAttributes, es_argv[0],
                    Info.dwCursorPosition,
                    &NumberOfCharsWritten);
                return;

            case 'L':                 // ESC[#L Insert # blank lines.
                if (es_argc == 0) es_argv[es_argc++] = 1; // ESC[L == ESC[1L
                if (es_argc != 1) return;
                Rect.Left = 0;
                Rect.Top = Info.dwCursorPosition.Y;
                Rect.Right = Info.dwSize.X - 1;
                Rect.Bottom = Info.dwSize.Y - 1;
                Pos.X = 0;
                Pos.Y = Info.dwCursorPosition.Y + es_argv[0];
                CharInfo.Char.UnicodeChar = ' ';
                CharInfo.Attributes = Info.wAttributes;
                ScrollConsoleScreenBuffer(hConOut, &Rect, NULL, Pos, &CharInfo);
                return;

            case 'M':                 // ESC[#M Delete # lines.
                if (es_argc == 0) es_argv[es_argc++] = 1; // ESC[M == ESC[1M
                if (es_argc != 1) return;
                if (es_argv[0] > Info.dwSize.Y - Info.dwCursorPosition.Y)
                    es_argv[0] = Info.dwSize.Y - Info.dwCursorPosition.Y;
                Rect.Left = 0;
                Rect.Top = Info.dwCursorPosition.Y + es_argv[0];
                Rect.Right = Info.dwSize.X - 1;
                Rect.Bottom = Info.dwSize.Y - 1;
                Pos.X = 0;
                Pos.Y = Info.dwCursorPosition.Y;
                CharInfo.Char.UnicodeChar = ' ';
                CharInfo.Attributes = Info.wAttributes;
                ScrollConsoleScreenBuffer(hConOut, &Rect, NULL, Pos, &CharInfo);
                return;

            case 'P':                 // ESC[#P Delete # characters.
                if (es_argc == 0) es_argv[es_argc++] = 1; // ESC[P == ESC[1P
                if (es_argc != 1) return;
                if (Info.dwCursorPosition.X + es_argv[0] > Info.dwSize.X - 1)
                    es_argv[0] = Info.dwSize.X - Info.dwCursorPosition.X;
                Rect.Left = Info.dwCursorPosition.X + es_argv[0];
                Rect.Top = Info.dwCursorPosition.Y;
                Rect.Right = Info.dwSize.X - 1;
                Rect.Bottom = Info.dwCursorPosition.Y;
                CharInfo.Char.UnicodeChar = ' ';
                CharInfo.Attributes = Info.wAttributes;
                ScrollConsoleScreenBuffer(hConOut, &Rect, NULL, Info.dwCursorPosition,
                    &CharInfo);
                return;

            case '@':                 // ESC[#@ Insert # blank characters.
                if (es_argc == 0) es_argv[es_argc++] = 1; // ESC[@ == ESC[1@
                if (es_argc != 1) return;
                if (Info.dwCursorPosition.X + es_argv[0] > Info.dwSize.X - 1)
                    es_argv[0] = Info.dwSize.X - Info.dwCursorPosition.X;
                Rect.Left = Info.dwCursorPosition.X;
                Rect.Top = Info.dwCursorPosition.Y;
                Rect.Right = Info.dwSize.X - 1 - es_argv[0];
                Rect.Bottom = Info.dwCursorPosition.Y;
                Pos.X = Info.dwCursorPosition.X + es_argv[0];
                Pos.Y = Info.dwCursorPosition.Y;
                CharInfo.Char.UnicodeChar = ' ';
                CharInfo.Attributes = Info.wAttributes;
                ScrollConsoleScreenBuffer(hConOut, &Rect, NULL, Pos, &CharInfo);
                return;

            case 'k':                 // ESC[#k
            case 'A':                 // ESC[#A Moves cursor up # lines
                if (es_argc == 0) es_argv[es_argc++] = 1; // ESC[A == ESC[1A
                if (es_argc != 1) return;
                Pos.Y = Info.dwCursorPosition.Y - es_argv[0];
                if (Pos.Y < 0) Pos.Y = 0;
                Pos.X = Info.dwCursorPosition.X;
                SetConsoleCursorPosition(hConOut, Pos);
                return;

            case 'e':                 // ESC[#e
            case 'B':                 // ESC[#B Moves cursor down # lines
                if (es_argc == 0) es_argv[es_argc++] = 1; // ESC[B == ESC[1B
                if (es_argc != 1) return;
                Pos.Y = Info.dwCursorPosition.Y + es_argv[0];
                if (Pos.Y >= Info.dwSize.Y) Pos.Y = Info.dwSize.Y - 1;
                Pos.X = Info.dwCursorPosition.X;
                SetConsoleCursorPosition(hConOut, Pos);
                return;

            case 'a':                 // ESC[#a
            case 'C':                 // ESC[#C Moves cursor forward # spaces
                if (es_argc == 0) es_argv[es_argc++] = 1; // ESC[C == ESC[1C
                if (es_argc != 1) return;
                Pos.X = Info.dwCursorPosition.X + es_argv[0];
                if (Pos.X >= Info.dwSize.X) Pos.X = Info.dwSize.X - 1;
                Pos.Y = Info.dwCursorPosition.Y;
                SetConsoleCursorPosition(hConOut, Pos);
                return;

            case 'j':                 // ESC[#j
            case 'D':                 // ESC[#D Moves cursor back # spaces
                if (es_argc == 0) es_argv[es_argc++] = 1; // ESC[D == ESC[1D
                if (es_argc != 1) return;
                Pos.X = Info.dwCursorPosition.X - es_argv[0];
                if (Pos.X < 0) Pos.X = 0;
                Pos.Y = Info.dwCursorPosition.Y;
                SetConsoleCursorPosition(hConOut, Pos);
                return;

            case 'E':                 // ESC[#E Moves cursor down # lines, column 1.
                if (es_argc == 0) es_argv[es_argc++] = 1; // ESC[E == ESC[1E
                if (es_argc != 1) return;
                Pos.Y = Info.dwCursorPosition.Y + es_argv[0];
                if (Pos.Y >= Info.dwSize.Y) Pos.Y = Info.dwSize.Y - 1;
                Pos.X = 0;
                SetConsoleCursorPosition(hConOut, Pos);
                return;

            case 'F':                 // ESC[#F Moves cursor up # lines, column 1.
                if (es_argc == 0) es_argv[es_argc++] = 1; // ESC[F == ESC[1F
                if (es_argc != 1) return;
                Pos.Y = Info.dwCursorPosition.Y - es_argv[0];
                if (Pos.Y < 0) Pos.Y = 0;
                Pos.X = 0;
                SetConsoleCursorPosition(hConOut, Pos);
                return;

            case '`':                 // ESC[#`
            case 'G':                 // ESC[#G Moves cursor column # in current row.
                if (es_argc == 0) es_argv[es_argc++] = 1; // ESC[G == ESC[1G
                if (es_argc != 1) return;
                Pos.X = es_argv[0] - 1;
                if (Pos.X >= Info.dwSize.X) Pos.X = Info.dwSize.X - 1;
                if (Pos.X < 0) Pos.X = 0;
                Pos.Y = Info.dwCursorPosition.Y;
                SetConsoleCursorPosition(hConOut, Pos);
                return;

            case 'd':                 // ESC[#d Moves cursor row #, current column.
                if (es_argc == 0) es_argv[es_argc++] = 1; // ESC[d == ESC[1d
                if (es_argc != 1) return;
                Pos.Y = es_argv[0] - 1;
                if (Pos.Y < 0) Pos.Y = 0;
                if (Pos.Y >= Info.dwSize.Y) Pos.Y = Info.dwSize.Y - 1;
                SetConsoleCursorPosition(hConOut, Pos);
                return;

            case 'f':                 // ESC[#;#f
            case 'H':                 // ESC[#;#H Moves cursor to line #, column #
                if (es_argc == 0)
                    es_argv[es_argc++] = 1; // ESC[H == ESC[1;1H
                if (es_argc == 1)
                    es_argv[es_argc++] = 1; // ESC[#H == ESC[#;1H
                if (es_argc > 2) return;
                Pos.X = es_argv[1] - 1;
                if (Pos.X < 0) Pos.X = 0;
                if (Pos.X >= Info.dwSize.X) Pos.X = Info.dwSize.X - 1;
                Pos.Y = es_argv[0] - 1;
                if (Pos.Y < 0) Pos.Y = 0;
                if (Pos.Y >= Info.dwSize.Y) Pos.Y = Info.dwSize.Y - 1;
                SetConsoleCursorPosition(hConOut, Pos);
                return;

            case 's':                 // ESC[s Saves cursor position for recall later
                if (es_argc != 0) return;
                SavePos = Info.dwCursorPosition;
                return;

            case 'u':                 // ESC[u Return to saved cursor position
                if (es_argc != 0) return;
                SetConsoleCursorPosition(hConOut, SavePos);
                return;

            case 'n':                 // ESC[#n Device status report
                if (es_argc != 1) return; // ESC[n == ESC[0n -> ignored
                switch (es_argv[0]) {
                    case 5:		// ESC[5n Report status
                        SendSequence(L"\33[0n"); // "OK"
                        return;

                    case 6:		// ESC[6n Report cursor position
                    {
                                    TCHAR buf[32];
                                    wsprintf(buf, L"\33[%d;%dR", Info.dwCursorPosition.Y + 1,
                                        Info.dwCursorPosition.X + 1);
                                    SendSequence(buf);
                    }
                        return;

                    default:
                        return;
                }

            case 't':                 // ESC[#t Window manipulation
                if (es_argc != 1) return;
                if (es_argv[0] == 21)	// ESC[21t Report xterm window's title
                {
                    TCHAR buf[MAX_PATH * 2];
                    DWORD len = GetConsoleTitle(buf + 3, lenof(buf) - 3 - 2);
                    // Too bad if it's too big or fails.
                    buf[0] = ESC;
                    buf[1] = ']';
                    buf[2] = 'l';
                    buf[3 + len] = ESC;
                    buf[3 + len + 1] = '\\';
                    buf[3 + len + 2] = '\0';
                    SendSequence(buf);
                }
                return;

            default:
                return;
        }
    } else // (prefix == ']')
    {
        // Ignore any \e]? or \e]> sequences.
        if (prefix2 != 0)