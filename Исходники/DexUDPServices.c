unsigned int DexUDPSendPacket( DexUDP *dex_udp_parameters, const char data[DEX_UDP_PACKET_SIZE] )
{
	
	DWORD	  dwBytesSent = 0;
	DWORD     dwFlags = 0;
	WSABUF    wbSend;
	
	int       status;
	
	static    count = 0;
	
	wbSend.buf = (char *) data;	
	wbSend.len = DEX_UDP_PACKET_SIZE;
	
	// Send packet to the local host no matter what.
	status = WSASendTo( dex_udp_parameters->socket, 
		&wbSend, 1, 
		&dwBytesSent, 
		dwFlags, 
		(SOCKADDR*) &localXmitAddr, 
		LocalAddrSize,
		NULL, NULL);
	
	// Broadcast to the net only if a valid broadcast address was already set.
	if ( dex_udp_parameters->sockaddr.sin_addr.s_addr ) {
		status = WSASendTo( dex_udp_parameters->socket, 
			&wbSend, 1, 
			&dwBytesSent, 
			dwFlags, 
			(SOCKADDR*) &dex_udp_parameters->sockaddr, 
			sizeof( dex_udp_parameters->sockaddr ),
			NULL, NULL);
	}
	
	if ( status ) {
		status = WSAGetLastError();
		dwBytesSent = 0;
	}
	
	return( dwBytesSent );
	
}