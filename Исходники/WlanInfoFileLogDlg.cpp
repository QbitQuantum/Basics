// Ping test
BOOL PingTest(LPCWSTR strIpAddr, ICMP_ECHO_REPLY& reply)
{
    CString strIP       = strIpAddr;
    LPWSTR  addr        = strIP.GetBuffer(strIP.GetLength());
	CHAR    cIPString[128] = {'\0',};

    WideCharToMultiByte(CP_ACP, 0, addr, -1, cIPString, sizeof(cIPString), NULL, NULL);

    IPAddr		ipaddr;	 
	WSADATA		wsadata;
	HANDLE		hIcmp;

    BOOL        bResult = FALSE;

    if(strlen(cIPString))
	{
		// start winsock, requesting min version of 1.01
		WSAStartup(0x0101, &wsadata );
		
		//*******************************************************************
		// Now we ping the IP address resolved above
		//*******************************************************************
		
		// convert the IP char string to a IPAddr representation
		ipaddr = inet_addr((const char*)cIPString);
		
		if(ipaddr == INADDR_NONE)
		{
			AfxMessageBox(TEXT("Invalid Host or IP Entered"));
			WriteFileLog(1, _T("[PING] Invalid Host or IP Entered\r\n") );
		}
		else
		{
			INT		iPacketSize		= 0;
			
            // ping test을 위한 핸들 생성
			hIcmp = IcmpCreateFile();
			
			if(hIcmp == INVALID_HANDLE_VALUE)
			{
				AfxMessageBox(TEXT("Could not create ICMP handle"));
				WriteFileLog(1, _T("[PING] Could not create ICMP handle\r\n") );
			}
			else
			{
				LPVOID	lpData			= NULL;
				LPVOID	lpRevBuffer		= NULL;

				// determine the size of the data packet to send
				iPacketSize = 32;
				
				// allocate memory for the ping function call return and packet size
				lpData = LocalAlloc(LPTR, iPacketSize);
				lpRevBuffer = LocalAlloc(LPTR, sizeof(ICMP_ECHO_REPLY) * iPacketSize);
				
				if(lpData && lpRevBuffer)
				{
					// send the ping
					if( NULL == IcmpSendEcho( hIcmp,
                                              ipaddr,
                                              lpData,
                                              iPacketSize,
                                              NULL,
                                              lpRevBuffer,
                                              (sizeof(ICMP_ECHO_REPLY) * iPacketSize),
                                              1000))
					{					
                        // ping test 실패
                        bResult = FALSE;
						WriteFileLog(1, _T("[PING] IcmpSendEcho Failed(%d)\r\n"), GetLastError() );
					}
					else
					{
                        // ping test 성공
                        //&reply = (ICMP_ECHO_REPLY*)lpRevBuffer;
                        memcpy(&reply, lpRevBuffer, sizeof(ICMP_ECHO_REPLY));
                        bResult = TRUE;
					}
				}

				free(lpData);
				free(lpRevBuffer);
				IcmpCloseHandle(hIcmp);
			}					
		}
		WSACleanup();
	}
	else
	{
		WriteFileLog(1, _T("[PING] Invalid IP Address\r\n") );
	}

    return bResult;
}