int swprintf_s (wchar_t* strDest, size_t destMax, const wchar_t* format, ...)
{
    int ret = 0;
    va_list arglist;

    va_start(arglist, format);
    ret = vswprintf_s(strDest, destMax, format, arglist);
    va_end(arglist);

    return ret;
}