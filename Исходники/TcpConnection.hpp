void TcpConnection::init_addr(){

	if( !this->connected_)
		return;

	if( local_addr == NULL ){
		struct sockaddr_in local_sockaddr;
		int addrlen = sizeof(struct sockaddr_storage);

		getsockname(socket_, (struct sockaddr*)&local_sockaddr, &addrlen);

		DWORD len = addrlen;
		//local_addr = inet_ntoa(local_sockaddr.sin_addr);
		local_addr = new char[22];
		if( WSAAddressToStringA((LPSOCKADDR)&local_sockaddr, addrlen, NULL, local_addr, &len) != 0){
			printf("WSAAddressToString() failed with error code %ld\n", WSAGetLastError());
		}
	}

	if( remote_addr == NULL ){
		struct sockaddr_in remote_sockaddr;
		int addrlen = sizeof(struct sockaddr_storage);

		getpeername(socket_, (struct sockaddr*)&remote_sockaddr, &addrlen);

		DWORD len = addrlen;
		//remote_addr =  inet_ntoa(remote_sockaddr.sin_addr);
		remote_addr = new char[22];
		if( WSAAddressToStringA((LPSOCKADDR)&remote_sockaddr, addrlen, NULL, remote_addr, &len) != 0){
			printf("WSAAddressToString() failed with error code %ld\n", WSAGetLastError());
		}
	}
}