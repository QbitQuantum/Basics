static CHAR_TYPE *try_dir( CHAR_TYPE *dir, CHAR_TYPE *prefix )
{
    CHAR_TYPE *         buf;
    size_t              numchars;
    int                 addslash = 0;
    unsigned            number;
    int                 alive;

    /*** Ensure the directory exists ***/
    if( dir[0] != NULLCHAR ) {
        if( __F_NAME(access,_waccess)( dir, F_OK )  ==  -1 ) {
            return( NULL );
        }
    }

    /*** Initialize addslash ***/
    numchars = __F_NAME(_mbslen,wcslen)( dir );
    if( numchars > 0  &&  prefix[0] != STRING( '\\' ) ) {
#ifdef __WIDECHAR__
        if( dir[numchars-1] != L'\\' ) {
#else
        if( _mbccmp( _mbsninc(dir,numchars-1), "\\" ) ) {
#endif
            addslash = 1;
        }
    }

    /*** Ensure the filename wouldn't be too long ***/
    /* dir + slash if needed + prefix + room for unique characters */
    /* strlen is ok for DBCS, since we want the byte count */
    numchars = __F_NAME(strlen,wcslen)( dir )  +  addslash  +  __F_NAME(strlen,wcslen)( prefix )  +  UNIQUE;
    if( numchars > _MAX_PATH )  return( NULL );

    /*** Try to build a unique filename ***/
    buf = malloc( CHARSIZE * (numchars+1) );
    for( number=1,alive=1; alive; number++ ) {
        __F_NAME(strcpy,wcscpy)( buf, dir );
        if( addslash ) {
            __F_NAME(strcat,wcscat)( buf, STRING( "\\" ) );
        }
        __F_NAME(strcat,wcscat)( buf, prefix );
        __F_NAME(utoa,_utow)( number, buf + __F_NAME(strlen,wcslen)(buf), 10 );

        if( __F_NAME(access,_waccess)( buf, F_OK )  !=  0 ) {
            return( buf );
        }
        if( number == 65535u )  alive = 0;
    }

    return( NULL );
}


_WCRTLINK CHAR_TYPE *__F_NAME(_tempnam,_wtempnam)( CHAR_TYPE *dir, CHAR_TYPE *prefix )
{
    CHAR_TYPE *         p;
    CHAR_TYPE *         envp;

    /*** Try the directory given by the TMP environment variable ***/
    envp = __F_NAME(getenv,_wgetenv)( STRING( "TMP" ) );
    if( envp != NULL ) {
        p = try_dir( envp, prefix );
        if( p != NULL )  return( p );
    }

    /*** Try the directory passed to this function (dir) ***/
    if( dir != NULL ) {
        p = try_dir( dir, prefix );
        if( p != NULL )  return( p );
    }

    /*** Try the _P_tmpdir directory (#defined in stdio.h) ***/
    p = try_dir( __F_NAME(_P_tmpdir,_wP_tmpdir), prefix );
    if( p != NULL )  return( p );

    /*** Try the current directory ***/
    p = try_dir( STRING( "" ), prefix );
    if( p != NULL )  return( p );

    return( NULL );
}