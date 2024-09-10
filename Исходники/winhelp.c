/*
 * @unimplemented
 */
BOOL
WINAPI
WinHelpW(HWND hWnd, LPCWSTR lpszHelp, UINT uCommand, DWORD_PTR dwData)
{
    INT len;
    LPSTR file;
    BOOL ret = FALSE;

    if (!lpszHelp) return WinHelpA(hWnd, NULL, uCommand, dwData);

    len = WideCharToMultiByte(CP_ACP, 0, lpszHelp, -1, NULL, 0, NULL, NULL);
    if ((file = HeapAlloc(GetProcessHeap(), 0, len))) {
        WideCharToMultiByte(CP_ACP, 0, lpszHelp, -1, file, len, NULL, NULL);
        ret = WinHelpA(hWnd, file, uCommand, dwData);
        HeapFree(GetProcessHeap(), 0, file);
    }
    return ret;
}