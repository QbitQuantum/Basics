void EpollFrame::NewConnectMonitor()
{
#ifndef WIN32
	int nCount = MAXPOLLSIZE;
	epoll_event *events = new epoll_event[nCount];	//epoll事件
	int i = 0;
	Socket listenSock;
	Socket clientSock;

	while ( !m_stop )
	{
		nCount = MAXPOLLSIZE;
		if ( !((EpollMonitor*)m_pNetMonitor)->WaitConnect( events, nCount, -1 ) ) break; 

		for ( i = 0; i < nCount; i++ )
		{
			if ( ((EpollMonitor*)m_pNetMonitor)->IsStop(events[i].data.u64) ) 
			{
				delete[]events;
				return;
			}

			listenSock.Detach();
			listenSock.Attach((SOCKET)events[i].data.u64);
			while ( true )
			{
				listenSock.Accept( clientSock );
				if ( INVALID_SOCKET == clientSock.GetSocket() ) 
				{
					clientSock.Detach();
					break;
				}
				OnConnect(clientSock.Detach(), false);
			}
			if ( !m_pNetMonitor->AddAccept( listenSock.GetSocket() ) ) 
			{
				printf( "AddAccept (%d) error \n", listenSock.GetSocket() );
				listenSock.Close();
			}
		}
	}
	delete[]events;
#endif
}