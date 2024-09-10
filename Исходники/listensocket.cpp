bool ListenSocket::Listen(int backlog) {
    const auto sockId = CreateSockId(TRANSPORT_TCP);
    if (sockId == INVALID_SOCKID) {
        return false;
    }

    int optValue = 1;
    auto optLength = static_cast<SockLen_t>(sizeof(optValue));
    auto ret = SetSockOpt(sockId, SOL_SOCKET, SO_REUSEADDR, &optValue, optLength);
    if (ret == SOCKET_ERROR) {
        DestroySockId(sockId);
        return false;
    }

    auto sockAddr = m_localHost.SockAddr();
    auto sockAddrLen = m_localHost.SockAddrLen();
    ret = bind(sockId, sockAddr, sockAddrLen);
    if (ret == SOCKET_ERROR) {
        DestroySockId(sockId);
        return false;
    }

    ret = listen(sockId, backlog);
    if (ret == SOCKET_ERROR) {
        DestroySockId(sockId);
        return false;
    }

    AttachSockId(sockId);
    return true;
}