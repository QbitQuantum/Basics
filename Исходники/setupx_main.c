/***********************************************************************
 *		InstallHinfSection (SETUPX.527)
 *
 * hwnd = parent window
 * hinst = instance of SETUPX.DLL
 * lpszCmdLine = e.g. "DefaultInstall 132 C:\MYINSTALL\MYDEV.INF"
 * Here "DefaultInstall" is the .inf file section to be installed (optional).
 * The 132 value is made of the HOW_xxx flags and sometimes 128 (-> setupx16.h).
 *
 * nCmdShow = nCmdShow of CreateProcess
 */
RETERR16 WINAPI InstallHinfSection16( HWND16 hwnd, HINSTANCE16 hinst, LPCSTR lpszCmdLine, INT16 nCmdShow)
{
    InstallHinfSectionA( HWND_32(hwnd), 0, lpszCmdLine, nCmdShow );
    return OK;
}