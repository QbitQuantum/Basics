VOID CALLBACK workerIoThreadProc(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PVOID Overlapped, ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO Io) {
	ods("workerIoThreadProc start\n");
	BOOL success;
	LPOVERLAPPED_ACCEPT ola=(LPOVERLAPPED_ACCEPT)Overlapped;
	if(OAS_RECV==ola->oas){
		ods("OAS_RECV\n");
		DWORD numWritten=0;
		SecureZeroMemory(Overlapped, sizeof(OVERLAPPED));
		DWORD sizeofSend=sizeof(status200HelloWorld)-1;
		CopyMemory(ola->acceptBuf, status200HelloWorld, sizeofSend);
		ola->oas=OAS_SEND;
		StartThreadpoolIo(Io);
		success=WriteFile((HANDLE)ola->s, ola->acceptBuf, sizeofSend, &numWritten, &ola->overlapped);
		if(!success && GetLastError()!=ERROR_IO_PENDING){
			int wsaError=WSAGetLastError();
			DebugBreak();
		}
	}else if(OAS_SEND==ola->oas){
		ods("OAS_SEND\n");
		SecureZeroMemory(Overlapped, sizeof(OVERLAPPED));
		ola->oas=OAS_CLOSE;
		StartThreadpoolIo(Io);
		success=DisconnectEx(ola->s, &ola->overlapped, TF_REUSE_SOCKET, 0);
		if(!success && GetLastError()!=ERROR_IO_PENDING){
			int wsaError=WSAGetLastError();
			DebugBreak();
		}
	}else if(OAS_CLOSE==ola->oas){
		ods("OAS_CLOSE\n");
		DWORD acceptBufSize=max(0, ola->bufSize-sizeof(sockaddr_in)-16-sizeof(sockaddr_in)-16);
		acceptBufSize=0;
		StartThreadpoolIo(pListen);
		success=AcceptEx(sListen, ola->s, ola->acceptBuf, acceptBufSize, sizeof(sockaddr_in)+16, sizeof(sockaddr_in)+16, 0, &ola->overlapped);
		if(!success && WSAGetLastError()!=ERROR_IO_PENDING){
			DebugBreak();
		}
	}else{
		DebugBreak();
	}
	ods("workerIoThreadProc return\n");
}