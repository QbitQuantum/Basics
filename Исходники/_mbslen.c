_WCRTLINK size_t _NEARFAR(__mbslen,__fmbslen)( unsigned char const _FFAR *s )
{
    size_t              count = 0;

    if( __IsDBCS ) {
        while( *s != '\0' ) {
            s += _ismbblead(*s) ? 2 : 1;/* point to next char */
            count++;                    /* update count */
        }
        return( count );
    } else {
        return( _NEARFAR(strlen,_fstrlen)( s ) );
    }
}