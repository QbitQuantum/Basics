int __cdecl __mingw_vfprintf(
     FILE *stream,
     const char *format,
     va_list argptr 
)
{
    return vfprintf_s(stream, format, argptr);
}