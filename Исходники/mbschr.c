_WCRTLINK unsigned char _FFAR *_NEARFAR(_mbschr,_fmbschr)( const unsigned char _FFAR *string, unsigned int ch )
{
    char                mbc[MB_LEN_MAX+1];

//    if( !__IsDBCS && !ch&0xFF00 )  return( strchr( string, ch ) );

    /*** Search for the specified character ***/
    _mbvtop( ch, mbc );
    mbc[_mbclen(mbc)] = '\0';
    #ifdef __FARFUNC__
        while( !_fmbterm(string) && _fmbccmp(string,mbc)!=0 )
            string = _fmbsinc( string );        /* skip over character */
    #else
        while( !_mbterm(string) && _mbccmp(string,mbc)!=0 )
            string = _mbsinc( string );         /* skip over character */
    #endif

    /*** Return character address, or NULL if not found ***/
    if( !_NEARFAR(_mbterm,_fmbterm)(string) || ch==0 )
        return( (unsigned char _FFAR*) string );
    else
        return( NULL );
}