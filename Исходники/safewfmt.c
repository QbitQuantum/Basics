static int my_swscanf_s( const wchar_t *s, const wchar_t *fmt, ... )
{
    va_list     arg;
    int         rc;

    va_start( arg, fmt );
    rc = vswscanf_s( s, fmt, arg );
    va_end( arg );
    return( rc );
}