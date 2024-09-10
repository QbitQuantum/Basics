int Socket::sendTo(const uint8_t *buf, int &len, 
        const struct sockaddr_un &addr, const int flags)
{
    if (-1 == m_fd) return EG_INVAL;

    return sendTo(buf, len, flags, (const struct sockaddr *)&addr,
            sizeof(addr));
}