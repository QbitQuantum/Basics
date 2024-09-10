BOOL __lib_CreateDirectoryW( LPCWSTR lpPathName,
                             LPSECURITY_ATTRIBUTES lpSecurityAttributes )
/***********************************************************************/
{
    if( WIN32_IS_NT ) {                                 /* NT */
        return( CreateDirectoryW( lpPathName, lpSecurityAttributes ) );
    } else {                                            /* Win95 or Win32s */
        char *          mbPathName;
        BOOL            osrc;
        size_t          cvt;
        size_t          len;

        /*** Allocate some memory ***/
        len = wcslen( lpPathName ) * MB_CUR_MAX + 1;
        mbPathName = lib_malloc( len );
        if( mbPathName == NULL ) {
            return( FALSE );
        }

        /*** Prepare to call the OS ***/
        cvt = wcstombs( mbPathName, lpPathName, len );
        if( cvt == (size_t)-1 ) {
            lib_free( mbPathName );
            return( FALSE );
        }

        /*** Call the OS ***/
        osrc = CreateDirectoryA( mbPathName, lpSecurityAttributes );
        lib_free( mbPathName );
        return( osrc );
    }
}