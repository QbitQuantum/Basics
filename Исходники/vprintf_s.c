int
_cdecl
vprintf_s(const char *format, va_list valist)
{
    return vfprintf_s(stdout,format,valist);
}