static void
flash_display(void)
{
    DWORD length = term.cols * term.rows;
    DWORD got;
    WORD *buf1;
    WORD *buf2;

    static COORD origin;

    if ((buf1 = typeallocn(WORD, length)) != 0
	&& (buf2 = typeallocn(WORD, length)) != 0) {
	ReadConsoleOutputAttribute(hConsoleOutput, buf1, length, origin, &got);
	ReadConsoleOutputAttribute(hConsoleOutput, buf2, length, origin, &got);
	for (got = 0; got < length; got++) {
	    buf2[got] ^= (FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
	}
	WriteConsoleOutputAttribute(hConsoleOutput, buf2, length, origin, &got);
	Sleep(200);
	WriteConsoleOutputAttribute(hConsoleOutput, buf1, length, origin, &got);
	free(buf1);
	free(buf2);
    }
}