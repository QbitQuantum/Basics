DWORD DarunGrim::IDACommandProcessor()
{
	SOCKET SocketArray[WSA_MAXIMUM_WAIT_EVENTS];
	WSAEVENT EventArray[WSA_MAXIMUM_WAIT_EVENTS];
	WSANETWORKEVENTS NetworkEvents;
	DWORD EventTotal = 0, index;

	SocketArray[0] = pSourceController->GetSocket();
	SocketArray[1] = pTargetController->GetSocket();
	for (int i = 0; i<2; i++)
	{
		WSAEVENT NewEvent = WSACreateEvent();
		WSAEventSelect(SocketArray[i], NewEvent, FD_READ | FD_CLOSE);
		EventArray[EventTotal] = NewEvent;
		EventTotal++;
	}
	while (1)
	{
		index = WSAWaitForMultipleEvents(EventTotal,
			EventArray,
			FALSE,
			WSA_INFINITE,
			FALSE);

		if (index<0)
			break;

		index = index - WSA_WAIT_EVENT_0;
		//-------------------------
		// Iterate through all events and enumerate
		// if the wait does not fail.
		for (DWORD i = index; i<EventTotal; i++)
		{
			if (SocketArray[i] == WSA_INVALID_HANDLE)
				continue;

			index = WSAWaitForMultipleEvents(1,
				&EventArray[i],
				TRUE,
				1000,
				FALSE);
			if ((index != WSA_WAIT_FAILED) && (index != WSA_WAIT_TIMEOUT))
			{
				if (WSAEnumNetworkEvents(SocketArray[i], EventArray[i], &NetworkEvents) == 0)
				{
					Logger.Log(10, "Signal( %d - %d )\n", i, NetworkEvents.lNetworkEvents);
					if (NetworkEvents.lNetworkEvents == FD_READ)
					{
						char buffer[DATA_BUFSIZE] = { 0, };
						WSABUF DataBuf;
						DataBuf.len = DATA_BUFSIZE;
						DataBuf.buf = buffer;
						/*
						DWORD RecvBytes;
						DWORD Flags=0;
						if ( WSARecv( SocketArray[i], &DataBuf, 1, &RecvBytes, &Flags, NULL, NULL )==SOCKET_ERROR )
						{
						Logger.Log( 10, "Error occurred at WSARecv()\n" );
						}else
						{
						Logger.Log( 10, "Read %d bytes\n", RecvBytes );
						}*/
						char type;
						DWORD length;
						PBYTE data = RecvTLVData(SocketArray[i], &type, &length);
						if (data)
						{
							Logger.Log(10, "%s: Type: %d Length: %d data:%x\n", __FUNCTION__, type, length, data);
							if (type == SHOW_MATCH_ADDR && length >= 4)
							{
								DWORD address = *(DWORD *)data;
								Logger.Log(10, "%s: Showing address=%x\n", __FUNCTION__, address);
								//Get Matching Address

								DWORD MatchingAddress = 0;
								if (pDiffMachine)
								{
									MatchingAddress = pDiffMachine->GetMatchAddr(i, address);
								}
								if (MatchingAddress != 0)
								{
									//Show using JUMP_TO_ADDR
									if (i == 0)
									{
										pTargetController->ShowAddress(MatchingAddress);
									}
									else
									{
										pSourceController->ShowAddress(MatchingAddress);
									}
								}
							}
						}
					}
					else if (NetworkEvents.lNetworkEvents == FD_CLOSE)
					{
						closesocket(SocketArray[i]);
						WSACloseEvent(EventArray[i]);
						memcpy(SocketArray + i, SocketArray + i + 1, EventTotal - i + 1);
						memcpy(EventArray + i, EventArray + i + 1, EventTotal - i + 1);
						EventTotal--;
						break;
					}
				}
			}
		}
	}
	return 1;
}