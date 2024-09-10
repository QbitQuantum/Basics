void linenoiseClearScreen(void) {
#ifdef _WIN32
    COORD coord = {0, 0};
    CONSOLE_SCREEN_BUFFER_INFO inf;
    DWORD count;
    DWORD size;

    GetConsoleScreenBufferInfo(console_out, &inf);
    size = inf.dwSize.X * inf.dwSize.Y;
    FillConsoleOutputCharacterA(console_out, ' ', size, coord, &count );
    SetConsoleCursorPosition(console_out, coord); 
#else
    if (write(1,"\x1b[H\x1b[2J",7) <= 0) {
        /* nothing to do, just to avoid warning. */
    }
#endif
}