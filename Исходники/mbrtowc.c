_WCRTLINK int _NEARFAR(mbrtowc,_fmbrtowc)( wchar_t _FFAR *pwc, const char _FFAR *s, size_t n, mbstate_t _FFAR *ps )
{
    int                 rc;

    /*** Check the simple cases ***/
    if( s == NULL )  return( 0 );           /* always in initial state */
    if( n == 0 )  return( -2 );             /* can't process nothing */

    /*** Check for a valid multibyte character ***/
    rc = _NEARFAR(mbtowc,_fmbtowc)( pwc, s, n );
    if( rc != -1 ) {
        return( rc );
    } else if( n < MB_LEN_MAX && _ismbblead( (unsigned char)*s ) ) {
        return( -2 );                       /* incomplete, possibly valid */
    } else {
        _RWD_errno = EILSEQ;                /* encoding error */
        return( -1 );
    }
}