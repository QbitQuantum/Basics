BOOL CProtocolBridge::IsLocalCall(IHttpContext* ctx)
{
	PSOCKADDR src = ctx->GetRequest()->GetRemoteAddress();
	PSOCKADDR dest = ctx->GetRequest()->GetLocalAddress();

	if (AF_INET == src->sa_family && AF_INET == dest->sa_family)
	{
        DWORD srcAddress = ntohl(((PSOCKADDR_IN)src)->sin_addr.s_addr);
		DWORD destAddress = ntohl(((PSOCKADDR_IN)dest)->sin_addr.s_addr);

		return srcAddress == destAddress || LOCAL127 == srcAddress || LOCAL127 == destAddress;
	}
	else if (AF_INET6 == src->sa_family && AF_INET6 == dest->sa_family)
	{
        IN6_ADDR* srcAddress = &((PSOCKADDR_IN6)src)->sin6_addr;
		IN6_ADDR* destAddress = &((PSOCKADDR_IN6)dest)->sin6_addr;

		if (0 == memcmp(srcAddress, destAddress, sizeof IN6_ADDR))
		{
			return TRUE;
		}

		if (IN6_IS_ADDR_LOOPBACK(srcAddress) || IN6_IS_ADDR_LOOPBACK(destAddress))
		{
			return TRUE;
		}
	}

	return FALSE;
}