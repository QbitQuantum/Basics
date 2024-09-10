void _vdebugPrintf(const wchar_t* format, va_list va) {
#ifdef _DEBUG
    wchar_t buf[c_bufferCount];
    _vsnwprintf_s(buf, _countof(buf), _TRUNCATE, format, va);
    OutputDebugStringW(buf);
#endif
}