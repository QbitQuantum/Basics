_WCRTLINK int _ismbcalpha( unsigned int ch )
{
#ifdef __NT__
    BOOL                rc;
    int                 len;
    char                mbc[ MB_LEN_MAX + 1 ];
    WORD                char_type[ MB_LEN_MAX + 1 ];

    _mbvtop( ch, mbc );
    len = _mbclen( mbc );
    mbc[ len ] = '\0';
    rc = GetStringTypeEx( LOCALE_USER_DEFAULT, CT_CTYPE1, mbc, -1, char_type );
    if( rc == FALSE ) return( 0 );
    if( (char_type[ 0 ] & C1_ALPHA) == 0 ) return( 0 );
    return( 1 );
#else                                   /* OS/2 and others */
    if( __MBCodePage == 932 ) {                 /* Japanese code page */
        if( SINGLE_BYTE_CHAR( ch ) ) {
            if( ch >= 0xA6  &&  ch <= 0xDF ) {  /* Katakana letters */
                return( 1 );
            } else {
                return( isalpha( ch ) );
            }
        } else {                                /* double-byte chars */
            return( _ismbdalpha( ch ) );
        }
    } else {
        if( SINGLE_BYTE_CHAR( ch ) ) {
            return( isalpha( ch ) );
        } else {
            return( 0 );
        }
    }
#endif
}