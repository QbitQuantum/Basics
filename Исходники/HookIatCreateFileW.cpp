HANDLE
WINAPI
MyCreateFileW(
            LPCWSTR lpFileName,
            DWORD dwDesiredAccess,
            DWORD dwShareMode,
            LPSECURITY_ATTRIBUTES lpSecurityAttributes,
            DWORD dwCreationDisposition,
            DWORD dwFlagsAndAttributes,
            HANDLE hTemplateFile
    )
{
    WCHAR wFileName[MAX_PATH] = { 0 };
    wcscpy(wFileName, lpFileName);
    if ( wcscmp(wcslwr(wFileName), L"g:\\test.txt") == 0 )
    {
        if ( MessageBox(NULL, "是否打开文件", "提示", MB_YESNO) == IDYES )
        {
            return dwCreateFileWAddr(lpFileName,
                            dwDesiredAccess,
                            dwShareMode,
                            lpSecurityAttributes,
                            dwCreationDisposition,
                            dwFlagsAndAttributes,
                            hTemplateFile);
        } 
        else
        {
            return INVALID_HANDLE_VALUE;
        }
    }
    else
    {
        return dwCreateFileWAddr(lpFileName,
            dwDesiredAccess,
            dwShareMode,
            lpSecurityAttributes,
            dwCreationDisposition,
            dwFlagsAndAttributes,
            hTemplateFile);
    }
}