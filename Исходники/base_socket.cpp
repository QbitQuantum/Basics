int32_t CBaseSocket::get_local_addr(Inet_Addr &local_addr) const
{
#ifdef WIN32
	int32_t len = sizeof(sockaddr_in);
#else
	uint32_t len = sizeof(sockaddr_in);
#endif

	  sockaddr *addr = reinterpret_cast<sockaddr *> (local_addr.get_addr());
	if(::getsockname(get_handler(), addr, &len) == -1)
		return -1;

	return 0;
}