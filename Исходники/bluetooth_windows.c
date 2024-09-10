static int
bthPerformServiceLookup (
    BluetoothServiceLookupResult *result,
    ULONGLONG address, GUID *guid,
    DWORD beginFlags, DWORD nextFlags
) {
    int found = 0;

    if (bthStartSockets()) {
        SOCKADDR_BTH socketAddress = {
            .addressFamily = AF_BTH,
            .btAddr = address
        };

        char addressString[0X100];
        DWORD addressLength = sizeof(addressString);

        if (WSAAddressToString((SOCKADDR *)&socketAddress, sizeof(socketAddress),
                               NULL,
                               addressString, &addressLength) != SOCKET_ERROR) {
            HANDLE handle;

            CSADDR_INFO csa[] = {
                {
                    .RemoteAddr = {
                        .lpSockaddr = (SOCKADDR *)&socketAddress,
                        .iSockaddrLength = sizeof(socketAddress)
                    }
                }
            };

            WSAQUERYSET restrictions = {
                .dwNameSpace = NS_BTH,
                .lpszContext = addressString,
                .lpcsaBuffer = csa,
                .dwNumberOfCsAddrs = ARRAY_COUNT(csa),
                .lpServiceClassId = guid,
                .dwSize = sizeof(restrictions)
            };

            if (WSALookupServiceBegin(&restrictions, (LUP_FLUSHCACHE | beginFlags), &handle) != SOCKET_ERROR) {
                DWORD resultLength = sizeof(*result);

                if (WSALookupServiceNext(handle, nextFlags, &resultLength, &result->querySet) != SOCKET_ERROR) {
                    found = 1;
                } else {
                    static const DWORD exceptions[] = {
#ifdef WSA_E_NO_MORE
                        WSA_E_NO_MORE,
#endif /* WSA_E_NO_MORE */

#ifdef WSAENOMORE
                        WSAENOMORE,
#endif /* WSAENOMORE */

                        NO_ERROR
                    };

                    bthSocketError("WSALookupServiceNext", exceptions);
                }

                if (WSALookupServiceEnd(handle) == SOCKET_ERROR) {
                    bthSocketError("WSALookupServiceEnd", NULL);
                }
            } else {
                bthSocketError("WSALookupServiceBegin", NULL);
            }
        } else {