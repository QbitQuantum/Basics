BOOL __lib_SetCurrentDirectoryW( LPCWSTR lpPathName )
/***************************************************/
{
    if( WIN32_IS_NT ) {                                 /* NT */
        return( SetCurrentDirectoryW( lpPathName ) );
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
        osrc = SetCurrentDirectoryA( mbPathName );
        lib_free( mbPathName );
        return( osrc );
    }
}