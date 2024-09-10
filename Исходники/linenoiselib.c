static void refreshLine(int fd, const char *prompt, char *buf, size_t len, size_t pos, size_t cols) {
    char seq[64];
#ifdef _WIN32
    DWORD pl, bl, w;
    CONSOLE_SCREEN_BUFFER_INFO b;
    COORD coord;
#endif
    size_t plen = strlen(prompt);
    
    while((plen+pos) >= cols) {
        buf++;
        len--;
        pos--;
    }
    while (plen+len > cols) {
        len--;
    }

#ifndef _WIN32
    /* Cursor to left edge */
    snprintf(seq,64,"\x1b[0G");
    if (write(fd,seq,strlen(seq)) == -1) return;
    /* Write the prompt and the current buffer content */
    if (write(fd,prompt,strlen(prompt)) == -1) return;
    if (write(fd,buf,len) == -1) return;
    /* Erase to right */
    snprintf(seq,64,"\x1b[0K");
    if (write(fd,seq,strlen(seq)) == -1) return;
    /* Move cursor to original position. */
    snprintf(seq,64,"\x1b[0G\x1b[%dC", (int)(pos+plen));
    if (write(fd,seq,strlen(seq)) == -1) return;
#else

    REDIS_NOTUSED(seq);
    REDIS_NOTUSED(fd);

    /* Get buffer console info */
    if (!GetConsoleScreenBufferInfo(hOut, &b)) return;
    /* Erase Line */
    coord.X = 0;
    coord.Y = b.dwCursorPosition.Y;
    FillConsoleOutputCharacterA(hOut, ' ', b.dwSize.X, coord, &w);
    /*  Cursor to the left edge */
    SetConsoleCursorPosition(hOut, coord);
    /* Write the prompt and the current buffer content */
    WriteConsole(hOut, prompt, (DWORD)plen, &pl, NULL);
    WriteConsole(hOut, buf, (DWORD)len, &bl, NULL);
    /* Move cursor to original position. */
    coord.X = (int)(pos+plen);
    coord.Y = b.dwCursorPosition.Y;
    SetConsoleCursorPosition(hOut, coord);
#endif
}