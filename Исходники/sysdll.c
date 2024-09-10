/* LoadLib
 *  load a dynamic library
 *
 *  "lib" [ OUT ] - return parameter for loaded library
 *
 *  "path" [ IN ] - NUL terminated string in directory-native
 *  character set denoting target library
 */
static
rc_t KDyldLoad ( KDyld *self, KDylib *lib, const wchar_t *path )
{
    DWORD err;
#if WE_WERE_BUILDING_FOR_WINDOWS_7_ALONE
    UINT errMode = GetErrorMode();
#endif

	if ( path == NULL )
	{
		if ( GetModuleHandleExW( 0, NULL, &( lib -> handle ) ) )
			return 0;

        return RC ( rcFS, rcDylib, rcLoading, rcNoObj, rcUnknown );
	}

    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOOPENFILEERRORBOX); /* suppress the message box in case of an error */
    lib -> handle = LoadLibraryW ( path );
#if WE_WERE_BUILDING_FOR_WINDOWS_7_ALONE
    SetErrorMode(errMode);
#endif
    if ( lib -> handle != NULL )
        return KDylibSetLogging ( lib );

    err = GetLastError ();
    switch ( err )
    {
    case ERROR_MOD_NOT_FOUND :
        return RC ( rcFS, rcDylib, rcLoading, rcPath, rcNotFound );
    case ERROR_BAD_EXE_FORMAT :
        return RC ( rcFS, rcDylib, rcLoading, rcFormat, rcInvalid );
    }

    return RC ( rcFS, rcDylib, rcLoading, rcNoObj, rcUnknown );
}