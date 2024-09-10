/*
 *  Open a dynamic channel with the name given in szChannelName
 *  the output file handle can be used in ReadFile/WriteFile calls
 */
DWORD OpenDynamicChannel(LPCSTR szChannelName, HANDLE* phFile)
{
    HANDLE hWTSHandle = NULL;
    HANDLE hWTSFileHandle;
    PVOID vcFileHandlePtr = NULL;
    DWORD len;
    DWORD rc = ERROR_SUCCESS;

    hWTSHandle = WTSVirtualChannelOpenEx(WTS_CURRENT_SESSION, (LPSTR)szChannelName, WTS_CHANNEL_OPTION_DYNAMIC);

    if (!hWTSHandle)
    {
        rc = GetLastError();
        printf("WTSVirtualChannelOpenEx API Call Failed: GetLastError() = %d\n", GetLastError());
        goto exitpt;
    }

    BOOL bSucc = WTSVirtualChannelQuery(hWTSHandle, WTSVirtualFileHandle, &vcFileHandlePtr, &len);

    if ( !bSucc )
    {
        rc = GetLastError();
        goto exitpt;
    }
    if ( len != sizeof( HANDLE ))
    {
        rc = ERROR_INVALID_PARAMETER;
        goto exitpt;
    }
    hWTSFileHandle = *(HANDLE *)vcFileHandlePtr;

    bSucc = DuplicateHandle(
                GetCurrentProcess(),
                hWTSFileHandle,
                GetCurrentProcess(),
                phFile,
                0,
                FALSE,
                DUPLICATE_SAME_ACCESS );
    if ( !bSucc )
    {
        rc = GetLastError();
        goto exitpt;
    }

    rc = ERROR_SUCCESS;
exitpt:
    if ( vcFileHandlePtr )
    {
        WTSFreeMemory( vcFileHandlePtr );
    }
    if ( hWTSHandle )
    {
        WTSVirtualChannelClose( hWTSHandle );
    }
    return rc;
}