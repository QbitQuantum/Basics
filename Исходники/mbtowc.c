_WCRTLINK int _NEARFAR(mbtowc,_fmbtowc)( wchar_t _FFAR *pwc, const char _FFAR *ch, size_t n )
{
#ifdef __NT__
    int                 rc;
    int                 len;
    wchar_t             wch;
#endif

    /*** Catch special cases ***/
    if( ch == NULL )  return( 0 );
    if( n == 0 )  return( -1 );
    if( *ch == '\0' ) {
        if( pwc != NULL )  *pwc = L'\0';
        return( 0 );
    }
    if( _ismbblead( ch[0] )  &&  ch[1] == '\0' )  return( -1 ); /* invalid */

    /*** Convert the character ***/
    #ifdef __NT__
        len = _NEARFAR(_mbclen,_fmbclen)( (unsigned char _FFAR *)ch );
        rc = MultiByteToWideChar( __MBCodePage, MB_ERR_INVALID_CHARS,
                                  (LPCSTR)ch, min(n,len), (LPWSTR)&wch, 1 );
        if( rc != 0 ) {
            if( pwc != NULL )  *pwc = wch;
            return( len );                      /* return mbchar size */
        } else {
            return( -1 );                       /* cannot convert */
        }
    #else
        if( _ismbblead(*ch) && n>=2 ) {         /* lead byte present? */
            if( pwc != NULL ) {
                *pwc = (((wchar_t)ch[0])<<8) |  /* convert to lead:trail */
                        (wchar_t)ch[1];
            }
            return( 2 );                        /* return char size */
        } else if( !_ismbblead(*ch) ) {
            if( pwc != NULL ) {
                *pwc = (wchar_t)ch[0];          /* convert to 00:byte */
            }
            return( 1 );                        /* return char size */
        } else {
            return( -1 );                       /* n==1, but char 2 bytes */
        }
    #endif
}