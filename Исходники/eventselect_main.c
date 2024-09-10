DWORD WINAPI WorkerThread(LPVOID lpParam)  
{  
	int ret, index;  
	WSANETWORKEVENTS NetworkEvents;  
	char szMessage[MSGSIZE];  
	while (TRUE)  
	{  
		ret = WSAWaitForMultipleEvents(g_iTotalConn, g_CliEventArr, FALSE, 1000, FALSE);  
		if (ret == WSA_WAIT_FAILED || ret == WSA_WAIT_TIMEOUT)  
		{  
			continue;  
		}  
		index = ret - WSA_WAIT_EVENT_0;  
		WSAEnumNetworkEvents(g_CliSocketArr[index], g_CliEventArr[index], &NetworkEvents);  
		if (NetworkEvents.lNetworkEvents & FD_READ)  
		{  
			// Receive message from client  
			ret = recv(g_CliSocketArr[index], szMessage, MSGSIZE, 0);  
			if (ret == 0 || (ret == SOCKET_ERROR && WSAGetLastError() == WSAECONNRESET))  
			{  
				Cleanup(index);  
			}  
			else  
			{  
				szMessage[ret] = '\0';  
				send(g_CliSocketArr[index], szMessage, strlen(szMessage), 0);  
			}  
		}  
		if (NetworkEvents.lNetworkEvents & FD_CLOSE)  
		{  
			Cleanup(index);  
		}  
	}  
	return 0;  
}  