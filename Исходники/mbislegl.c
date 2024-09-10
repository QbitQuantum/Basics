_WCRTLINK int _ismbclegal( unsigned int ch )
{
#ifdef __NT__
    BOOL                rc;
    int                 len;
    char                mbc[ MB_LEN_MAX + 1 ];
    WORD                char_type[ MB_LEN_MAX + 1 ];

    _mbvtop( ch, mbc );
    len = _mbclen( mbc );
    mbc[ len ] = '\0';
    if( len <= 1 ) return( 0 );
    rc = GetStringTypeEx( LOCALE_USER_DEFAULT, CT_CTYPE1, mbc, -1, char_type );
    if( rc == FALSE ) return( 0 );
    if( char_type[ 0 ] == 0 ) return( 0 );
    return( 1 );
#else                                   /* OS/2 and others */
    return( _ismbblead( ch >> 8 ) && _ismbbtrail( ch & 0xFF ) );
#endif
}