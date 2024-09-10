int TurnerClassic::select_provider (turner_provider provider, LPVOID data)
{
    close();

    IDirectPlayLobbyA   *lobby;
    DWORD               size;
    char                address[128];
    DWORD               adsize = sizeof(address);

    int res = DirectPlayLobbyCreate( NULL, &lobby, NULL, NULL, 0 );
    if (FAILED(res))
        return res;

    switch (provider)
    {
        case TURNER_PROVIDER_IPX:
            res = lobby->CreateAddress( DPSPGUID_IPX, DPAID_INet,
                                        NULL, 0, address, &adsize );
            break;
        case TURNER_PROVIDER_TCPIP:
            size = (data) ? strlen((char*)data)+1 : 0;
            res = lobby->CreateAddress( DPSPGUID_TCPIP, DPAID_INet,
                                        data, size, address, &adsize );
            break;
        case TURNER_PROVIDER_MODEM:
            size = (data) ? strlen((char*)data)+1 : 0;
            res = lobby->CreateAddress( DPSPGUID_MODEM, DPAID_Phone,
                                        data, size, address, &adsize );
            break;
        case TURNER_PROVIDER_SERIAL:
            size = (data) ? sizeof(DPCOMPORTADDRESS) : 0;
            res = lobby->CreateAddress( DPSPGUID_SERIAL, DPAID_ComPort,
                                        data, size, address, &adsize );
            break;
        default:
            lobby->Release();
            return DPERR_UNSUPPORTED;
    }

    lobby->Release();

    if (FAILED(res))
        return res;

//��� Initialize COM
    if (!TurnerCOMInit)
    {
        CoInitialize(NULL);
        TurnerCOMInit=1;
    }

//��� Connect to DirectPlay
    res = CoCreateInstance(CLSID_DirectPlay,
                           NULL,
                           CLSCTX_INPROC_SERVER,
                           IID_IDirectPlay4A,
                           (void **) &pIDP);

    if (FAILED(res))
    {
        pIDP=0;
        return res;
    }

    res = pIDP->InitializeConnection(address, 0);
    if (FAILED(res))
    {
        pIDP->Release();
        pIDP = 0;
    }

    return res;
}