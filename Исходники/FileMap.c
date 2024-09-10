/*
 * @implemented
 */
LPVOID
NTAPI
MapViewOfFile(HANDLE hFileMappingObject,
              DWORD dwDesiredAccess,
              DWORD dwFileOffsetHigh,
              DWORD dwFileOffsetLow,
              SIZE_T dwNumberOfBytesToMap)
{
    /* Call the extended API */
    return MapViewOfFileEx(hFileMappingObject,
                           dwDesiredAccess,
                           dwFileOffsetHigh,
                           dwFileOffsetLow,
                           dwNumberOfBytesToMap,
                           NULL);
}