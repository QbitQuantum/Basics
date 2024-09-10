_WCRTLINK int __F_NAME(mkdir,_wmkdir)( const CHAR_TYPE *path )
{
    APIRET              rc;
#ifdef __WIDECHAR__
    size_t              rcConvert;
    char                mbcsPath[ MB_CUR_MAX * _MAX_PATH ];
    unsigned char       *p;

    /*** Convert the wide character string to a multibyte string ***/
    rcConvert = wcstombs( mbcsPath, path, sizeof( mbcsPath ) );
    p = _mbsninc( (unsigned char *)mbcsPath, rcConvert );
    *p = '\0';
#endif
    rc = DosMkDir( (PSZ)__F_NAME(path,mbcsPath), 0 );
    if( rc != 0 ) {
        return( __set_errno_dos( rc ) );
    }
    return( 0 );            /* indicate no error */
}