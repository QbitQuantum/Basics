void RestoreConsole()
{
	SetConsoleMode(hStdin, inConMode);
	SetConsoleMode(hStdout, outConMode);

#ifdef NEW_CONSOLE
	SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
#endif
}