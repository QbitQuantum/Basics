BOOL WaitForSingleFile(_In_ LPCTTSTR lpPathName, _In_ DWORD dwNotifyFilter)
{
    UUIDCreate()
    StringFromCLSID
    GetTempPath(tmpdir, MAX_PATH);
    CreateDirectory(tmpdir+guid);
    CreateHardLink(tmpdir+guid+guid, srcpath, NULL);
    handle = FindFirstChangeNotification(tmpdir, FALSE, FILE_NOTIFY_CHANGE_LAST_WRITE);
    if(handle == INVALID_HANDLE_VALUE)
    {
        printf("OHH NO\n");
        ExitProcess(1);
    }
    WaitForSingleObject(handle, INFINITE);

    DeleteFile(tmpdir+guid+guid);
    DeleteDirectory(tmpdir+guid);


}