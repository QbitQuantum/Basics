void PezDebugStringW(const wchar_t* pStr, ...)
{
    wchar_t msg[1024] = {0};

    va_list a;
    va_start(a, pStr);

    _vsnwprintf_s(msg, _countof(msg), _TRUNCATE, pStr, a);
    OutputDebugStringW(msg);
}