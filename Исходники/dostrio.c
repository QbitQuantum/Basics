dig_fhandle DIGPathOpen( const char *name, unsigned name_len, const char *exts, char *result, unsigned max_result )
{
    bool        has_ext;
    bool        has_path;
    const char  *src;
    char        *dst;
    char        trpfile[256];
    tiny_ret_t  rc;
    char        c;

    result = result; max_result = max_result;
    has_ext = FALSE;
    has_path = FALSE;
    src = name;
    dst = trpfile;
    while( name_len-- > 0 ) {
        c = *src++;
        *dst++ = c;
        switch( c ) {
        case '.':
            has_ext = TRUE;
            break;
        case '/':
        case '\\':
            has_ext = FALSE;
                /* fall through */
        case ':':
            has_path = TRUE;
            break;
        }
    }
    if( !has_ext ) {
        *dst++ = '.';
        name_len = strlen( exts );
        memcpy( dst, exts, name_len );
        dst += name_len;
    }
    *dst = '\0';
    if( has_path ) {
        rc = TinyOpen( trpfile, TIO_READ );
    } else {
        _searchenv( trpfile, "PATH", RWBuff );
        rc = TinyOpen( RWBuff, TIO_READ );
    }
    return( TINY_ERROR( rc ) ? DIG_NIL_HANDLE : TINY_INFO( rc ) );
}