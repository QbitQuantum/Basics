/*
 * writes a string of characters to the output
 * returns -1 if the string doesn't fit in the output buffer
 * return the length of the string if all characters were written
 */
static inline int pf_output_stringW( pf_output *out, LPCWSTR str, int len )
{
    int space = out->len - out->used;

    if( len < 0 )
        len = strlenW( str );
    if( out->unicode )
    {
        LPWSTR p = out->buf.W + out->used;

        if( space >= len )
        {
            memcpy( p, str, len*sizeof(WCHAR) );
            out->used += len;
            return len;
        }
        if( space > 0 )
            memcpy( p, str, space*sizeof(WCHAR) );
        out->used += len;
    }
    else
    {
        LPSTR p = out->buf.A + out->used;
        ULONG n;

        RtlUnicodeToMultiByteSize( &n, str, len * sizeof(WCHAR) );
        if( space >= n )
        {
            RtlUnicodeToMultiByteN( p, n, NULL, str, len * sizeof(WCHAR) );
            out->used += n;
            return len;
        }
        if (space > 0) RtlUnicodeToMultiByteN( p, space, NULL, str, len * sizeof(WCHAR) );
        out->used += n;
    }
    return -1;
}