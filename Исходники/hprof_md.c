int
md_vsnprintf(char *s, int n, const char *format, va_list ap)
{
    return _vsnprintf(s, n, format, ap);
}