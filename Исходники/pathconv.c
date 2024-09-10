/*
 * Translate  foo/dir1\\dir2" \\"bar"grok  -->  "foo\\dir1\\dir2 \\"bargrok".
 */
char *PathConvert( const char *pathname, char quote )
/***************************************************/
{
    const unsigned char *path = (const unsigned char *)pathname;
    char                *out;
    unsigned char       *p;
    bool                quoteends = FALSE;  /* quote the whole filename */
    bool                backslash = FALSE;  /* true if last char was a '\\' */
    bool                inquote = FALSE;    /* true if inside a quoted string */

    /*** Allocate a buffer for the new string (should be big enough) ***/
    out = AllocMem( 2 * ( strlen( (char *)path ) + 1 + 2 ) );
    p = (unsigned char *)out;

    /*** Determine if path contains any bizarre characters ***/
    if( _mbschr( path, ' ' )  !=  NULL      ||
        _mbschr( path, '\t' )  !=  NULL     ||
        _mbschr( path, '"' )  !=  NULL      ||
        _mbschr( path, '\'' )  !=  NULL     ||
        _mbschr( path, '`' )  !=  NULL      ||
        _mbschr( path, quote )  !=  NULL ) {
        quoteends = TRUE;
        *p++ = quote;
    }

    /*** Convert the path one character at a time ***/
    while( *path != '\0' ) {
        if( *path == '"' ) {
            if( inquote ) {
                if( backslash ) {
                    *p++ = '"';         /* handle \" within a string */
                    backslash = FALSE;
                } else {
                    inquote = FALSE;
                }
            } else {
                inquote = TRUE;
            }
        } else if( *path == '\\' ) {
            *p++ = '\\';
            if( backslash ) {
                backslash = FALSE;
            } else {
                backslash = TRUE;
            }
        } else if( *path == '/' ) {
            if( inquote ) {
                *p++ = '/';
            } else {
                *p++ = '\\';
            }
            backslash = FALSE;
        } else {
            _mbccpy( p, path );         /* copy an ordinary character */
            p = _mbsinc( p );
            backslash = FALSE;
        }
        path = _mbsinc( path );
    }
    if( quoteends )  *p++ = quote;
    *p++ = '\0';

    return( out );
}