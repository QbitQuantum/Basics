int udp_peer_send2(udp_peer_t* peer, const void *message, unsigned len, const struct sockaddr_in *peer_addr)
{
    WSABUF wsabuf;
    DWORD written;
    int ret;

    if (NULL == peer || NULL == message || 0 == len || 65535 < len || NULL == peer_addr)
    {
        log_error("udp_peer_send2: bad peer(%p) or bad message(%p) or bad len(%u) or bad peer_addr(%p)", 
            peer, message, len, peer_addr);
        return -1;
    }

    memset(&wsabuf, 0, sizeof(wsabuf));
    wsabuf.len = len;
    wsabuf.buf = (char*)message;

    ret = 0;
    written = 0;
    WSASendTo(peer->fd, &wsabuf, 1, &written, 0, (struct sockaddr*)peer_addr, sizeof(*peer_addr), NULL, NULL);
    if (written != len)
    {
        log_warn("udp_peer_send2: WSASendTo() failed, errno: %d", WSAGetLastError());
        ret = -1;
    }

    return ret;
}