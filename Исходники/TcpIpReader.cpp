DWORD TcpIpReader::startServer() {
	breakSocket=false;

	wchar_t log[300];
	while (true) {
		//__try {
			fd_set readfds;

			FD_ZERO(&readfds);
			// Set server socket to set
			FD_SET(socket, &readfds);

			// Timeout parameter
			timeval tv = { 0 };
			tv.tv_sec = 5;

			while(true) {
				if (breakSocket)
					return 0;
				FD_SET(socket, &readfds);
				int ret = select(0, &readfds, NULL, NULL, &tv);
				if (ret > 0)
					break;
				if (ret<0) {
					wchar_t log[100];
					DWORD err=WSAGetLastError();
					swprintf(log,L"[BixVReader]wsa err:%x",err);
					OutputDebugString(log);
					if (err==0x2736) {
						socket=WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,NULL,0,0);
						sockaddr_in Service;
						Service.sin_family = AF_INET;
						Service.sin_addr.s_addr = inet_addr("127.0.0.1");
						Service.sin_port = htons((u_short)(port));
						bind(socket, (SOCKADDR *) &Service, sizeof (Service));
						listen(socket, 1);

						FD_ZERO(&readfds);
						// Set server socket to set
						FD_SET(socket, &readfds);
					}
				}
			}

			SOCKET AcceptEventSocket;

			AcceptSocket = accept(socket, NULL, NULL);
			closesocket(socket);
			socket=NULL;
			if (AcceptSocket == INVALID_SOCKET)
				return 0;

			swprintf(log,L"[BixVReader]Socket connected:%i",AcceptSocket);
			OutputDebugString(log);

			FD_ZERO(&readfds);
			// Set server socket to set
			FD_SET(eventsocket, &readfds);

			while(true) {
				if (breakSocket)
					return 0;
				FD_SET(eventsocket, &readfds);
				int ret = select(0, &readfds, NULL, NULL, &tv);
				if (ret > 0)
					break;
				if (ret<0) {
					DWORD err=WSAGetLastError();
					swprintf(log,L"[BixVReader]wsa err:%x",err);
					OutputDebugString(log);
					if (err==0x2736) {
						eventsocket=WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,NULL,0,0);
						sockaddr_in eventService;
						eventService.sin_family = AF_INET;
						eventService.sin_addr.s_addr = inet_addr("127.0.0.1");
						eventService.sin_port = htons((u_short)(eventPort));
						bind(eventsocket, (SOCKADDR *) &eventService, sizeof (eventService));
						listen(eventsocket, 1);

						FD_ZERO(&readfds);
						// Set server socket to set
						FD_SET(eventsocket, &readfds);
					}
				}
			}

			AcceptEventSocket = accept(eventsocket, NULL, NULL);
			closesocket(eventsocket);
			eventsocket=NULL;
			if (AcceptEventSocket == INVALID_SOCKET)
				return 0;

			swprintf(log,L"[BixVReader]Event Socket connected:%i",AcceptEventSocket);
			OutputDebugString(log);

			if (waitInsertIpr!=NULL) {
				// if I'm waiting for card insertion, verify if there's a card present
				if (initProtocols()) {
					SectionLocker lock(device->m_RequestLock);
					if (waitInsertIpr->UnmarkCancelable()==S_OK)
						waitInsertIpr->CompleteWithInformation(STATUS_SUCCESS, 0);
					waitInsertIpr=NULL;
					state=SCARD_SWALLOWED;
				}
			}
			
			while (true) {
				// wait for a command
				DWORD command=0;
				int read=0;
				if ((read=recv(AcceptEventSocket,(char*)&command,sizeof(DWORD),MSG_WAITALL))<=0) {
					state=SCARD_ABSENT;
					OutputDebugString(L"[BixVReader]Socket error");
					powered=0;
					::shutdown(AcceptSocket,SD_BOTH);
					::shutdown(AcceptEventSocket,SD_BOTH);
					if (waitRemoveIpr!=NULL) {// card inserted
						OutputDebugString(L"[BixVReader]complete Wait Remove");
						SectionLocker lock(device->m_RequestLock);
						if (waitRemoveIpr->UnmarkCancelable()==S_OK) {
							OutputDebugString(L"[BixVReader]Wait Remove Unmarked");
							waitRemoveIpr->CompleteWithInformation(STATUS_SUCCESS, 0);
							OutputDebugString(L"[BixVReader]Wait Remove Completed");
						}
						waitRemoveIpr=NULL;
					}
					if (waitInsertIpr!=NULL) {// card removed
						OutputDebugString(L"[BixVReader]cancel Wait Remove");
						SectionLocker lock(device->m_RequestLock);
						if (waitInsertIpr->UnmarkCancelable()==S_OK) {
							OutputDebugString(L"[BixVReader]Wait Insert Unmarked");
							waitInsertIpr->CompleteWithInformation(HRESULT_FROM_WIN32(ERROR_CANCELLED), 0);
							OutputDebugString(L"[BixVReader]Wait Insert Cancelled");
						}
						waitInsertIpr=NULL;
					}
					break;
				}
				OutputDebugString(L"[BixVReader]Socket data");
				if (command==0)
					powered=0;
				if (command==0 && waitRemoveIpr!=NULL) {// card removed
					SectionLocker lock(device->m_RequestLock);
					state=SCARD_ABSENT;
					if (waitRemoveIpr->UnmarkCancelable()==S_OK)						
						waitRemoveIpr->CompleteWithInformation(STATUS_SUCCESS, 0);
					waitRemoveIpr=NULL;
				}
				else if (command==1 && waitInsertIpr!=NULL) {// card inserted
					SectionLocker lock(device->m_RequestLock);
					state=SCARD_SWALLOWED;
					initProtocols();					
					if (waitInsertIpr->UnmarkCancelable()==S_OK)
						waitInsertIpr->CompleteWithInformation(STATUS_SUCCESS, 0);
					waitInsertIpr=NULL;
				}
			}
		//}
		//__except(EXCEPTION_EXECUTE_HANDLER) {
		//	wchar_t log[300];
		//	DWORD err=GetExceptionCode();
		//	swprintf(log,L"Exception:%08X",err);
		//	OutputDebugString(log);
		//}
	}
	OutputDebugString(L"[BixVReader]Socket quit!!!");
	return 0;
}