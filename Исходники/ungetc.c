_WCRTLINK INTCHAR_TYPE __F_NAME(ungetc,ungetwc)( INTCHAR_TYPE c, FILE *fp )
{
    if( c == INTCHAR_EOF ) {    /* cannot push EOF */
        return( c );
    }
    _ValidFile( fp, INTCHAR_EOF );
    _AccessFile( fp );

    /*** Deal with stream orientation ***/
    ORIENT_STREAM( fp, INTCHAR_EOF );

    if( fp->_flag & _DIRTY ) {        /* cannot unget after a put */
        _ReleaseFile( fp );
        return( INTCHAR_EOF );
    }
    if(( fp->_flag & _READ ) == 0 ) { /* not open for input */
        _ReleaseFile( fp );
        return( INTCHAR_EOF );
    }
    if( _FP_BASE( fp ) == NULL ) {      /* no buffer allocated */
        __ioalloc( fp );
    }
#ifdef __WIDECHAR__
    if( fp->_flag & _BINARY ) {
        /*** Leave the character in wide form ***/
        if( fp->_cnt == 0 ) {           /* read buffer is empty */
            fp->_cnt = sizeof( wchar_t );
            fp->_ptr = _FP_BASE( fp ) + fp->_bufsize - sizeof( wchar_t );
            fp->_flag |= _UNGET;                    /* 10-mar-90 */
            memcpy( fp->_ptr, &c, sizeof( wchar_t ) );
        } else if( fp->_ptr != _FP_BASE( fp ) ) {
            fp->_cnt += sizeof( wchar_t );
            fp->_ptr -= sizeof( wchar_t );
            fp->_flag |= _UNGET;
            memcpy( fp->_ptr, &c, sizeof( wchar_t ) );
        } else {                        /* read buffer is full */
            _ReleaseFile( fp );
            return( WEOF );
        }
    } else {
        unsigned char   mbc[MB_CUR_MAX];
        int             mbcLen;

        /*** Convert the character to multibyte form ***/
        if( wctomb( (char *)mbc, c ) == -1 ) {
            _RWD_errno = EILSEQ;
            return( WEOF );
        }
        mbcLen = _mbclen( mbc );

        /*** Store the converted character ***/
        if( fp->_cnt == 0 ) {           /* read buffer is empty */
            fp->_cnt = mbcLen;
            fp->_ptr = _FP_BASE( fp ) + fp->_bufsize - mbcLen;
            fp->_flag |= _UNGET;                            /* 10-mar-90 */
            _mbccpy( fp->_ptr, mbc );
        } else if( fp->_ptr != _FP_BASE( fp ) ) {
            fp->_cnt += mbcLen;
            fp->_ptr -= mbcLen;
            fp->_flag |= _UNGET;
            _mbccpy( fp->_ptr, mbc );
        } else {                        /* read buffer is full */
            _ReleaseFile( fp );
            return( WEOF );
        }
    }
#else
    if( fp->_cnt == 0 ) {               /* read buffer is empty */
        fp->_cnt = 1;
        fp->_ptr = _FP_BASE( fp ) + fp->_bufsize - 1;
        fp->_flag |= _UNGET;                                /* 10-mar-90 */
        *fp->_ptr = c;
    } else if( fp->_ptr != _FP_BASE( fp ) ) {
        fp->_cnt++;
        fp->_ptr--;
        if( *fp->_ptr != c ) {
            fp->_flag |= _UNGET;                            /* 10-mar-90 */
        }
        *fp->_ptr = c;
    } else {                            /* read buffer is full */
        _ReleaseFile( fp );
        return( EOF );
    }
#endif
    fp->_flag &= ~ _EOF;

    _ReleaseFile( fp );
    return( (UCHAR_TYPE)c );
}