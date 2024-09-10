LVAL xsetupconsole()
{
    HWND mywin;
    HANDLE myhandle;
    COORD winsize, origin;
    WORD textattrib;
    DWORD n;
    mywin = GetForegroundWindow();
    SetConsoleTitle("Nyquist");

    myhandle = GetStdHandle(STD_OUTPUT_HANDLE);
    origin.X = 0;
    origin.Y = 0;
    winsize.X = 100;
    winsize.Y = 40;
    textattrib = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;

    FillConsoleOutputAttribute(myhandle, textattrib, winsize.X * winsize.Y, origin, &n);
    SetConsoleScreenBufferSize(myhandle, winsize);
    FillConsoleOutputAttribute(myhandle, textattrib, winsize.X * winsize.Y, origin, &n);
    SetConsoleTextAttribute(myhandle, textattrib);
    return NIL;
}