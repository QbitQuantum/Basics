/// <summary>
/// Get physical device paths.
/// </summary>
/// <param name="drives">Found drives</param>
/// <returns>Error code</returns>
DWORD PhysicalDisk::GetPhysicalPaths( std::vector<std::wstring>& drives )
{
    HDEVINFO diskClassDevices = nullptr;
    GUID diskClassDeviceInterfaceGuid = GUID_DEVINTERFACE_DISK;
    SP_DEVICE_INTERFACE_DATA deviceInterfaceData = { 0 };
    PSP_DEVICE_INTERFACE_DETAIL_DATA deviceInterfaceDetailData = nullptr;
    DWORD requiredSize = 0;
    DWORD deviceIndex = 0;

    HANDLE disk = INVALID_HANDLE_VALUE;
    STORAGE_DEVICE_NUMBER diskNumber = { 0 };
    DWORD bytesReturned = 0;

    //
    // Get the handle to the device information set for installed
    // disk class devices. Returns only devices that are currently
    // present in the system and have an enabled disk device
    // interface.
    //
    diskClassDevices = SetupDiGetClassDevs( &diskClassDeviceInterfaceGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE );
    if (diskClassDevices == INVALID_HANDLE_VALUE)
        return GetLastError();

    ZeroMemory( &deviceInterfaceData, sizeof(SP_DEVICE_INTERFACE_DATA) );
    deviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

    for (; SetupDiEnumDeviceInterfaces( diskClassDevices, NULL, &diskClassDeviceInterfaceGuid, deviceIndex, &deviceInterfaceData ); ++deviceIndex)
    {
        SetupDiGetDeviceInterfaceDetailW( diskClassDevices, &deviceInterfaceData, NULL, 0, &requiredSize, NULL );
        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
            goto Exit;

        deviceInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc( requiredSize );

        ZeroMemory( deviceInterfaceDetailData, requiredSize );
        deviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

        if (!SetupDiGetDeviceInterfaceDetail( diskClassDevices, &deviceInterfaceData, deviceInterfaceDetailData, requiredSize, NULL, NULL ))
            goto Exit;

        disk = CreateFile( deviceInterfaceDetailData->DevicePath,
                           GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
                           NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

        if (disk == INVALID_HANDLE_VALUE)
            goto Exit;

        if (!DeviceIoControl( disk, IOCTL_STORAGE_GET_DEVICE_NUMBER, NULL, 0, &diskNumber, sizeof(STORAGE_DEVICE_NUMBER), &bytesReturned, NULL ))
            goto Exit;

        CloseHandle( disk );
        disk = INVALID_HANDLE_VALUE;

        drives.emplace_back( L"\\\\?\\PhysicalDrive" + std::to_wstring( diskNumber.DeviceNumber ) );

        if (deviceInterfaceDetailData)
        {
            free( deviceInterfaceDetailData );
            deviceInterfaceDetailData = nullptr;
        }
    }

Exit:

    if (INVALID_HANDLE_VALUE != diskClassDevices)
        SetupDiDestroyDeviceInfoList( diskClassDevices );

    if (INVALID_HANDLE_VALUE != disk)
        CloseHandle( disk );

    if (deviceInterfaceDetailData)
        free( deviceInterfaceDetailData );

    return GetLastError();
}