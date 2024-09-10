static int outputChars(struct current *current, const char *buf, int len)
{
    COORD pos;
    DWORD n;

    pos.Y = (SHORT)current->y;

#ifdef USE_UTF8
    while ( len > 0 ) {
        int c, s;
        wchar_t wc;

        s = utf8_tounicode(buf, &c);

        len -= s;
        buf += s;

        wc = (wchar_t)c;

        pos.X = (SHORT)current->x;

        /* fixed display utf8 character */
        WriteConsoleOutputCharacterW(current->outh, &wc, 1, pos, &n);

        current->x += utf8_width(c);
    }
#else
    pos.X = (SHORT)current->x;

    WriteConsoleOutputCharacterA(current->outh, buf, len, pos, &n);
    current->x += len;
#endif

    return 0;
}