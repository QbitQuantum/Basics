/*
 * _AddLine - add a line to the lines data structures
 */
void _AddLine( LPWDATA w, const void *in_data, unsigned len )
{
    int                 i;
    BOOL                hadbreak;
    HWND                hwnd;
    int                 tabcnt = 0;
    int                 nlcnt = 0;
    int                 curbufoff = 0;
    const char          *data;
#ifdef _MBCS
    static char         leadByte;
    static int          leadByteWaiting;
    unsigned char       ch[MB_CUR_MAX+1];
    LPBYTE              p;
#else
    char                ch;
#endif

    data = (const char *)in_data;
    hwnd = w->hwnd;

    _AccessWinLines();
    if( w->LineTail != NULL && !w->LineTail->has_cr ) {
        FARstrcpy( w->tmpbuff->data, w->LineTail->data );
#ifdef _MBCS
        curbufoff = FAR_mbslen( (LPBYTE)w->tmpbuff->data );
#else
        curbufoff = FARstrlen( w->tmpbuff->data );
#endif
        if( curbufoff > w->buffoff ) {
            w->buffoff = curbufoff;
        }
    }
    if( w->no_advance ) {
        curbufoff = 0;
    }
    for( i = 0; i < len; i ++ ) {
        w->no_advance = FALSE;
        do {
            hadbreak = FALSE;
#ifdef _MBCS                        /* MBCS */
            if( tabcnt ) {
                _mbccpy( ch, (unsigned char *)" " );     /* copy the character */
                ch[_mbclen( ch )] = '\0';           /* terminate char with NULL */
                tabcnt--;
            } else if( nlcnt ) {
                _mbccpy( ch, (unsigned char *)"\n" );    /* copy the character */
                ch[_mbclen( ch )] = '\0';           /* terminate char with NULL */
                nlcnt--;
            } else {
                if( !leadByteWaiting ) {
                    if( _ismbblead( *data ) ) {
                        leadByteWaiting = 1;
                        leadByte = *data;
                        ch[0] = '\0';
                    } else {
                        ch[0] = *data;
                        ch[1] = '\0';
                    }
                } else {
                    leadByteWaiting = 0;
                    ch[0] = leadByte;
                    ch[1] = *data;
                    ch[2] = '\0';
                }
                data++;
            }

            if( !_mbccmp( ch, (unsigned char *)"\t" ) ) {
                tabcnt = TAB( curbufoff + 1 );
                continue;
            } else if( !_mbccmp( ch, (unsigned char *)"\f" ) ) {
                nlcnt = w->height;
                continue;
            } else if( !_mbccmp( ch, (unsigned char *)"\r" ) ) {
                curbufoff = 0;
                w->no_advance = TRUE;
                w->tmpbuff->has_cr = TRUE;
                continue;
            } else if( !_mbccmp( ch, (unsigned char *)"\n" ) ) {
                hadbreak = TRUE;
                newLine( w );
                curbufoff = w->buffoff;
            } else if( !_mbccmp( ch, (unsigned char *)"\b" ) ) {
                if( curbufoff > 0 ) {
                    p = FAR_mbsninc( (LPBYTE)w->tmpbuff->data, curbufoff - 1 );
                    if( _ismbblead( *p ) ) {
                        *p = ' ';           /* stomp lead byte */
                        /* char split into 2; don't change curbufoff */
                    } else {
                        curbufoff--;        /* back up one character */
                    }
                }
            } else if( ch[0] != '\0' ) {
                FAR_mbccpy( FAR_mbsninc( (LPBYTE)w->tmpbuff->data, curbufoff ), ch );
                curbufoff++;
                if( curbufoff > w->buffoff ) {
                    w->buffoff = curbufoff;
                }
                if( TOOWIDE( w->buffoff, w ) ) {
                    hadbreak = TRUE;
                    newLine( w );
                    curbufoff = w->buffoff;
                }
            }
#else                               /* SBCS */
            if( tabcnt ) {
                ch = ' ';
                tabcnt--;
            } else if( nlcnt ) {
                ch = '\n';
                nlcnt--;
            } else {
                ch = data[i];
            }

            if( ch == '\t' ) {
                tabcnt = TAB( curbufoff + 1 );
                continue;
            } else if( ch == '\f' ) {
                nlcnt = w->height;
                continue;
            } else if( ch == '\r' ) {
                curbufoff = 0;
                w->no_advance = TRUE;
                w->tmpbuff->has_cr = TRUE;
                continue;
            } else if( ch == '\n' ) {
                hadbreak = TRUE;
                newLine( w );
                curbufoff = w->buffoff;
            } else if( ch == '\b' ) {
                if( curbufoff > 0 ) {
                    curbufoff--;
                }
            } else {
                w->tmpbuff->data[curbufoff++] = ch;
                if( curbufoff > w->buffoff ) {
                    w->buffoff = curbufoff;
                }
                if( TOOWIDE( w->buffoff, w ) ) {
                    hadbreak = TRUE;
                    newLine( w );
                    curbufoff = w->buffoff;
                }
            }
#endif
        } while( tabcnt || nlcnt );
    }
    if( !hadbreak ) {
        updateBuff( w );
    }
    _ReleaseWinLines();

} /* _AddLine */