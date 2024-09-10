/// <summary>
/// Unlink memory VAD node
/// </summary>
/// <param name="imageMem">Image to purge</param>
/// <returns>bool on success</returns>
bool MMap::UnlinkVad( const MemBlock& imageMem )
{
    HANDLE hFile = CreateFile( _T( "\\\\.\\VadPurge" ), GENERIC_ALL, 0, NULL, OPEN_EXISTING, 0, NULL );

    // Load missing driver
    if (hFile == INVALID_HANDLE_VALUE)
    {
        std::wstring drvPath = Utils::GetExeDirectory() + L"\\";

        if (IsWindows8Point1OrGreater())
            drvPath += L"VadPurge81.sys";
        else if(IsWindows8OrGreater())
            drvPath += L"VadPurge8.sys";
        else if(IsWindows7OrGreater())
            drvPath += L"VadPurge7.sys";

        NTSTATUS status = Utils::LoadDriver( L"VadPurge", drvPath );

        if (status != ERROR_SUCCESS && status != STATUS_IMAGE_ALREADY_LOADED)
            return false;

        hFile = CreateFile( _T( "\\\\.\\VadPurge" ), GENERIC_ALL, 0, NULL, OPEN_EXISTING, 0, NULL );
    }

    //
    // Lock pages in working set before unlinking
    // UserMode page faults can't be resolved without VAD record
    //
    if (hFile != INVALID_HANDLE_VALUE)
    {
        //
        // Adjust working set and lock pages
        //
        SIZE_T sizeMin = 0, sizeMax = 0;
        BOOL ret = FALSE;

        GetProcessWorkingSetSize( _process.core().handle(), &sizeMin, &sizeMax );
        SetProcessWorkingSetSize( _process.core().handle(), sizeMin + imageMem.size(), sizeMax + imageMem.size() );

        PVOID pBase = imageMem.ptr<PVOID>();
        ULONG size = static_cast<ULONG>(imageMem.size());
        NTSTATUS status = GET_IMPORT( NtLockVirtualMemory )(_process.core().handle(), &pBase, &size, 1);

        // Continue only if pages are locked
        if (status == STATUS_SUCCESS)
        {
            PURGE_DATA data = { _process.core().pid(), 1, { imageMem.ptr<ULONGLONG>(), imageMem.size() } };
            DWORD junk = 0;

            ret = DeviceIoControl( hFile, static_cast<DWORD>(IOCTL_VADPURGE_PURGE), &data, sizeof(data), NULL, 0, &junk, NULL );
        }

        CloseHandle( hFile );

        return (status == STATUS_SUCCESS && ret == TRUE) ? true : false;
    }

    return false;
}