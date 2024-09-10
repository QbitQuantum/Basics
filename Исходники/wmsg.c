static bool MsgReadErrArray( void )
#endif
{
    int         i;
    char        buffer[128];
    unsigned    msg_shift;

    msg_shift = _WResLanguage() * MSG_LANG_SPACING;
    for( i = ERR_FIRST_MESSAGE; i <= ERR_LAST_MESSAGE; i++ ) {
#if !defined(__WINDOWS__)
        if( WResLoadString( &hInstance, i + msg_shift, (lpstr)buffer, sizeof( buffer ) ) <= 0 ) {
#else
        if( LoadString( inst, i + msg_shift, (LPSTR)buffer, sizeof( buffer ) ) <= 0 ) {
#endif
            if( i == ERR_FIRST_MESSAGE )
                return( false );
            buffer[0] = '\0';
        }
        MsgArray[i - ERR_FIRST_MESSAGE] = my_alloc( strlen( buffer ) + 1 );
        if( MsgArray[i - ERR_FIRST_MESSAGE] == NULL )
            return( false );
        _fstrcpy( MsgArray[i - ERR_FIRST_MESSAGE], buffer );
    }
    return( true );
}

#if !defined(__WINDOWS__)
bool MsgInit( void )
{
    char        buffer[_MAX_PATH];
#if defined(_PLS)
    char        *fname;
    char        fullpath[_MAX_PATH];
#endif
    bool        rc;

    hInstance.status = 0;
    if( _cmdname( buffer ) != NULL ) {
        rc = OpenResFile( &hInstance, buffer );
#if defined(_PLS)
        if( !rc ) {
            _splitpath2( buffer, fullpath, NULL, NULL, &fname, NULL );
            _makepath( buffer, NULL, NULL, fname, ".exp" );
            _searchenv( buffer, "PATH", fullpath );
            if( fullpath[0] != '\0' ) {
                rc = OpenResFile( &hInstance, fullpath );
            }
        }
#endif
        if( rc ) {
            MsgReadErrArray();
            CloseResFile( &hInstance );
            return( true );
        }
    }
    CloseResFile( &hInstance );
    posix_write( STDOUT_FILENO, NO_RES_MESSAGE, NO_RES_SIZE );
    return( false );
}