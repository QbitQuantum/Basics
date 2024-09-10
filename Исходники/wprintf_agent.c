int vwprintfDotsShell ( const wchar_t * format, ... ) {
    int res;
    va_list argList;
    va_start( argList, format );
    res = vwprintf( format, argList );
    va_end( argList );
    return res;
}