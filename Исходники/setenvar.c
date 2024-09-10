BOOL __lib_SetEnvironmentVariableW( LPCWSTR lpName, LPCWSTR lpValue )
/*******************************************************************/
{
    if( WIN32_IS_NT ) {                                 /* NT */
        return( SetEnvironmentVariableW( lpName, lpValue ) );
    } else {                                            /* Win95 or Win32s */
        char *          mbName;
        char *          mbValue;
        BOOL            osrc;
        size_t          cvt;
        size_t          len;

        /*** Allocate some memory ***/
        len = wcslen( lpName ) * MB_CUR_MAX + 1;
        mbName = lib_malloc( len );
        if( mbName == NULL ) {
            return( FALSE );
        }
        if( lpValue == NULL ) {
            mbValue = NULL;
        } else {
            len = wcslen( lpValue ) * MB_CUR_MAX + 1;
            mbValue = lib_malloc( len );
            if( mbValue == NULL ) {
                lib_free( mbName );
                return( FALSE );
            }
        }

        /*** Prepare to call the OS ***/
        cvt = wcstombs( mbName, lpName, len );
        if( cvt == (size_t)-1 ) {
            lib_free( mbName );
            if( mbValue != NULL )  lib_free( mbValue );
            return( FALSE );
        }
        if( mbValue != NULL ) {
            cvt = wcstombs( mbValue, lpValue, len );
            if( cvt == (size_t)-1 ) {
                lib_free( mbValue );
                return( FALSE );
            }
        }

        /*** Call the OS ***/
        osrc = SetEnvironmentVariableA( mbName, mbValue );
        lib_free( mbName );
        if( mbValue != NULL )  lib_free( mbValue );
        return( osrc );
    }
}