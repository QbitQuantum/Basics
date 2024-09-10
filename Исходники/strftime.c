_WCRTLINK size_t _wstrftime_ms( CHAR_TYPE *s, size_t maxsize, const char *format, const struct tm *timeptr )
{
    wchar_t     *auto_buf;
    int         length;

    length = _mbslen( (unsigned char *)format ) + 1;
    auto_buf = (wchar_t *)alloca( length * CHARSIZE );
    mbstowcs( auto_buf, format, length );
    return( wcsftime( s, maxsize, auto_buf, timeptr ) );
}