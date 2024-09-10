_WCRTLINK CHAR_TYPE *__F_NAME(getcwd,_wgetcwd)( CHAR_TYPE *buf, size_t size )
/***************************************************************************/
{
    int         len;
#ifdef __WIDECHAR__
    char        cwd[MB_CUR_MAX * _MAX_PATH];       /* multi-byte chars */
#else
    char        cwd[_MAX_PATH];                    /* single-byte chars */
#endif

    __null_check( buf, 1 );
    if( __getdcwd( &cwd[3], 0 ) ) {
        _RWD_errno = ENOENT;      /* noent? */
        return( NULL );
    }

    /* get current drive and insert into cwd[0] */
    cwd[0] = TinyGetCurrDrive() + 'A';
    cwd[1] = ':';
    cwd[2] = '\\';
#ifdef __WIDECHAR__
    len = _mbslen( (unsigned char *)cwd ) + 1;
#else
    len = strlen( cwd ) + 1;
#endif
    if( buf == NULL ) {
        if( (buf = lib_malloc( max( size, len ) * CHARSIZE )) == NULL ) {
            _RWD_errno = ENOMEM;
            return( NULL );
        }
        size = len;
    }

    /*** Copy the pathname into a buffer and quit ***/
#ifdef __WIDECHAR__
    if( mbstowcs( buf, cwd, size ) == -1 ) {
        return( NULL );
    }
    return( buf );
#else
    return( strncpy( buf, cwd, size ) );
#endif
}