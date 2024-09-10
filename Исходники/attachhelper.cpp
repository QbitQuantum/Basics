void Log(LPCWSTR wszFormat, ...)
{
    va_list insertionArgs;
    va_start(insertionArgs, wszFormat);
    if (g_fConsoleMode)
    {
        vwprintf(wszFormat, insertionArgs);
    }
    else
    {
        WCHAR wszMessage[1024];
        _vswprintf_p(wszMessage, 1024, wszFormat, insertionArgs);
        MessageBoxW(NULL, wszMessage, L"CLRProfiler", MB_OK);
    }

    va_end(insertionArgs);
}