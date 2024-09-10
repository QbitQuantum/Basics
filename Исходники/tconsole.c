void nt_init_term(void)
{
	DWORD dwmode;
	CONSOLE_SCREEN_BUFFER_INFO scrbuf;
	HANDLE hinput = GetStdHandle(STD_INPUT_HANDLE);

	if (GetConsoleMode(hinput, &dwmode)) {
		if (!SetConsoleMode(hinput, dwmode | ENABLE_WINDOW_INPUT))
			dbgprintf(PR_ERROR, "!!! %s(): SetConsoleMode(0x%p, ..) error %ld\n", __FUNCTION__, hinput, GetLastError());
	}
	/* defaults */
	glines = 25;
	gcolumns = 80;
	hConOut = CreateFile("CONOUT$", GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hConOut == INVALID_HANDLE_VALUE) {
		dbgprintf(PR_ERROR, "!!! %s(): CreateFile(\"CONOUT$\", ..) error %ld\n", __FUNCTION__, GetLastError());
		return;
	}
	if (!GetConsoleScreenBufferInfo(hConOut, &scrbuf)) {
		dbgprintf(PR_ERROR, "!!! %s(): GetConsoleScreenBufferInfo(0x%p, ..) error %ld\n", __FUNCTION__, hConOut, GetLastError());
		/* fail all remaining calls */
		hConOut = INVALID_HANDLE_VALUE;
		return;
	}
	if (!GetConsoleCursorInfo(hConOut, &cursinfo))
		dbgprintf(PR_ERROR, "!!! %s(): GetConsoleCursorInfo(0x%p, ..) error %ld\n", __FUNCTION__, hConOut, GetLastError());
        cursinfo_valid = TRUE;
	glines = scrbuf.srWindow.Bottom - scrbuf.srWindow.Top + 1;
	gcolumns = scrbuf.srWindow.Right - scrbuf.srWindow.Left + 1;
}