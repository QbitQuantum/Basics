ULONG
DeleteRegistryKey(
    const LPWSTR DriverName
)
{
    LPWSTR RegistryPath;
    ULONG dwErrorCode;

    dwErrorCode = StringConcat(&RegistryPath, REGISTRY_PATH_PREFIX, DriverName);
    if (dwErrorCode)
        return GetLastError();

    dwErrorCode = SHDeleteKeyW(HKEY_LOCAL_MACHINE, RegistryPath);
    StringFree(RegistryPath);
    return dwErrorCode;
}