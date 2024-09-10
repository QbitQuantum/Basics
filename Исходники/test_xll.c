static void _console()
{
    DWORD dwError;
    char szError[4096];

    // standard handles that are not redirected to console will already
    // have been initialized correctly - mscrt obeys pipe/file redirections
    // even if we are not in a console process.

    sprintf(szError, "%d %d %d\n",
        (int) GetStdHandle(STD_INPUT_HANDLE),
        (int) GetStdHandle(STD_OUTPUT_HANDLE),
        (int) GetStdHandle(STD_ERROR_HANDLE));
    OutputDebugString(szError);


    // however console handles are not inherited, so first we attach a console
    if (GetConsoleWindow() == NULL)
        AttachConsole(ATTACH_PARENT_PROCESS);

    sprintf(szError, "%d %d %d\n",
        (int) GetStdHandle(STD_INPUT_HANDLE),
        (int) GetStdHandle(STD_OUTPUT_HANDLE),
        (int) GetStdHandle(STD_ERROR_HANDLE));
    OutputDebugString(szError);

    // for some reason this doesn't now work. is it windows 10 or excel 2016
    // or 32 bit on 64. something changed post windows 7 that stops AllocConsole?

    // if we have no console, and no redirection, then allocate a new console
    if (GetConsoleWindow() == NULL)
    {
        if (!AllocConsole())
        {
            sprintf(szError, "%d %d %d\n",
            (int) GetStdHandle(STD_INPUT_HANDLE),
            (int) GetStdHandle(STD_OUTPUT_HANDLE),
            (int) GetStdHandle(STD_ERROR_HANDLE));
        OutputDebugString(szError);

            dwError = GetLastError();
            sprintf(szError, "GetLastError: %d\n", dwError);
            OutputDebugString(szError);
            return;
        }
    }

    // -2 means we had no console window at startup, so fixup the streams
    // that aren't propertly initialized
    _reopen_console("CONIN$", stdin, "rb");
    _reopen_console("CONOUT$", stdout, "ab");
    _reopen_console("CONOUT$", stderr, "ab");

    // some packacges (pytest) assume that file descriptors 0, 1, 2
    // are always stdin/out/err, so dup them back so it works
    if (_fileno(stdin) != 0)
        _dup2(_fileno(stdin), 0);
    if (_fileno(stdout) != 1)
        _dup2(_fileno(stdout), 1);
    if (_fileno(stderr) != 2)
        _dup2(_fileno(stderr), 2);

    printf("Hello From The Other Side.\n");
}