_WCRTLINK unsigned char _FFAR *_NEARFAR(_mbstok_r,_fmbstok_r)( unsigned char _FFAR *str, const unsigned char _FFAR *delim, unsigned char _FFAR **ptr )
{
    unsigned char _FFAR *   string_start;
    int                     count;
    int                     char_len;

//    if( !__IsDBCS )  return( strtok( str, delim ) );

    if( str == NULL ) {
        str = *ptr;
        if( str == NULL )
            return( NULL );
    }

    /*** Skip characters until we reach one not in 'delim' ***/
    #ifdef __FARFUNC__
        while( !_fmbterm(str) && _fmbschr(delim,_fmbsnextc(str))!=NULL )
            str = _fmbsinc( str );
    #else
        while( !_mbterm(str) && _mbschr(delim,_mbsnextc(str))!=NULL )
            str = _mbsinc( str );
    #endif
    if( _NEARFAR(_mbterm,_fmbterm)(str) )  return( NULL );
    string_start = str;

    /*** Skip characters until we reach one in 'delim' ***/
    #ifdef __FARFUNC__
        while( !_fmbterm(str) && _fmbschr(delim,_fmbsnextc(str))==NULL )
            str = _fmbsinc( str );
    #else
        while( !_mbterm(str) && _mbschr(delim,_mbsnextc(str))==NULL )
            str = _mbsinc( str );
    #endif

    /*** Handle the next token ***/
    if( !_NEARFAR(_mbterm,_fmbterm)(str) ) {
        char_len = _NEARFAR(_mbclen,_fmbclen)( str ); /* get char length */
        for( count=0; count<char_len; count++ )
            str[count] = '\0';                  /* replace delim with NULL */
        str += char_len;                        /* start of next token */
        *ptr = str; /* save next start */
        return( string_start );                 /* return next token start */
    } else {
        *ptr = NULL;/* no more tokens */
        return( string_start );                 /* return same token */
    }
}