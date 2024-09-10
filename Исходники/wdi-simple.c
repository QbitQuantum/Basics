// from http://support.microsoft.com/kb/124103/
HWND GetConsoleHwnd(void)
{
    HWND hwndFound;
    char pszNewWindowTitle[128];
    char pszOldWindowTitle[128];

    GetConsoleTitleA(pszOldWindowTitle, 128);
    wsprintfA(pszNewWindowTitle,"%d/%d", GetTickCount(), GetCurrentProcessId());
    SetConsoleTitleA(pszNewWindowTitle);
    Sleep(40);
    hwndFound = FindWindowA(NULL, pszNewWindowTitle);
    SetConsoleTitleA(pszOldWindowTitle);
    return hwndFound;
}