bool NetSocket::PostSend()
{
    int status = _netStatus.load();
    int expected = status | NET_STATUS_CONNECTED & NET_STATUS_RECV_PENDING & (!NET_STATUS_SEND_PENDING);
    int desired = expected | NET_STATUS_SEND_PENDING;

    if (!_netStatus.compare_exchange_strong(expected, desired))
    {
        DebugPrint("PostSend: netStatus exchange failed: current(0x%x)", status);
        return false;
    }

    size_t sendQueueSize = _sendQueue.unsafe_size();
    if (sendQueueSize == 0)
    {
        DebugPrint("PostSend: send queue is empty.");
        return false;
    }

    NetIoBuffer* sendOP = new NetIoBuffer(NetCompletionOP::OP_WRITE);
    sendOP->Reset(GetSocket());

    std::vector<WSABUF> wbufs;
    wbufs.resize(sendQueueSize);

    MemoryBlock* buffer = nullptr;
    int idx = 0;
    while (_sendQueue.try_pop(buffer))
    {
        wbufs[idx].buf = buffer->GetData();
        wbufs[idx].len = buffer->GetDataLen();
        sendOP->PushData(buffer);
        idx++;
    }

    int rc = WSASend(
        GetSocket(),
        &(wbufs[0]),
        static_cast<DWORD>(wbufs.size()),
        NULL,
        0,
        &(sendOP->ol),
        NULL
    );

    if (rc == SOCKET_ERROR)
    {
        if (WSAGetLastError() != WSA_IO_PENDING)
        {
            DebugPrint("PostSend: WSASend* failed: %s", SocketGetLastErrorString().c_str());
            Disconnect(NET_CTYPE_SYSTEM);
            delete sendOP;

            return false;
        }
    }

    return true;
}