// Code from http://dslweb.nwnexus.com/~ast/dload/guicon.htm
// Andrew Tucker, no license, assumed to be public domain.
void wxlua_RedirectIOToDosConsole(bool alloc_new_if_needed, short max_console_lines)
{
    int  hConHandle = 0;
    long lStdHandle = 0;
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    memset(&coninfo, 0, sizeof(CONSOLE_SCREEN_BUFFER_INFO));
    FILE *fp = 0; // we don't close this, let the OS close it when the app exits

    wxDynamicLibrary kernel;
    // Dynamically load kernel32 because AttachConsole() is not supported pre-XP
    BOOL attached_ok = kernel.Load(wxT("kernel32.dll"));
    
    if (attached_ok)
    {
        // Try to attach to the parent process if it's a console, i.e. we're run from a DOS prompt.
        // The code below is equivalent to calling this code:
        //   BOOL attached_ok = AttachConsole( ATTACH_PARENT_PROCESS );

        typedef BOOL (WINAPI *AttachConsole_t)(DWORD dwProcessId);
        AttachConsole_t wxDL_INIT_FUNC(pfn, AttachConsole, kernel);

        if (pfnAttachConsole)
            attached_ok = pfnAttachConsole( ATTACH_PARENT_PROCESS );
        else
            attached_ok = 0;
    }

    if (attached_ok == 0) // failed attaching
    {
        // we tried to attach, but failed don't alloc a new one
        if (!alloc_new_if_needed)
            return;

        // Unable to attach, allocate a console for this app
        AllocConsole();
    }

    // set the screen buffer to be big enough to let us scroll text
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
    coninfo.dwSize.Y = (WORD)max_console_lines;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);
    // redirect unbuffered STDOUT to the console
    lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "w" );
    *stdout = *fp;
    setvbuf( stdout, NULL, _IONBF, 0 );
    // redirect unbuffered STDIN to the console
    lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "r" );
    *stdin = *fp;
    setvbuf( stdin, NULL, _IONBF, 0 );
    // redirect unbuffered STDERR to the console
    lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "w" );
    *stderr = *fp;
    setvbuf( stderr, NULL, _IONBF, 0 );
    // make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
    // point to console as well
    std::ios::sync_with_stdio();
}