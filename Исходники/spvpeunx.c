_WCRTLINK int (spawnvpe)( int mode, const char *path, const char *const argv[], const char *const envp[] )
{
    char    *p;
    char    *p2;
    int     retval, err;
    char    buffer[_POSIX_PATH_MAX];
    int     trailer = 0;

    __last_path = "";
    if( *path == '\0' ) {
        _RWD_errno = ENOENT;
        return( -1 );
    }
    p = (char *)getenv( "PATH" );
    for( p2 = (char *)path; *p2 != '\0'; p2++ ) {   /* POSIX check for / in file name */
        if( *p2 == '/' )
            break;
    }
    if( p == NULL || *p2 == '/' )
        return( spawnve( mode, path, argv, envp ) );
    err = _RWD_errno;
    for( retval = -1; ; ) {
        if( *p == '\0' )
            break;
        for( __last_path = p, p2 = buffer; *p && *p != ':';  )
            *p2++ = *p++;
        if( p2 > buffer && p2[-1] != '/' )
            *p2++ = '/';
        strcpy( p2, path );
        retval = spawnve( mode, buffer, argv, envp );
        if( retval != -1 )
            break;
        if( !(_RWD_errno == ENOENT || _RWD_errno == EACCES || _RWD_errno == ENOTDIR) )
            break;
        if( *p == '\0' )
            break;
/*
 * Search current directory once if PATH has a trailling ':'
 */
        if( trailer )
            break;
        if( *++p == '\0' ) {
            --p;
            trailer++;
        }
        _RWD_errno = err;
    }
    return( retval );
}