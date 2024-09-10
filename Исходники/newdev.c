/*
* @implemented
*/
BOOL WINAPI
UpdateDriverForPlugAndPlayDevicesA(
    IN HWND hwndParent,
    IN LPCSTR HardwareId,
    IN LPCSTR FullInfPath,
    IN DWORD InstallFlags,
    OUT PBOOL bRebootRequired OPTIONAL)
{
    BOOL Result;
    LPWSTR HardwareIdW = NULL;
    LPWSTR FullInfPathW = NULL;

    int len = MultiByteToWideChar(CP_ACP, 0, HardwareId, -1, NULL, 0);
    HardwareIdW = HeapAlloc(GetProcessHeap(), 0, len * sizeof(WCHAR));
    if (!HardwareIdW)
    {
        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        return FALSE;
    }
    MultiByteToWideChar(CP_ACP, 0, HardwareId, -1, HardwareIdW, len);

    len = MultiByteToWideChar(CP_ACP, 0, FullInfPath, -1, NULL, 0);
    FullInfPathW = HeapAlloc(GetProcessHeap(), 0, len * sizeof(WCHAR));
    if (!FullInfPathW)
    {
        HeapFree(GetProcessHeap(), 0, HardwareIdW);
        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        return FALSE;
    }
    MultiByteToWideChar(CP_ACP, 0, FullInfPath, -1, FullInfPathW, len);

    Result = UpdateDriverForPlugAndPlayDevicesW(
        hwndParent,
        HardwareIdW,
        FullInfPathW,
        InstallFlags,
        bRebootRequired);

    HeapFree(GetProcessHeap(), 0, HardwareIdW);
    HeapFree(GetProcessHeap(), 0, FullInfPathW);

    return Result;
}