INT
SockLoadTransportList(
    PWSTR *TransportList)
{
    ULONG	TransportListSize;
    HKEY	KeyHandle;
    LONG	Status;

    TRACE("Called\n");

    /* Open the Transports Key */
    Status = RegOpenKeyExW (HKEY_LOCAL_MACHINE,
                            L"SYSTEM\\CurrentControlSet\\Services\\Winsock\\Parameters",
                            0,
                            KEY_READ,
                            &KeyHandle);

    /* Check for error */
    if (Status) {
        ERR("Error reading transport list registry\n");
        return WSAEINVAL;
    }

    /* Get the Transport List Size */
    Status = RegQueryValueExW(KeyHandle,
                              L"Transports",
                              NULL,
                              NULL,
                              NULL,
                              &TransportListSize);

    /* Check for error */
    if (Status) {
        ERR("Error reading transport list registry\n");
        return WSAEINVAL;
    }

    /* Allocate Memory for the Transport List */
    *TransportList = HeapAlloc(GlobalHeap, 0, TransportListSize);

    /* Check for error */
    if (*TransportList == NULL) {
        ERR("Buffer allocation failed\n");
        return WSAEINVAL;
    }

    /* Get the Transports */
    Status = RegQueryValueExW (KeyHandle,
                               L"Transports",
                               NULL,
                               NULL,
                               (LPBYTE)*TransportList,
                               &TransportListSize);

    /* Check for error */
    if (Status) {
        ERR("Error reading transport list registry\n");
        HeapFree(GlobalHeap, 0, *TransportList);
        return WSAEINVAL;
    }

    /* Close key and return */
    RegCloseKey(KeyHandle);
    return 0;
}