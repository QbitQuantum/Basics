void Win32EnableConsole()
{
    int consoleHandle;
    long stdHandle;
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    FILE *file;

    const int bufferSize = 500;

    // allocate a console for this app
    AllocConsole();

    // set the screen buffer to be big enough to let us scroll text

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
    consoleInfo.dwSize.Y = bufferSize;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), consoleInfo.dwSize);

    // redirect unbuffered STDOUT to the console
    stdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
    consoleHandle = _open_osfhandle(stdHandle, _O_TEXT);
    file = _fdopen(consoleHandle, "w");
    *stdout = *file;
    setvbuf(stdout, NULL, _IONBF, 0);

    // redirect unbuffered STDIN to the console
    stdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
    consoleHandle = _open_osfhandle(stdHandle, _O_TEXT);
    file = _fdopen(consoleHandle, "r");
    *stdin = *file;
    setvbuf(stdin, NULL, _IONBF, 0);

    // redirect unbuffered STDERR to the console
    stdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
    consoleHandle = _open_osfhandle(stdHandle, _O_TEXT);
    file = _fdopen(consoleHandle, "w");
    *stderr = *file;
    setvbuf(stderr, NULL, _IONBF, 0);

    // make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog point to console as well
    std::ios::sync_with_stdio();

    GetConsoleScreenBufferInfo((HANDLE)consoleHandle, &consoleInfo);
    consoleInfo.srWindow.Top = 800;
    SetConsoleWindowInfo((HANDLE)consoleHandle, false, &consoleInfo.srWindow);
    
/*
    SetWindowPos(
        (HWND)GetStdHandle(STD_OUTPUT_HANDLE),
        HWND_TOP,
        1920+100, 800,
        500, 200,
        SWP_NOSIZE | SWP_SHOWWINDOW);*/
    }