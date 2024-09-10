ProtocolEvent ProtocolUDP::sendData(const void *buffer, size_t len, const int flags, size_t *bytes)
{
        char buf[SOCKADDR_SIZE];
        struct sockaddr *sa = (struct sockaddr *)buf;		
	socklen_t addrlen;
	SocketAddress *addr = NULL;
	ssize_t ret;
	
	if (!buffer) {
		HAGGLE_DBG("%s Send buffer is NULL\n", getName());
		return PROT_EVENT_ERROR;
	}
	
	if (!peerIface) {
		HAGGLE_DBG("%s Send interface invalid\n", getName());
		*bytes = 0;
		return PROT_EVENT_ERROR;
	}
	
#if defined(ENABLE_IPv6)
	addr = peerIface->getAddress<IPv6Address>();
#endif

	if (!addr)
		addr = peerIface->getAddress<IPv4Address>();
	
	if (!addr) {
		HAGGLE_DBG("%s Send interface has no valid address\n", getName());
		*bytes = 0;
		return PROT_EVENT_ERROR;
	}
	
	if (addr->getTransport()->getType() != Transport::TYPE_UDP) {
		HAGGLE_DBG("%s Send interface [%s] has no valid UDP port\n", getName(),
			   peerIface->getIdentifierStr());
		*bytes = 0;
		return PROT_EVENT_ERROR;
	}
	
	addrlen = addr->fillInSockaddr(sa);
	
	HAGGLE_DBG("%s sending to address %s:%d\n", 
		   getName(), addr->getURI(), 
		   reinterpret_cast<const TransportUDP *>(addr->getTransport())->getPort());
	
	ret = sendTo(buffer, len, flags, sa, addrlen);

	if (ret < 0)
		return PROT_EVENT_ERROR;
	else if (ret == 0)
		return PROT_EVENT_PEER_CLOSED;

	*bytes = ret;

	return PROT_EVENT_SUCCESS;	
}