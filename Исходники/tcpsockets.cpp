TCPServerSocket::TCPServerSocket(int iPortNo, int iBackLog, bool bUseIPv6)
        : TCPSocket(bUseIPv6)
{
    const int   iReUseAddrFlag = 1;

    SetSockOpt(SOL_SOCKET, SO_REUSEADDR, &iReUseAddrFlag, sizeof(iReUseAddrFlag));
    Bind(iPortNo);
    SetLocal();
    Listen(iBackLog);
}