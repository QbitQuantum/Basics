//--------------------------------------------------------------------------------------
BOOL LoadPrivileges(char *lpszName)
{
    HANDLE hToken = NULL;
    LUID Val;
    TOKEN_PRIVILEGES tp;
    BOOL bRet = FALSE;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
    {
        DbgMsg(__FILE__, __LINE__, "OpenProcessToken() fails: error %d\n", GetLastError());
        goto end;
    }

    if (!LookupPrivilegeValueA(NULL, lpszName, &Val))
    {
        DbgMsg(__FILE__, __LINE__, "LookupPrivilegeValue() fails: error %d\n", GetLastError());
        goto end;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = Val;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof (tp), NULL, NULL))
    {
        DbgMsg(__FILE__, __LINE__, "AdjustTokenPrivileges() fails: error %d\n", GetLastError());
        goto end;
    }

    bRet = TRUE;

end:
    if (hToken)
    {
        CloseHandle(hToken);
    }

    return bRet;
} 