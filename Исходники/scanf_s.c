int scanf_s (const char* format, ...)
{
    int ret = 0;
    va_list arglist;

    va_start(arglist, format);
    ret =  vscanf_s( format, arglist);
    va_end(arglist);

    return ret;
}