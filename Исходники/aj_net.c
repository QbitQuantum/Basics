static AJ_Status AJ_ARDP_UDP_Send(void* context, uint8_t* buf, size_t len, size_t* sent)
{
    AJ_Status status = AJ_OK;
    DWORD ret;
    NetContext* ctx = (NetContext*) context;
    WSAOVERLAPPED ov;
    DWORD flags = 0;
    WSABUF wsbuf;

    memset(&ov, 0, sizeof(ov));
    ov.hEvent = sendEvent;
    wsbuf.len = len;
    wsbuf.buf = buf;

    AJ_InfoPrintf(("AJ_ARDP_UDP_Send(buf=0x%p, len=%lu)\n", buf, len));

    ret = WSASend(ctx->udpSock, &wsbuf, 1, NULL, flags, &ov, NULL);
    if (ret == SOCKET_ERROR) {
        AJ_ErrPrintf(("AJ_ARDP_UDP_Send(): WSASend() failed. WSAGetLastError()=0x%x, status=AJ_ERR_WRITE\n", WSAGetLastError()));
        *sent = 0;
        return AJ_ERR_WRITE;
    }

    if (!WSAGetOverlappedResult(ctx->udpSock, &ov, sent, TRUE, &flags)) {
        AJ_ErrPrintf(("AJ_ARDP_UDP_Send(): WSAGetOverlappedResult() failed. WSAGetLastError()=0x%x, status=AJ_ERR_WRITE\n", WSAGetLastError()));
        return AJ_ERR_WRITE;
    }

    return status;
}