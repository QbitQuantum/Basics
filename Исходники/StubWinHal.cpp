int __cdecl hal_vprintf( const char* format, va_list arg )
{
    return vprintf_s ( format, arg );
}