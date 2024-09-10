void* EpollMonitor::WaitAcceptEvent( void *pData )
{
#ifndef WIN32
	epoll_event *events = new epoll_event[m_nMaxMonitor];	//epoll事件
	Socket sock;
	Socket sockClient;
	SOCKET hSock;
	/* 等待有事件发生 */
	while ( !m_bStop )
	{
		int nPollCount = epoll_wait(m_hEPollAccept, events, m_nMaxMonitor, -1 );
		if ( -1 == nPollCount ) break;
		/* 处理所有事件，nfds 为返回发生事件数 */
		int i = 0;
		for ( i = 0; i < nPollCount; i++ ) 
		{
			if ( m_epollExit == events[i].data.fd ) 
			{
				::closesocket(m_epollExit);
				break;
			}
			
			sock.Detach();
			sock.Attach(events[i].data.fd);
			while ( true )
			{
				sock.Accept( sockClient );
				if ( INVALID_SOCKET == sockClient.GetSocket() ) break;
				sockClient.SetSockMode();
				hSock = sockClient.Detach();
				AddMonitor(hSock);
				while ( !m_acceptEvents->Push((void*)hSock) ) m_sigWaitAcceptSpace.Wait();
				m_ioSignal.Notify();
			}
		}
	}
	delete[]events;
#endif
	return NULL;
}