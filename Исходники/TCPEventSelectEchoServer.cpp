DWORD WINAPI ThreadProc(
	__in  LPVOID lpParameter
	)
{
	int   ret, index;
	DWORD cbTransferred;
	WSANETWORKEVENTS NetworkEvents;
	char             szMessage[MSGSIZE];

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
				// szMessage contains the received data
				szMessage[ret] = '/0';

				//将接收到的消息返回
				int sendCount,currentPosition=0,count=ret;
				while( count>0 && (sendCount=send(g_CliSocketArr[index] , szMessage+currentPosition,count,0))!=SOCKET_ERROR)
				{
					count-=sendCount;
					currentPosition+=sendCount;
				}

				if (NetworkEvents.lNetworkEvents & FD_CLOSE)
				{
					Cleanup(index);
				}
			}
		}
	}

	return 0;
}