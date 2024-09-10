int inet_pton( int af, const char *src, void *dst )
{
	/* IPv6 is largest buffer, so use it for both */
	struct	sockaddr_in6	dst_sockaddr;
	struct	sockaddr_in6	*pDst_sockaddr;
	int		dst_size;
	int		result;
	DWORD	error;

	pDst_sockaddr = &dst_sockaddr;

	switch( af )
	{
	case AF_INET:
		dst_size = sizeof( struct sockaddr_in );
		break;
	case AF_INET6:
		dst_size = sizeof( struct sockaddr_in6 );
		break;
	default:
		return 0;
	}

	result = WSAStringToAddressA( src, af, NULL, 
		(LPSOCKADDR)pDst_sockaddr, &dst_size );

	if ( result != 0 )
	{
		error = GetLastError();
		return error;
		return 0;
	}

	switch( af )
	{
	case AF_INET:
		memcpy( dst, &((struct sockaddr_in*)pDst_sockaddr)->sin_addr, 
			sizeof( struct in_addr ) );
		break;
	case AF_INET6:
		memcpy( dst, &pDst_sockaddr->sin6_addr, 
			sizeof( struct in6_addr ) );
		break;
	}

	return 1;
}