static void output(const char* str,
                   size_t      len,
                   int         x,
                   int         y)
{
    COORD pos = { (SHORT)x, (SHORT)y };
    WriteConsoleOutputCharacterA(console_out, str, len, pos, 0);
}