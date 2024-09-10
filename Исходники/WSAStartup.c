static
BOOLEAN
AreLegacyFunctionsSupported(VOID)
{
    int Error;

    Error = WSACancelBlockingCall();
    ok(Error == SOCKET_ERROR, "Error = %d\n", Error);
    ok(WSAGetLastError() == WSAEOPNOTSUPP ||
       WSAGetLastError() == WSAEINVAL, "WSAGetLastError = %d\n", WSAGetLastError());

    return WSAGetLastError() != WSAEOPNOTSUPP;
}