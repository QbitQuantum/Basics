/*
 * @implemented
 */
SOCKET
EXPORT
WSASocketA(IN  INT af,
           IN  INT type,
           IN  INT protocol,
           IN  LPWSAPROTOCOL_INFOA lpProtocolInfo,
           IN  GROUP g,
           IN  DWORD dwFlags)
/*
 * FUNCTION: Creates a new socket
 */
{
    WSAPROTOCOL_INFOW ProtocolInfoW;
    LPWSAPROTOCOL_INFOW p;
    UNICODE_STRING StringU;
    ANSI_STRING StringA;

    WS_DbgPrint(MAX_TRACE, ("af (%d)  type (%d)  protocol (%d).\n",
    af, type, protocol));

    if (lpProtocolInfo)
    {
        memcpy(&ProtocolInfoW,
               lpProtocolInfo,
               sizeof(WSAPROTOCOL_INFOA) - sizeof(CHAR) * (WSAPROTOCOL_LEN + 1));
        RtlInitAnsiString(&StringA, (LPSTR)lpProtocolInfo->szProtocol);
        RtlInitUnicodeString(&StringU, (LPWSTR)&ProtocolInfoW.szProtocol);
        RtlAnsiStringToUnicodeString(&StringU, &StringA, FALSE);
        p = &ProtocolInfoW;
    }
    else
    {
        p = NULL;
    }

    return WSASocketW(af,
                      type,
                      protocol,
                      p,
                      g,
                      dwFlags);
}