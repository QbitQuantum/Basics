/**
 * Return true if this SocketAddress is IPv4 or IPv6
 */
bool SocketAddress::isIp() const
{
    const ::addrinfo& ai = getAddrInfo(*this);
    return ai.ai_family == AF_INET || ai.ai_family == AF_INET6;
}