DWORD
OpenDeviceKey(
    HDEVINFO Handle,
    PSP_DEVINFO_DATA  FILTERINFOData,
    DWORD KeyType,
    REGSAM DesiredAccess,
    OUT HKEY * OutKey)
{
    HKEY hKey;

    /* try open device registry key */
    hKey = SetupDiOpenDevRegKey(Handle, FILTERINFOData, DICS_FLAG_CONFIGSPECIFIC, 0, KeyType, DesiredAccess);

    if (hKey == INVALID_HANDLE_VALUE)
        return GetLastError();

    /* store result */
    *OutKey = hKey;

    return ERROR_SUCCESS;
}