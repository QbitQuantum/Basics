static int is_directory( const CHAR_TYPE *name )
/**********************************************/
{
    UINT_WC_TYPE    curr_ch;
    UINT_WC_TYPE    prev_ch;

    curr_ch = NULLCHAR;
    for(;;) {
        prev_ch = curr_ch;
#ifdef __WIDECHAR__
        curr_ch = *name;
#else
        curr_ch = _mbsnextc( (unsigned char *)name );
#endif
        if( curr_ch == NULLCHAR ) {
            if( prev_ch == '\\' || prev_ch == '/' || prev_ch == ':' ){
                /* directory, need add "*.*" */
                return( 2 );
            }
            if( prev_ch == '.' ){
                /* directory, need add "\\*.*" */
                return( 1 );
            }
            /* without wildcards maybe file or directory, need next check */
            /* need add "\\*.*" if directory */
            return( 0 );
        }
        if( curr_ch == '*' )
            break;
        if( curr_ch == '?' )
            break;
#ifdef __WIDECHAR__
        ++name;
#else
        name = (char *)_mbsinc( (unsigned char *)name );
#endif
    }
    /* with wildcard must be file */
    return( -1 );
}