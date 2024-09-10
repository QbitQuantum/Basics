// Mutates the input argument (buf), because we're evil.
void mp_write_console_ansi(HANDLE wstream, char *buf)
{
    while (*buf) {
        char *next = strchr(buf, '\033');
        if (!next) {
            write_console_text(wstream, buf);
            break;
        }
        next[0] = '\0'; // mutate input for fun and profit
        write_console_text(wstream, buf);
        if (next[1] != '[') {
            write_console_text(wstream, "\033");
            buf = next;
            continue;
        }
        next += 2;
        // ANSI codes generally follow this syntax:
        //    "\033[" [ <i> (';' <i> )* ] <c>
        // where <i> are integers, and <c> a single char command code.
        // Also see: http://en.wikipedia.org/wiki/ANSI_escape_code#CSI_codes
        int params[2] = {-1, -1}; // 'm' might be unlimited; ignore that
        int num_params = 0;
        while (num_params < 2) {
            char *end = next;
            long p = strtol(next, &end, 10);
            if (end == next)
                break;
            next = end;
            params[num_params++] = p;
            if (next[0] != ';' || !next[0])
                break;
            next += 1;
        }
        char code = next[0];
        if (code)
            next += 1;
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(wstream, &info);
        switch (code) {
        case 'K': {     // erase to end of line
            COORD at = info.dwCursorPosition;
            int len = info.dwSize.X - at.X;
            FillConsoleOutputCharacterW(wstream, ' ', len, at, &(DWORD){0});
            SetConsoleCursorPosition(wstream, at);
            break;
        }
        case 'A': {     // cursor up
            info.dwCursorPosition.Y -= 1;
            SetConsoleCursorPosition(wstream, info.dwCursorPosition);
            break;
        }
        case 'm': {     // "SGR"
            for (int n = 0; n < num_params; n++) {
                int p = params[n];
                if (p == 0) {
                    info.wAttributes = stdoutAttrs;
                    SetConsoleTextAttribute(wstream, info.wAttributes);
                } else if (p == 1) {
                    info.wAttributes |= FOREGROUND_INTENSITY;
                    SetConsoleTextAttribute(wstream, info.wAttributes);
                } else if (p >= 30 && p < 38) {
                    info.wAttributes &= ~FOREGROUND_ALL;
                    info.wAttributes |= ansi2win32[p - 30];
                    SetConsoleTextAttribute(wstream, info.wAttributes);
                }
            }
            break;
        }
        }
        buf = next;
    }
}