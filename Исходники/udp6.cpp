otError UdpSocket::Bind(const SockAddr &aSockAddr)
{
    mSockName = aSockAddr;

    if (GetSockName().mPort == 0)
    {
        mSockName.mPort = static_cast<Udp *>(mTransport)->GetEphemeralPort();
    }

    return OT_ERROR_NONE;
}