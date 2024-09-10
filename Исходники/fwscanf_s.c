int fwscanf_s(FILE* stream, const wchar_t* format, ...)
{
    int ret = 0;
    va_list arglist;

    va_start(arglist, format);
    ret = vfwscanf_s( stream, format, arglist);
    va_end(arglist);

    return ret;
}