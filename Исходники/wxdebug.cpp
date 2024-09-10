//
// warning -- this function is implemented twice for ansi applications
// linking to the unicode library
//
void WINAPI DbgLogInfo(DWORD Type,DWORD Level,__format_string LPCSTR pFormat,...)
{
    /* Check the current level for this type combination */

    BOOL bAccept = DbgCheckModuleLevel(Type,Level);
    if (bAccept == FALSE) {
        return;
    }

    TCHAR szInfo[2000];

    /* Format the variable length parameter list */

    va_list va;
    va_start(va, pFormat);

    (void)StringCchPrintf(szInfo, NUMELMS(szInfo),
             TEXT("%s(tid %x) %8d : "),
             m_ModuleName,
             GetCurrentThreadId(), timeGetTime() - dwTimeOffset);

    CHAR szInfoA[2000];
    WideCharToMultiByte(CP_ACP, 0, szInfo, -1, szInfoA, NUMELMS(szInfoA), 0, 0);

    (void)StringCchVPrintfA(szInfoA + lstrlenA(szInfoA), NUMELMS(szInfoA) - lstrlenA(szInfoA), pFormat, va);
    (void)StringCchCatA(szInfoA, NUMELMS(szInfoA), "\r\n");

    WCHAR wszOutString[2000];
    MultiByteToWideChar(CP_ACP, 0, szInfoA, -1, wszOutString, NUMELMS(wszOutString));
    DbgOutString(wszOutString);

    va_end(va);
}