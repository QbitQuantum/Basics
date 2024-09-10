void __DEBUG_MSG__(const WCHAR* szFormat, va_list args)
{
    const size_t SIZE = 4096;   
    WCHAR szBuf[SIZE] = {0}; 
    _vsnwprintf_s(szBuf, SIZE, SIZE, szFormat, args);
    lstrcatW(szBuf, L"\n");
    DebugConsole::Printf(GetStdString(szBuf).c_str());
}