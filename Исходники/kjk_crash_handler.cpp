WCHAR *FmtV(const WCHAR *fmt, va_list args)
{
    WCHAR   message[256];
    size_t  bufCchSize = dimof(message);
    WCHAR * buf = message;
    for (;;)
    {
        int count = _vsnwprintf_s(buf, bufCchSize, _TRUNCATE, fmt, args);
        if ((count >= 0) && ((size_t)count < bufCchSize))
            break;
        /* we have to make the buffer bigger. The algorithm used to calculate
           the new size is arbitrary (aka. educated guess) */
        if (buf != message)
            free(buf);
        if (bufCchSize < 4*1024)
            bufCchSize += bufCchSize;
        else
            bufCchSize += 1024;
        buf = AllocArray<WCHAR>(bufCchSize);
        if (!buf)
            break;
    }
    if (buf == message)
        buf = str::Dup(message);

    return buf;
}