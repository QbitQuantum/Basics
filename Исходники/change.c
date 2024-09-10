/****************************************************************************
 *		FindFirstChangeNotificationW (KERNEL32.@)
 */
HANDLE WINAPI FindFirstChangeNotificationW( LPCWSTR lpPathName, BOOL bWatchSubtree,
                                            DWORD dwNotifyFilter)
{
    UNICODE_STRING nt_name;
    OBJECT_ATTRIBUTES attr;
    NTSTATUS status;
    HANDLE handle = INVALID_HANDLE_VALUE;

    TRACE( "%s %d %x\n", debugstr_w(lpPathName), bWatchSubtree, dwNotifyFilter );

    if (!RtlDosPathNameToNtPathName_U( lpPathName, &nt_name, NULL, NULL ))
    {
        SetLastError( ERROR_PATH_NOT_FOUND );
        return handle;
    }

    attr.Length = sizeof(attr);
    attr.RootDirectory = 0;
    attr.Attributes = OBJ_CASE_INSENSITIVE;
    attr.ObjectName = &nt_name;
    attr.SecurityDescriptor = NULL;
    attr.SecurityQualityOfService = NULL;

    status = NtOpenFile( &handle, FILE_LIST_DIRECTORY | SYNCHRONIZE,
                         &attr, &FindFirstChange_iosb,
                         FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                         FILE_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT );
    RtlFreeUnicodeString( &nt_name );

    if (status != STATUS_SUCCESS)
    {
        SetLastError( RtlNtStatusToDosError(status) );
        return INVALID_HANDLE_VALUE;
    }

    status = NtNotifyChangeDirectoryFile( handle, NULL, NULL, NULL,
                                          &FindFirstChange_iosb,
                                          NULL, 0, dwNotifyFilter, bWatchSubtree );
    if (status != STATUS_PENDING)
    {
        NtClose( handle );
        SetLastError( RtlNtStatusToDosError(status) );
        return INVALID_HANDLE_VALUE;
    }
    return handle;
}