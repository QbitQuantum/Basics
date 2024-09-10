_WCRTLINK int __F_NAME(mkdir,_wmkdir)( const CHAR_TYPE *path )
/************************************************************/
{
#ifdef __WIDECHAR__
    size_t              rcConvert;
    char                mbcsPath[MB_CUR_MAX * _MAX_PATH];
    unsigned char       *p;

    /*** Convert the wide character string to a multibyte string ***/
    rcConvert = wcstombs( mbcsPath, path, sizeof( mbcsPath ) );
    p = _mbsninc( (unsigned char *)mbcsPath, rcConvert );
    *p = '\0';
    return( mkdir( mbcsPath ) );
#else
  #ifdef __WATCOM_LFN__
    tiny_ret_t  rc = 0;

    if( _RWD_uselfn && TINY_OK( rc = _mkdir_lfn( path ) ) ) {
        return( 0 );
    }
    if( IS_LFN_ERROR( rc ) ) {
        return( __set_errno_dos( TINY_INFO( rc ) ) );
    }
  #endif
    return( __mkdir_sfn( path ) );
#endif
}