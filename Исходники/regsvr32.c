static void __cdecl output_write(UINT id, ...)
{
    WCHAR fmt[1024];
    __ms_va_list va_args;
    WCHAR *str;
    DWORD len, nOut, ret;

    if (Silent) return;

    if (!LoadStringW(GetModuleHandleW(NULL), id, fmt, sizeof(fmt)/sizeof(fmt[0])))
    {
        WINE_FIXME("LoadString failed with %d\n", GetLastError());
        return;
    }

    __ms_va_start(va_args, id);
    SetLastError(NO_ERROR);
    len = FormatMessageW(FORMAT_MESSAGE_FROM_STRING|FORMAT_MESSAGE_ALLOCATE_BUFFER,
                         fmt, 0, 0, (LPWSTR)&str, 0, &va_args);
    __ms_va_end(va_args);
    if (len == 0 && GetLastError() != NO_ERROR)
    {
        WINE_FIXME("Could not format string: le=%u, fmt=%s\n", GetLastError(), wine_dbgstr_w(fmt));
        return;
    }

    ret = WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), str, len, &nOut, NULL);

    /* WriteConsole fails if its output is redirected to a file.
     * If this occurs, we should use an OEM codepage and call WriteFile.
     */
    if (!ret)
    {
        DWORD lenA;
        char *strA;

        lenA = WideCharToMultiByte(GetConsoleOutputCP(), 0, str, len, NULL, 0, NULL, NULL);
        strA = HeapAlloc(GetProcessHeap(), 0, lenA);
        if (strA)
        {
            WideCharToMultiByte(GetConsoleOutputCP(), 0, str, len, strA, lenA, NULL, NULL);
            WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), strA, lenA, &nOut, FALSE);
            HeapFree(GetProcessHeap(), 0, strA);
        }
    }
    LocalFree(str);
}