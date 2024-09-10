void RedirectIOToConsole()
{
	// allocate a console for this app
	bool br = AllocConsole() == TRUE;
	if (!br) return;
	//assert( br );

	CONSOLE_SCREEN_BUFFER_INFO coninfo = { 0 };
	// set the screen buffer to be big enough to let us scroll text
	br = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo) == TRUE;
	assert( br );

	coninfo.dwSize.Y = MAX_CONSOLE_LINES;

	br = SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize) == TRUE;
	assert( br );

	// redirect unbuffered STDOUT to the console	
	HANDLE lStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	assert( lStdHandle != INVALID_HANDLE_VALUE );
	assert( lStdHandle != NULL );

	int hConHandle = _open_osfhandle((intptr_t)lStdHandle, _O_TEXT);
	assert( hConHandle != -1 );
	
	FILE *fp = _fdopen( hConHandle, "w" );
	assert(fp);

	*stdout = *fp;

	int ir = setvbuf( stdout, NULL, _IONBF, 0 );
	assert(	ir ==0 );

	// redirect unbuffered STDIN to the console
	lStdHandle = GetStdHandle(STD_INPUT_HANDLE);

	hConHandle = _open_osfhandle((intptr_t)lStdHandle, _O_TEXT);

	fp = _fdopen( hConHandle, "r" );
	*stdin = *fp;

	ir = setvbuf( stdin, NULL, _IONBF, 0 );
	assert(	ir ==0 );
	 

	// redirect unbuffered STDERR to the console
	lStdHandle = GetStdHandle(STD_ERROR_HANDLE);

	hConHandle = _open_osfhandle((intptr_t)lStdHandle, _O_TEXT);

	fp = _fdopen( hConHandle, "w" );

	*stderr = *fp;

	ir = setvbuf( stderr, NULL, _IONBF, 0 );
	assert(	ir ==0 );

	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog 
	// point to console as well
	std::ios::sync_with_stdio( true );
}