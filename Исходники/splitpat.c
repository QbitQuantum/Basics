_WCRTLINK void __F_NAME(_splitpath,_wsplitpath)( const CHAR_TYPE *path,
    CHAR_TYPE *drive, CHAR_TYPE *dir, CHAR_TYPE *fname, CHAR_TYPE *ext )
{
    const CHAR_TYPE *dotp;
    const CHAR_TYPE *fnamep;
    const CHAR_TYPE *startp;
#ifndef __WIDECHAR__
    unsigned    ch;
#else
    CHAR_TYPE   ch;
#endif
#ifdef __NETWARE__
    const CHAR_TYPE *ptr;
#endif

    /* take apart specification like -> //0/hd/user/fred/filename.ext for QNX */
    /* take apart specification like -> c:\fred\filename.ext for DOS, OS/2 */

#if defined(__UNIX__)

    /* process node/drive specification */
    startp = path;
    if( path[ 0 ] == PC && path[ 1 ] == PC ) {
        path += 2;
        for( ;; ) {
            if( *path == NULLCHAR )
                break;
            if( *path == PC )
                break;
            if( *path == '.' )
                break;
  #ifdef __WIDECHAR__
            ++path;
  #else
    #ifdef __UNIX__
            path++;
    #else
            path = _mbsinc( path );
    #endif
  #endif
        }
    }
    copypart( drive, startp, path - startp, _MAX_NODE );

#elif defined(__NETWARE__)

  #ifdef __WIDECHAR__
        ptr = wcschr( path, ':' );
  #else
    #ifdef __UNIX__
        ptr = strchr( path, ':' );
    #else
        ptr = _mbschr( path, ':' );
    #endif
  #endif
    if( ptr != NULL ) {
        if( drive != NULL ) {
            copypart( drive, path, ptr - path + 1, _MAX_SERVER +
                      _MAX_VOLUME + 1 );
        }
  #ifdef __WIDECHAR__
        path = ptr + 1;
  #else
    #ifdef __UNIX__
        path = ptr + 1;
    #else
        path = _mbsinc( ptr );
    #endif
  #endif
    } else if( drive != NULL ) {
        *drive = '\0';
    }

#else

    /* processs drive specification */
    if( path[ 0 ] != NULLCHAR  &&  path[ 1 ] == ':' ) {
        if( drive != NULL ) {
            drive[ 0 ] = path[ 0 ];
            drive[ 1 ] = ':';
            drive[ 2 ] = NULLCHAR;
        }
        path += 2;
    } else if( drive != NULL ) {
        drive[ 0 ] = NULLCHAR;
    }

#endif

    /* process /user/fred/filename.ext for QNX */
    /* process /fred/filename.ext for DOS, OS/2 */
    dotp = NULL;
    fnamep = path;
    startp = path;

    for( ;; ) {         /* 07-jul-91 DJG -- save *path in ch for speed */
        if( *path == NULLCHAR )
            break;
#ifdef __WIDECHAR__
        ch = *path;
#else
  #ifdef __UNIX__
        ch = *path;
  #else
        ch = _mbsnextc( path );
  #endif
#endif
        if( ch == '.' ) {
            dotp = path;
            ++path;
            continue;
        }
#ifdef __WIDECHAR__
        ++path;
#else
  #ifdef __UNIX__
        path++;
  #else
        path = _mbsinc( path );
  #endif
#endif
#if defined(__UNIX__)
        if( ch == PC ) {
#else /* DOS, OS/2, Windows, Netware */
        if( ch == PC || ch == ALT_PC ) {
#endif
            fnamep = path;
            dotp = NULL;
        }
    }
    copypart( dir, startp, fnamep - startp, _MAX_DIR - 1 );
    if( dotp == NULL )
        dotp = path;
    copypart( fname, fnamep, dotp - fnamep, _MAX_FNAME - 1 );
    copypart( ext,   dotp,   path - dotp,   _MAX_EXT - 1);
}