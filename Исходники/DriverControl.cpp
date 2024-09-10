/// <summary>
/// Reload driver
/// </summary>
/// <param name="path">Path to the driver file</param>
/// <returns>Status code</returns>
NTSTATUS DriverControl::Reload( std::wstring path /*= L"" */ )
{
    Unload();

    // Use default path
    if (path.empty())
    {
        const wchar_t* filename = nullptr;

        if (IsWindows10OrGreater())
            filename = BLACKBONE_FILE_NAME_10;
        else if (IsWindows8Point1OrGreater())
            filename = BLACKBONE_FILE_NAME_81;
        else if (IsWindows8OrGreater())
            filename = BLACKBONE_FILE_NAME_8;
        else if (IsWindows7OrGreater())
            filename = BLACKBONE_FILE_NAME_7;
        else
            filename = BLACKBONE_FILE_NAME;

        path = Utils::GetExeDirectory() + L"\\" + filename;
    }

    _loadStatus = LoadDriver( DRIVER_SVC_NAME, path );
    if (!NT_SUCCESS( _loadStatus ))
    {
        BLACKBONE_TRACE( L"Failed to load driver %ls. Status 0x%X", path.c_str(), _loadStatus );
        return _loadStatus;
    }

    _hDriver = CreateFileW( 
        BLACKBONE_DEVICE_FILE, 
        GENERIC_READ | GENERIC_WRITE, 
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL, OPEN_EXISTING, 0, NULL
        );

    if (!_hDriver)
    {
        _loadStatus = LastNtStatus();
        BLACKBONE_TRACE( L"Failed to open driver handle. Status 0x%X", _loadStatus );
        return _loadStatus;
    }

    return _loadStatus;
}