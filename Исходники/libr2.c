void alloc_console() {
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	HANDLE hStdin = GetStdHandle (STD_INPUT_HANDLE);
	DWORD lpMode;

	AllocConsole ();
	GetConsoleMode (hStdin, &lpMode);
	SetConsoleMode (hStdin, lpMode & (~ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT));
	GetConsoleScreenBufferInfo (hStdin, &coninfo);
	coninfo.dwSize.Y = 4096;
	SetConsoleScreenBufferSize (hStdin, coninfo.dwSize);

	freopen ("conin$", "r", stdin);
	freopen ("conout$", "w", stdout);
	freopen ("conout$", "w", stderr);
}