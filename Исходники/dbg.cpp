VOID MakeConsole(VOID)
{
    DWORD dwMode;
    struct _CONSOLE_SCREEN_BUFFER_INFO sbi;
    HANDLE hStd;
    FILE *fStream;

    //if (!InitializeCriticalSectionAndSpinCount(&CriticalSection, 0x00000400)) {
    //    DbgMsg("[-] InitializeCriticalSectionAndSpinCount failed : %lu\n", GetLastError());
    //}
    //InitializeCriticalSection(&CriticalSection);
    InitCriticalSection();
    if (!AllocConsole()) {
        FreeConsole();
        if (!AllocConsole()) {
            DbgMsg("[+] AllocConsole() failed : %lu\n", GetLastError());
        }
    }
    hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hStd, (LPDWORD)&dwMode);
    SetConsoleMode(hStd, dwMode & 0xFFFFFFEF);
    GetConsoleScreenBufferInfo(hStd, &sbi);
    sbi.dwSize.Y = 500;
    SetConsoleScreenBufferSize(hStd, sbi.dwSize);
    freopen_s(&fStream, "conin$", "r", stdin);
    freopen_s(&fStream, "conout$", "w", stdout);
    freopen_s(&fStream, "conout$", "w", stderr);
}