_WCRTLINK void __F_NAME(_makepath,_wmakepath)( CHAR_TYPE *path, const CHAR_TYPE *drive,
                const CHAR_TYPE *dir, const CHAR_TYPE *fname, const CHAR_TYPE *ext )
{
    UINT_WC_TYPE        first_pc = NULLCHAR;
  #ifndef __WIDECHAR__
    char                *pathstart = path;
    unsigned            ch;
  #endif

    if( drive != NULL ) {
        if( *drive != NULLCHAR ) {
            if( ( drive[0] == DIR_SEP ) && ( drive[1] == DIR_SEP ) ) {
                __F_NAME(strcpy, wcscpy)( path, drive );
                path += __F_NAME(strlen, wcslen)( drive );
            } else {
                *path++ = *drive;                               /* OK for MBCS */
                *path++ = DRV_SEP;
            }
        }
    }
    *path = NULLCHAR;
    if( dir != NULL ) {
        if( *dir != NULLCHAR ) {
            do {
  #ifdef __WIDECHAR__
                *path++ = pickup( *dir++, &first_pc );
  #else
                ch = pickup( _mbsnextc( (unsigned char *)dir ), &first_pc );
                _mbvtop( ch, (unsigned char *)path );
                path[_mbclen( (unsigned char *)path )] = NULLCHAR;
                path = (char *)_mbsinc( (unsigned char *)path );
                dir = (char *)_mbsinc( (unsigned char *)dir );
  #endif
            } while( *dir != NULLCHAR );
            /* if no path separator was specified then pick a default */
            if( first_pc == NULLCHAR )
                first_pc = DIR_SEP;
            /* if dir did not end in '/' then put in a provisional one */
  #ifdef __WIDECHAR__
            if( path[-1] == first_pc ) {
                path--;
            } else {
                *path = first_pc;
            }
  #else
            if( *(_mbsdec( (unsigned char *)pathstart, (unsigned char *)path )) == first_pc ) {
                path--;
            } else {
                *path = first_pc;
            }
  #endif
        }
    }

    /* if no path separator was specified thus far then pick a default */
    if( first_pc == NULLCHAR )
        first_pc = DIR_SEP;
    if( fname != NULL ) {
  #ifdef __WIDECHAR__
        if( pickup( *fname, &first_pc ) != first_pc && *path == first_pc )
            path++;
  #else
        ch = _mbsnextc( (unsigned char *)fname );
        if( pickup( ch, &first_pc ) != first_pc && *path == first_pc )
            path++;
  #endif

        while( *fname != NULLCHAR ) {
        //do {
  #ifdef __WIDECHAR__
            *path++ = pickup( *fname++, &first_pc );
  #else
            ch = pickup( _mbsnextc( (unsigned char *)fname ), &first_pc );
            _mbvtop( ch, (unsigned char *)path );
            path[_mbclen( (unsigned char *)path )] = NULLCHAR;
            path = (char *)_mbsinc( (unsigned char *)path );
            fname = (char *)_mbsinc( (unsigned char *)fname );
  #endif
        } //while( *fname != NULLCHAR );
    } else {
        if( *path == first_pc ) {
            path++;
        }
    }
    if( ext != NULL ) {
        if( *ext != NULLCHAR ) {
            if( *ext != EXT_SEP )
                *path++ = EXT_SEP;
            while( *ext != NULLCHAR ) {
                *path++ = *ext++;     /* OK for MBCS */
            }
        }
    }
    *path = NULLCHAR;
}