bool STNetEngine::LinuxIO( int timeout )
{
#ifndef WIN32
	int nCount = 0;
	int eventType = 0;
	int i = 0;
	Socket sockListen;
	Socket sockClient;
	SOCKET sock;
	map<SOCKET,int>::iterator it;
	pair<map<SOCKET,int>::iterator,bool> ret;
	
	//没有可io的socket则等待新可io的socket
	//否则检查是否有新的可io的socket，有则取出加入到m_ioList中，没有也不等待
	//继续进行m_ioList中的socket进行io操作
	if ( 0 >= m_ioList.size() ) nCount = m_pNetMonitor->WaitEvent( timeout );
	else nCount = m_pNetMonitor->WaitEvent( 0 );
	if ( 0 > nCount ) return false;
	//加入到m_ioList中
	for ( i = 0; i < nCount; i++ )
	{
		sock = m_pNetMonitor->GetSocket(i);
		if ( INVALID_SOCKET == sock ) return false;//STEpoll已关闭
		if ( m_pNetMonitor->IsAcceptAble(i) )//连接类型直接执行业务 
		{
			while ( true )
			{
				sockListen.Detach();
				sockListen.Attach(sock);
				sockListen.Accept( sockClient );
				if ( INVALID_SOCKET == sockClient.GetSocket() ) break;
				sockClient.SetSockMode();
				OnConnect(sockClient.Detach(), false);
			}
			continue;
		}
		//不是监听socket一定是io事件
		//加入到io列表，统一调度
		if ( m_pNetMonitor->IsWriteAble(i) ) eventType = 1|2;//recv+send事件
		else eventType = 1;//recv事件
		ret = m_ioList.insert(map<SOCKET,int>::value_type(sock,eventType) );//增加可io的对象
		if ( !ret.second ) ret.first->second = ret.first->second|eventType;//设置新事件
	}
	//遍历m_ioList，执行1次io
	for ( it = m_ioList.begin(); it != m_ioList.end(); it++ )
	{
		if ( 1&it->second ) //可读
		{
			if ( ok != OnData( it->first, 0, 0 ) ) //数据已读完或连接已断开
			{
				it->second = it->second&~1;//清除事件
			}
		}
		if ( 2&it->second ) //可写
		{
			if ( ok != OnSend( it->first, 0 ) )//数据已经发送完，或socket已经断开，或socket不可写
			{
				it->second = it->second&~2;//清除事件
			}
		}
	}
	
	//将不可io的socket清除
	it = m_ioList.begin();
	while (  it != m_ioList.end() ) 
	{
		if ( 0 == it->second ) 
		{
			m_ioList.erase(it);
			it = m_ioList.begin();
			continue;
		}
		it++;
	}
	return true;
#endif
	return false;
}