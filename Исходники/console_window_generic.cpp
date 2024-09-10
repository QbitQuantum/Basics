CL_ConsoleWindow_Generic::CL_ConsoleWindow_Generic(
	const CL_StringRef &title,
	int width,
	int height)
{
#ifdef WIN32
	AllocConsole();
	SetConsoleTitle(CL_StringHelp::utf8_to_ucs2(title).c_str());
	COORD coord;
	coord.X = width;
	coord.Y = height;
	scrbuf =
		CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			CONSOLE_TEXTMODE_BUFFER,
			NULL);

	if(scrbuf == INVALID_HANDLE_VALUE)
		throw CL_Exception("Unable to allocate console screen buffer");

	SetStdHandle(STD_OUTPUT_HANDLE, scrbuf);
	SetConsoleActiveScreenBuffer(scrbuf);
	SetConsoleScreenBufferSize(scrbuf, coord);

#endif
}