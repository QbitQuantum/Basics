/*
 * _GetString - read in a string, return the length
 */
int _GetString( LPWDATA w, char *str, int maxbuff )
{
    HWND        hwnd;
    int         buff_end = 0;
    int         curr_pos = 0;
    BOOL        escape = FALSE;
    BOOL        insert_flag = FALSE;
    int         maxlen = maxbuff;
    LPSTR       res;
    int         wt;
    int         len;
    int         i;
    int         scan;
#ifdef _MBCS
    unsigned char *p;
    int         expectingTrailByte = 0;
    int         overwrote = 0;
    unsigned char   ci;
    unsigned char   cx;
#else
    char        ci;
    char        cx;
#endif

#ifdef _MBCS
    res = _MemAlloc( MB_CUR_MAX * ( maxbuff + 1 ) );
#else
    res = _MemAlloc( maxbuff + 1 );
#endif
    if( res == NULL)
        return( 0 );

    hwnd = w->hwnd;

    _MoveToLine( w, _GetLastLineNumber( w ), FALSE );
    _NewCursor( w, SMALL_CURSOR );
    _SetInputMode( w, TRUE );
    _GotEOF = FALSE;
    str[0] = 0;

    while( 1 ) {

        w->curr_pos = curr_pos;
        _DisplayCursor( w );
        while( !_KeyboardHit( TRUE ) );
        ci = _GetKeyboard( &scan );
#if defined( __OS2__ )
        WinShowCursor( hwnd, FALSE );
#else
        HideCaret( hwnd );
#endif

        if( escape ) {
#ifdef _MBCS
            p = __mbsninc( (unsigned char *)str, curr_pos++ );
            *p = ci;
#else
            str[curr_pos++] = ci;
#endif
            escape = FALSE;
        } else if( (ci == CTRL_V) || (scan != 0xFF) ) {
            if( ci == CTRL_V ) {
                escape = TRUE;      /* This is a VI thing - */
                ci = '^';           /* it permits insertion of any key */
            }
            if( insert_flag ) {
                if( buff_end < maxlen && !TOOWIDE( buff_end, w ) ) {
#ifdef _MBCS
                    if( !expectingTrailByte ) {     /* shift over two bytes */
                        if( _ismbblead( ci ) ) {
                            expectingTrailByte = 1;
                            p = __mbsninc( (unsigned char *)str, curr_pos );
                            for( i = strlen( (char *)p ); i >= 0; i-- )
                                p[i + 2] = p[i];
                            p[0] = ci;
                        } else {                    /* shift over one byte */
                            p = __mbsninc( (unsigned char *)str, curr_pos );
                            for( i = strlen( (char *)p ); i >= 0; i-- )
                                p[i + 1] = p[i];
                            p[0] = ci;
                        }
                    } else {
                        expectingTrailByte = 0;
                        p = __mbsninc( (unsigned char *)str, curr_pos );
                        p[1] = ci;
                    }
                    overwrote = 0;
#else
                    for( i = buff_end; i >= curr_pos; i-- )
                        str[i + 1] = str[i];
                    buff_end++;
                    str[curr_pos] = ci;
#endif
                } else {
                    continue;
                }
            } else if( curr_pos == buff_end ) {
                if( buff_end < maxlen ) {
#ifdef _MBCS
                    if( !expectingTrailByte ) {
                        if( _ismbblead( ci ) ) {
                            expectingTrailByte = 1;
                            p = __mbsninc( (unsigned char *)str, buff_end );
                        } else {
                            p = __mbsninc( (unsigned char *)str, buff_end );
                        }
                        p[0] = ci;
                        p[1] = p[2] = 0;
                    } else {
                        expectingTrailByte = 0;
                        p = __mbsninc( (unsigned char *)str, buff_end );
                        p[1] = ci;
                        p[2] = 0;
                    }
                    overwrote = 0;
#else
                    str[buff_end++] = ci;
                    str[buff_end] = 0;
#endif
                } else {
                    continue;
                }
            } else {
#ifdef _MBCS
                p = __mbsninc( (unsigned char *)str, curr_pos );
                if( !expectingTrailByte ) {
                    if( _ismbblead( ci ) ) {
                        expectingTrailByte = 1;
                        if( !_ismbblead( *p ) ) {
                            for( i = strlen( (char *)p + 1 ); i >= 0; i-- ) {
                                p[i + 2] = p[i + 1];    /* shift over one byte */
                            }
                        }
                        p[0] = ci;
                    } else {
                        if( _ismbblead( *p ) ) {   /* shift over one byte */
                            for( i = 1; i <= strlen( (char *)p + 1 ); i++ ) {
                                p[i] = p[i + 1];
                            }
                        }
                        p[0] = ci;
                    }
                } else {
                    expectingTrailByte = 0;
                    p[1] = ci;
                }
                overwrote = 1;
#else
                str[curr_pos] = ci;
#endif
            }
#ifdef _MBCS
            if( !escape && !expectingTrailByte ) {
                curr_pos++;
                if( !overwrote ) {
                    buff_end++;
                }
            }
#else
            if( !escape ) {
                curr_pos++;
            }
#endif
        } else {
            cx = ci;
            if( cx >= 0x80 )
                cx -= 0x80;
            switch( cx ) {
            case VK_HOME:
                curr_pos = 0;
                break;
            case VK_END:
                curr_pos = buff_end;
                break;
            case VK_RETURN:
#ifdef __OS2__
            case VK_ENTER:
#endif
#ifdef _MBCS
                p = __mbsninc( (unsigned char *)str, buff_end );
                *p = '\0';
#else
                str[buff_end] = 0;
#endif
                _NewCursor( w, ORIGINAL_CURSOR );
#ifdef _MBCS
                _UpdateInputLine( w, str, __mbslen( (unsigned char *)str ), TRUE );
#else
                _UpdateInputLine( w, str, strlen( str ), TRUE );
#endif
                _SetInputMode( w, FALSE );
                FARstrcat( res, str );
                FARstrcpy( str, res );
                _MemFree( res );
                /* return number of bytes */
                return( strlen( str ) );
            case VK_LEFT:
                if( curr_pos > 0 )
                    curr_pos--;
                break;
            case VK_RIGHT:
                if( curr_pos < buff_end )
                    curr_pos++;
                break;
            case VK_DELETE:
                if( curr_pos == buff_end )
                    break;  /* DEL, not BS */
                if( curr_pos < buff_end )
                    curr_pos++;
                /* fall through to VK_BACK... */
            case VK_BACK:
                if( curr_pos > 0 ) {
#ifdef _MBCS
                    p = __mbsninc( (unsigned char *)str, curr_pos - 1 );
                    for( i = curr_pos; i < buff_end; i++ ) {
                        _mbccpy( __mbsninc( p, i - curr_pos ), __mbsninc( p, i - curr_pos + 1 ) );
                    }
                    p = __mbsninc( (unsigned char *)str, i - 1 );
                    *p = '\0';
#else
                    for( i = curr_pos; i <= buff_end; i++ )
                        str[i - 1] = str[i];
#endif
                    buff_end--;
                    curr_pos--;
                }
                break;
            case VK_INSERT:
                if( insert_flag ) {
                    insert_flag = FALSE;
                    _NewCursor( w, SMALL_CURSOR );
                } else {
                    insert_flag = TRUE;
                    _NewCursor( w, FAT_CURSOR );
                }
                break;
            default:
                continue;
            }
        }

        /*
         * update line.  if line was split, then we must reset
         * the current line info.
         */
#ifdef _MBCS
        wt = _UpdateInputLine( w, str, expectingTrailByte ? __mbslen( (unsigned char *)str ) - 1 : __mbslen( (unsigned char *)str ), FALSE );
#else
        wt = _UpdateInputLine( w, str, strlen( str ), FALSE );
#endif

        if( wt >= 0 ) {
#ifdef _MBCS
            len = __mbslen( (unsigned char *)str );
            p = __mbsninc( (unsigned char *)str, len - wt );
            ci = *p;
            *p = '\0';
            FARstrcat( res, str );
            *p = ci;
            for( i = 0; i <= wt; i++ )
                str[i] = str[len - wt + i];
#else
            len = strlen( str );
            ci = str[ len - wt ];
            str[ len - wt ] = 0;
            FARstrcat( res, str );
            str[ len - wt ] = ci;
            for( i = 0; i <= wt; i++ )
                str[i] = str[len - wt + i];
#endif
            curr_pos = wt;
            buff_end = wt;
            maxlen -= len + 1;
        }
    }

} /* _GetString */