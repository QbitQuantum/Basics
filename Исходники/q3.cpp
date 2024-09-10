DWORD Q3_ConnectToMasterServer(GAME_INFO *pGI, int iMasterIdx)
{
	size_t packetlen=0;
	char sendbuf[80];
	ZeroMemory(sendbuf,sizeof(sendbuf));
	SOCKET ConnectSocket;

//	UINT_PTR timerProgressWait = SetTimer(g_hWnd,IDT_TIMER_1SECOND,100,NULL);
	
	int i = 0;
	unsigned char *packet[MAX_PACKETS];
	size_t packet_len[MAX_PACKETS];

	for(i=0; i<MAX_PACKETS;i++)
		packet[i] = NULL;

	i = 0;

	char szIP[260];
	strcpy(szIP,pGI->szMasterServerIP[iMasterIdx]);
	
	SplitIPandPORT(szIP,pGI->dwMasterServerPORT);

	int len = 0;//(int)strlen(sendbuf);
	string query;
	query = pGI->szMasterQueryString;
	ReplaceStrInStr(query,"%PROTOCOL%",pGI->szGameProtocol[iMasterIdx]);
	len = UTILZ_ConvertEscapeCodes((TCHAR*)query.c_str(),sendbuf,sizeof(sendbuf));

	ConnectSocket = getsockudp(szIP,(unsigned short)pGI->dwMasterServerPORT); // etmaster.idsoftware.com"27950 master server
	if(INVALID_SOCKET==ConnectSocket)
	{

		KillTimer(g_hWnd,IDT_1SECOND);
		g_log.AddLogInfo(GS_LOG_ERROR,"Error connecting to server %s:%d!",szIP,pGI->dwMasterServerPORT);
		return 1;
	}

	WSAEVENT hEvent;
	hEvent = WSACreateEvent();
	if (hEvent == WSA_INVALID_EVENT)
	{
		KillTimer(g_hWnd,IDT_1SECOND);
		g_log.AddLogInfo(GS_LOG_ERROR,"WSACreateEvent() = WSA_INVALID_EVENT");
		closesocket(ConnectSocket);
		return 1;
	}

	//
	// Make the socket non-blocking and 
	// associate it with network events
	//
	int nRet;
	nRet = WSAEventSelect(ConnectSocket, hEvent,FD_READ|FD_CONNECT|FD_CLOSE);
	if (nRet == SOCKET_ERROR)
	{
		KillTimer(g_hWnd,IDT_1SECOND);
		g_log.AddLogInfo(GS_LOG_ERROR,"EventSelect() = SOCKET_ERROR");
		closesocket(ConnectSocket);
		WSACloseEvent(hEvent);
		return 5;
	}



	//
	// Handle async network events
	//

	WSANETWORKEVENTS events;
	while(1)
	{
		//
		// Wait for something to happen
		//
		//dbg_print("\nWaitForMultipleEvents()");
		DWORD dwRet;
		dwRet = WSAWaitForMultipleEvents(1, &hEvent, FALSE,4000,FALSE);
		if (dwRet == WSA_WAIT_TIMEOUT)
		{
			g_log.AddLogInfo(GS_LOG_ERROR,"WSAWaitForMultipleEvents = WSA_WAIT_TIMEOUT");
			break;
		}

		//
		// Figure out what happened
		//
		//g_log.AddLogInfo(0,"\nWSAEnumNetworkEvents()");
		nRet = WSAEnumNetworkEvents(ConnectSocket, hEvent, &events);
		if (nRet == SOCKET_ERROR)
		{
			g_log.AddLogInfo(GS_LOG_ERROR,"WSAEnumNetworkEvents() = SOCKET_ERROR");
			break;
		}

		//				 //
		// Handle events //
		//				 //

		// Connect event?
		if (events.lNetworkEvents & FD_CONNECT)
		{
			//g_log.AddLogInfo(0,"\nFD_CONNECT: %d", events.iErrorCode[FD_CONNECT_BIT]);
			g_log.AddLogInfo(0,"Master server %s",pGI->szMasterServerIP[0]);
			g_log.AddLogInfo(0,"Sending packet string: [%s]  Length: %d",sendbuf,len);
			g_log.AddLogInfo(0,"xml config: %s ",pGI->szMasterQueryString);

			if(send(ConnectSocket, sendbuf, len , 0)==SOCKET_ERROR) 
			{
				KillTimer(g_hWnd,IDT_1SECOND);
				WSACloseEvent(hEvent);
				closesocket(ConnectSocket);		
				g_log.AddLogInfo(GS_LOG_ERROR,"Error sending master query packet!");
				return 2;
			}
		}

		// Read event?
		if (events.lNetworkEvents & FD_READ)
		{
			//g_log.AddLogInfo(0,"\nFD_READ: %d, %d",events.iErrorCode[FD_READ_BIT],i);
			// Read the data and write it to stdout
			packet[i]=(unsigned char*)ReadPacket(ConnectSocket, &packetlen);
			packet_len[i] = packetlen;
			i++;

			if(i>=MAX_PACKETS)
				break;
	
		}

		// Close event?
		if (events.lNetworkEvents & FD_CLOSE)
		{
			g_log.AddLogInfo(0,"\nFD_CLOSE: %d",events.iErrorCode[FD_CLOSE_BIT]);
			break;
		}
/*
		// Write event?
		if (events.lNetworkEvents & FD_WRITE)
		{
			g_log.AddLogInfo(0,"\nFD_WRITE: %d",events.iErrorCode[FD_WRITE_BIT]);
		}
*/
	}
	
	closesocket(ConnectSocket);
	WSACloseEvent(hEvent);

	DWORD Q3_dwNewTotalServers=0;
	for(i=0; i<MAX_PACKETS;i++)
	{
		if(packet[i] != NULL)
		{
		    Q3_dwNewTotalServers += Q3_ParseServers((char*)packet[i],packet_len[i],pGI);
			free(packet[i]);			
			packet[i]=NULL;
			SetStatusText(pGI->iIconIndex,g_lang.GetString("StatusReceivingMaster"),Q3_dwNewTotalServers,pGI->szGAME_NAME);
			if(g_bCancel)
			{
				//ensure to clean up
				for(i=0; i<MAX_PACKETS;i++)
				{
					if(packet[i] != NULL)
					{
						free(packet[i]);			
						packet[i]=NULL;
					}
				}			
				break;
			}
			Sleep(50); //give cpu sometime to breath
		}
	}

//	KillTimer(g_hWnd,IDT_TIMER_1SECOND);
	pGI->dwTotalServers += Q3_dwNewTotalServers;


	return 0;
}