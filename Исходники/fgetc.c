static int __read_wide_char( FILE *fp, wchar_t *wc )
/**************************************************/
{
    if( fp->_flag & _BINARY ) {
        /*** Read a wide character ***/
        return( fread( wc, sizeof( wchar_t ), 1, fp ) );
    } else {
        char            mbc[MB_CUR_MAX];
        wchar_t         wcTemp;
        int             rc;

        /*** Read the multibyte character ***/
        if( !fread( &mbc[0], 1, 1, fp ) )
            return( 0 );

        if( _ismbblead( (unsigned char)mbc[0] ) ) {
            if( !fread( &mbc[1], 1, 1, fp ) )
                return( 0 );
        }

        /*** Convert it to wide form ***/
        rc = mbtowc( &wcTemp, mbc, MB_CUR_MAX );
        if( rc >= 0 ) {
            *wc = wcTemp;
            return( 1 );
        } else {
            _RWD_errno = EILSEQ;
            return( 0 );
        }
    }
}