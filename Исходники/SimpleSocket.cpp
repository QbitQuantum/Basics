bool SimpleSocket::ConnectSocket() { //0 for success, 1 for error
	int iResult=SOCKET_ERROR;
	// try the next address returned by GetAddrInfoW if the connect call failed
	for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {
		iResult = connect( TheSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		/*ipv4*/
		sockaddr_in* tmp_addr=(sockaddr_in*)(ptr->ai_addr);
		unsigned char i1=(tmp_addr->sin_addr.S_un.S_un_b.s_b1);
		unsigned char i2=(tmp_addr->sin_addr.S_un.S_un_b.s_b2);
		unsigned char i3=(tmp_addr->sin_addr.S_un.S_un_b.s_b3);
		unsigned char i4=(tmp_addr->sin_addr.S_un.S_un_b.s_b4);
		wchar_t buffer[32]=L"";
		swprintf_s(buffer,32,L"%d.%d.%d.%d",i1,i2,i3,i4);
		ipv4=std::wstring(buffer);
		
		if (iResult == SOCKET_ERROR) { //ERROR
			closesocket(TheSocket);
			TheSocket = INVALID_SOCKET;
			iStatus=SOCKET_CLOSED;
		} else if (iResult == 0) { //OK
			break;
		}
	} 

	FreeAddrInfoW(result); // after success connection or tried all addrs in result, free "result"

	if (TheSocket == INVALID_SOCKET) {
		onSysMsg(L"Unable to connect to server!");
		WSACleanup();
		iStatus=SOCKET_CLOSED;
		return 1;
	}
	else {
		iStatus=SOCKET_CONNECTED;
		return 0;
	}

}