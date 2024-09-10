int wprintf(const wchar_t* fmt, ...)
{
    va_list ptr;
    int ret;

    va_start(ptr, fmt);
    ret = vwprintf(fmt, ptr);
    va_end(ptr);
    return ret;
}