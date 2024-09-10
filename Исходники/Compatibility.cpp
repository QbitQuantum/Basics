int snprintf(char *output, size_t size, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    return _vsnprintf(output, size, format, ap);
}