bool IocpTransmitStrategy::PostSend() {
    auto& socketBuffer = m_transmitSocket.TheSocketBuffer();

    const auto sendLength = socketBuffer.PrepareSendPlan();
    if (sendLength < 1) {
        m_sendOperation.SetBusy(false);
        return true;
    }

    const auto count = socketBuffer.SetupSendIov(m_sendOperation.m_iov);

    DWORD bytesSent = 0;
    const auto& transmitSockId = m_transmitSocket.GetSockId();
    const auto ret = WSASend(transmitSockId
        , m_sendOperation.m_iov
        , count
        , &bytesSent
        , 0
        , &m_sendOperation.m_overlapped
        , NULL);
    if (ret != 0) {
        const auto error = WSAGetLastError();
        if (error != ERROR_IO_PENDING) {
            HandleFailure(&m_sendOperation, 0, error);
            return false;
        }
    }

    return true;
}