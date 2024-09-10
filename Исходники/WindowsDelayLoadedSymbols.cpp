LPVOID DL_MapViewOfFileExNuma(HANDLE hFileMappingObject, DWORD dwDesiredAccess, DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow, SIZE_T dwNumberOfBytesToMap, LPVOID lpBaseAddress, DWORD nndPreferred)
{
    typedef LPVOID (WINAPI * MapViewOfFileExNuma_t)(HANDLE, DWORD, DWORD, DWORD, SIZE_T, LPVOID, DWORD);
    static auto fcn = (MapViewOfFileExNuma_t)GetKernelProcAddress("MapViewOfFileExNuma");
    if (not fcn) return MapViewOfFileEx(hFileMappingObject, dwDesiredAccess, dwFileOffsetHigh, dwFileOffsetLow, dwNumberOfBytesToMap, lpBaseAddress);
    return fcn(hFileMappingObject, dwDesiredAccess, dwFileOffsetHigh, dwFileOffsetLow, dwNumberOfBytesToMap, lpBaseAddress, nndPreferred);
}