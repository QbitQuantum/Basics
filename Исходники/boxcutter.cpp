// Setup the console for output (e.g. using printf)
bool setup_console()
{
    int hConHandle;
    long lStdHandle;
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE *fp;

    // create a console
    if (!AttachConsole(ATTACH_PARENT_PROCESS)) {
        // if no parent console then give up        
        return false;
    }
    
    
	const unsigned int MAX_CONSOLE_LINES = 500;
	// set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),	&coninfo);
	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),	coninfo.dwSize);

    
	// redirect unbuffered STDOUT to the console
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);    
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "w");    
    if (!fp) {
        // could not open stdout
        return false;
    }
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);
    
    
	// redirect unbuffered STDIN to the console
	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "r");
    if (!fp) {
        // could not open stdin
        return false;
    }
	*stdin = *fp;
	setvbuf(stdin, NULL, _IONBF, 0);

    
	// redirect unbuffered STDERR to the console
	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "w");
    if (!fp) {
        // could not open stderr
        return false;
    }
	*stderr = *fp;
	setvbuf(stderr, NULL, _IONBF, 0);

	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
	// point to console as well
	std::ios::sync_with_stdio();

    return true;
}