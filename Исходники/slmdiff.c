int
SLMprintfLn(
    WCHAR *szLine)
{
    long cbWritten;
    WORD count;
    BYTE *lpBuf;
    DWORD dwMode;

    count = wcslen(szLine);

    if (!bUnicode) {
        lpBuf = pvAllocMem (count + 50);
        memset (lpBuf, 0, count + 50);
#ifdef _WIN32
        WideCharToMultiByte (CP_ACP, 0, szLine, count, lpBuf, count + 50, NULL, NULL);
#else
        wcstombs (lpBuf, szLine, count + 50);
#endif
        count = printf("%s", lpBuf);

        if (fCkSum)
            CheckSum(lpBuf, strlen(lpBuf));

        FreeMem (lpBuf);

        return (count);
    }
    else {
        if (fCkSum)
            CheckSum((char *)szLine, count * sizeof(WCHAR));

#ifdef _WIN32
        if (GetConsoleMode((HANDLE)_get_osfhandle(_fileno(stdout)), &dwMode))
            return (WriteConsoleW ((HANDLE)_get_osfhandle(_fileno(stdout)),
                                   szLine,
                                   wcslen(szLine),
                                   &cbWritten,
                                   NULL));
        else
            return (wprintf(L"%s", szLine));
#else
        return (wprintf(L"%s", szLine));
#endif
    }
}