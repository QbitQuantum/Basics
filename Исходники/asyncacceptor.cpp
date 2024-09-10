bool_t AsyncAcceptor::GetPeerInfomation(char_t *buffer, uint32_t size, AsyncSession *sess)
{
	bool_t ret = FALSE;

	#ifdef OS_WINDOWS
	sockaddr_in *local_addr		= 0;
	sockaddr_in *remote_addr	= 0;
	int32_t local_addr_len		= 0;
	int32_t remote_addr_len		= 0;

	GetAcceptExSockaddrs(buffer,
						0,
						sizeof(sockaddr_in) + 16,
						sizeof(sockaddr_in) + 16,
						(sockaddr **)&local_addr,
						&local_addr_len,
						(sockaddr **)&remote_addr,
						&remote_addr_len);

	Socket *sock = (Socket *)sess->Handle();
	if(!sock) { ECILA_TRACE(); return FALSE; }

	IPAddrs *ipaddr = sock->GetIpAddrs();
	if(!ipaddr) { ECILA_TRACE(); return FALSE; }

	ret = ipaddr->Init(remote_addr);
	if(!ret) { ECILA_TRACE(); return FALSE; }

	#endif


	return TRUE;
}