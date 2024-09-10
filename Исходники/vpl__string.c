int VPL_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
    int rv = 0;

    if (str != NULL) {
        _vsnprintf_s(str, size, _TRUNCATE, format, ap);
    }

    //rv, the number of characters that would be generated, does NOT include the terminating null character
    rv = _vscprintf(format, ap);

    if (rv < 0) {
        VPL_REPORT_FATAL("_vscprintf(%s):%d", format, rv);
        //When error, always return 0 and set *str to '\0' (To avoid caller crash)
        if(str != NULL && size > 0)
            *str = '\0';
        rv = 0;
    }

    return rv;
}