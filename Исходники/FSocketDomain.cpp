int FSocketDomain::getAddrInfo(const char *addr, const in_port_t port, struct addrinfo **res)
{
	return getAddrInfo(this->m_socketDomain, this->m_socketType, addr, port, res);
}