BOOL WINAPI GetUserProfileDirectoryA( HANDLE hToken, LPSTR lpProfileDir,
                     LPDWORD lpcchSize )
{
    BOOL ret;
    WCHAR *dirW = NULL;

    TRACE( "%p %p %p\n", hToken, lpProfileDir, lpcchSize );

    if (!lpProfileDir || !lpcchSize)
    {
        SetLastError( ERROR_INVALID_PARAMETER );
        return FALSE;
    }
    if (!(dirW = HeapAlloc( GetProcessHeap(), 0, *lpcchSize * sizeof(WCHAR) )))
        return FALSE;

    if ((ret = GetUserProfileDirectoryW( hToken, dirW, lpcchSize )))
        WideCharToMultiByte( CP_ACP, 0, dirW, *lpcchSize, lpProfileDir, *lpcchSize, NULL, NULL );

    HeapFree( GetProcessHeap(), 0, dirW );
    return ret;
}