DWORD __lib_GetCurrentDirectoryW( DWORD nBufferLength, LPWSTR lpBuffer )
/**********************************************************************/
{
    if( WIN32_IS_NT ) {                                 /* NT */
        return( GetCurrentDirectoryW( nBufferLength, lpBuffer ) );
    } else {                                            /* Win95 or Win32s */
        char *          mbBuffer;
        BOOL            osrc;
        size_t          cvt;
        size_t          len;

        /*** Allocate some memory ***/
        len = _MAX_PATH*MB_CUR_MAX + 1;
        mbBuffer = lib_malloc( len );
        if( mbBuffer == NULL ) {
            return( FALSE );
        }

        /*** Call the OS ***/
        osrc = GetCurrentDirectoryA( len, mbBuffer );
        if( osrc == 0 ) {
            lib_free( mbBuffer );
            return( 0 );
        }

        /*** If buffer too small, return required size ***/
        if( _mbslen( mbBuffer ) + 1  >  nBufferLength ) {
            lib_free( mbBuffer );
            return( osrc );
        }

        /*** Convert returned info ***/
        cvt = mbstowcs( lpBuffer, mbBuffer, nBufferLength );
        if( cvt == (size_t)-1 ) {
            lib_free( mbBuffer );
            return( 0 );
        }

        return( osrc );
    }
}