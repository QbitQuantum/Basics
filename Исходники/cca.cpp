void CnsMgr::Init()
{
	// get std handles
	h_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if(h_stdout == INVALID_HANDLE_VALUE)
	{
		throw cyerr("failed to get stdout handle", 8002);
	}
	h_stdin = GetStdHandle(STD_INPUT_HANDLE);
	if(h_stdin == INVALID_HANDLE_VALUE)
	{
		throw cyerr("failed to get stdin handle", 8003);
	}
	
	// create mysb, set as active
	h_mysb = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL);
	if(h_mysb == INVALID_HANDLE_VALUE)
	{
		throw cyerr("failed to create screen buffer", 8004);
	}
	{ // cursor info
		CONSOLE_CURSOR_INFO cci;
		cci.dwSize = 1; // anything 1-100 because not visible anyway
		cci.bVisible = FALSE;
		if(!SetConsoleCursorInfo(h_mysb, &cci))
		{
			throw cyerr("failed to set screen buffer cursor info", 8005);
		}
	}
	{ // screen buffer/window size
		// set both at once
		CONSOLE_SCREEN_BUFFER_INFOEX new_csbi;
		new_csbi.cbSize = sizeof(new_csbi);
		if(!GetConsoleScreenBufferInfoEx(h_mysb, &new_csbi))
		{
			throw cyerr("failed to get screen buffer info", 8007);
		}
		if(new_csbi.dwMaximumWindowSize.X < WND_W || new_csbi.dwMaximumWindowSize.Y < WND_H)
		{
			throw cyerr("maximum window size too small", 8008);
		}
		new_csbi.dwSize = {WND_W, WND_H};
		new_csbi.dwCursorPosition = {0, 0};
		new_csbi.srWindow = {0, 0, WND_W-1, WND_H-1};
		new_csbi.wAttributes = 0;
		if(!SetConsoleScreenBufferInfoEx(h_mysb, &new_csbi))
		{
			throw cyerr("failed to set window/buffer size", 8006);
		}
	}
	if(!SetConsoleMode(h_mysb, NULL)) // no output processing
	{
		throw cyerr("failed to set console output mode", 8010);
	}
	if(!SetConsoleActiveScreenBuffer(h_mysb))
	{
		throw cyerr("failed to set active screen buffer", 8009);
	}
	
	// change settings of stdin
	if(!GetConsoleMode(h_stdin, &ori_stdin_mode))
	{
		SetConsoleActiveScreenBuffer(h_stdout);
		throw cyerr("failed to get stdin console mode", 8011);
	}
	if(!SetConsoleMode(h_stdin, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT))
	{
		SetConsoleActiveScreenBuffer(h_stdout);
		throw cyerr("failed to set console input mode", 8012);
	}
	
	// try to change window title
	ori_title = new char[100];
	if(GetConsoleOriginalTitle(ori_title, 100))
	{
		if(!SetConsoleTitle("CCA"))
		{
			title_changed = false;
		}
		else
		{
			title_changed = true;
		}
	}
	else
	{
		title_changed = false;
	}
	
	// create (our) buffer
	buf = new CHAR_INFO[WND_W * WND_H];

	// done.
	initialized = true;
	
	// clear screen
	Fill(' ', 0); // black|black
	Flip();
}