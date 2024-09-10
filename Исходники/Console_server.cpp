int main(int argc, char* argv[])
{
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("윈도우 소켓 초기화 실패! \n");
		return -1;
	}

	// (socket + bind + listen)
	if(!CreateListenSocket())
	{
		printf("대기 소켓 생성 실패\n");
		return -1;
	}

	// 서버처리
	//===================================================
	int index = 0;
	WSANETWORKEVENTS neEvents;
	
	while(1)
	{
		// 이벤트 시그널 감지
		index = WSAWaitForMultipleEvents(g_SockCnt, EventList,
			FALSE, WSA_INFINITE, FALSE);
		index -= WSA_WAIT_EVENT_0;
		// 이벤트 내용 가져오기 + EventList[index] 이벤트를 넌시그날로 변경
		WSAEnumNetworkEvents( SockList[index], EventList[index], &neEvents);
		if(neEvents.lNetworkEvents & FD_ACCEPT)
		{
			EVENTERRORCHECK(neEvents, FD_ACCEPT_BIT);
			if(AddClient(index) != true)
				continue;
		}
		else if(neEvents.lNetworkEvents & FD_READ || neEvents.lNetworkEvents & FD_WRITE)
		{
			if(neEvents.iErrorCode[FD_READ_BIT] != 0 && neEvents.iErrorCode[FD_WRITE_BIT] != 0)
			{
				DisplayMessage();
				return -1;
			}
			RecvClient(index);
			
		}
		else if(neEvents.lNetworkEvents & FD_CLOSE)
		{
			EVENTERRORCHECK(neEvents, FD_CLOSE_BIT);
				DeleteClient(index);
		}
	}
	//===================================================

	WSACleanup();
	return 0;
}