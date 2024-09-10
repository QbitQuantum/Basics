/*
 * @implemented
 */
SOCKET
WSAAPI
WSASocketA(IN INT af,
           IN INT type,
           IN INT protocol,
           IN LPWSAPROTOCOL_INFOA lpProtocolInfo,
           IN GROUP g,
           IN DWORD dwFlags)
{
    WSAPROTOCOL_INFOW ProtocolInfoW;
    LPWSAPROTOCOL_INFOW p = &ProtocolInfoW;

    /* Convert Protocol Info to Wide */
    if (lpProtocolInfo)
    {
        /* Copy the Data */
        memcpy(&ProtocolInfoW,
               lpProtocolInfo,
               sizeof(WSAPROTOCOL_INFOA) - sizeof(CHAR) * (WSAPROTOCOL_LEN + 1));

        /* Convert the String */
        MultiByteToWideChar(CP_ACP,
                            0,
                            lpProtocolInfo->szProtocol,
                            -1,
                            ProtocolInfoW.szProtocol,
                            sizeof(ProtocolInfoW.szProtocol) / sizeof(WCHAR));
    }
    else
    {
        /* No Protocol Info Specified */
        p = NULL;
    }

    /* Call the Unicode Function */
    return WSASocketW(af,
                      type,
                      protocol,
                      p,
                      g,
                      dwFlags);
}