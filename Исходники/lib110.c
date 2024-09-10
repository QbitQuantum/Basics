int Scanf(char *format, ...)
{
    int ret;

    va_list ap;
    va_start(ap, format);
    ret = vscanf(format, ap);
    va_end(ap);
    return ret;
}