DWORD SrvConOpen(PWCHAR Host, PWCHAR Port, PSRV_CON *pSrvCon)
{
    SOCKET Socket;
    DWORD Err;
    ADDRINFOW Hints, *AddrInfo;
    PSRV_CON SrvCon;
    int OptVal;

    SrvCon = malloc(sizeof(*SrvCon));
    if (!SrvCon)
        return FB_E_NO_MEMORY;

    memset(SrvCon, 0, sizeof(*SrvCon));
    memset(&Hints, 0, sizeof(Hints));

    Hints.ai_family = AF_INET;
    Hints.ai_socktype = SOCK_STREAM;
    Hints.ai_protocol = IPPROTO_TCP;
    Hints.ai_flags = AI_PASSIVE;

    if (GetAddrInfoW(Host, Port, &Hints, &AddrInfo)) {
        Err = WSAGetLastError();
        printf("GetAddrInfoW failed Error %d\n", Err);
        free(SrvCon);
        return Err;
    }

    Socket = socket(AddrInfo->ai_family, AddrInfo->ai_socktype,
                    AddrInfo->ai_protocol);
    if (Socket == INVALID_SOCKET) {
        Err = WSAGetLastError();
        FreeAddrInfoW(AddrInfo);
        free(SrvCon);
        return Err;
    }

    OptVal = 1;
    if (setsockopt(Socket, SOL_SOCKET, SO_REUSEADDR,
                    (char *) &OptVal, sizeof (OptVal))) {
        Err = WSAGetLastError();
        printf("socket connect failed Error %d\n", Err);
        FreeAddrInfoW(AddrInfo);
        closesocket(Socket);
        free(SrvCon);
        return Err;
    }

    if (connect(Socket, AddrInfo->ai_addr, (int)AddrInfo->ai_addrlen)) {
        Err = WSAGetLastError();
        printf("socket connect failed Error %d\n", Err);
        FreeAddrInfoW(AddrInfo);
        closesocket(Socket);
        free(SrvCon);
        return Err;
    }

    SrvCon->Socket = Socket;
    *pSrvCon = SrvCon;
    return 0;
}