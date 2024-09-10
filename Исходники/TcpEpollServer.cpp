BOOL CTcpEpollServer::EpollAcceptSocket(SOCKET hSocket, const sockaddr_in& SockAddr)
{
	if(INVALID_SOCKET == hSocket)
		return FALSE;

    // 设置程非阻塞式SOCKET
    if (!SetNonblock(hSocket, TRUE))
    {
        return FALSE;
    }

	// 回调上层创建context
	CTcpContext *pContext = CreateContext();
	if (pContext == NULL)
	{
		return FALSE;
	}

	// Context 赋值
	pContext->m_hSocket = hSocket;
	memcpy(&pContext->m_oSocketAddr, &SockAddr, sizeof(sockaddr_in));

	// 添加至队列
	AddTcpContext(pContext);

	struct epoll_event ev;
	ev.events	= EPOLLIN | EPOLLOUT | EPOLLET;  //ET模式+读事件+写事件
	ev.data.ptr = (void*)pContext;
	if (epoll_ctl(m_hEpollHandle, EPOLL_CTL_ADD, hSocket, &ev) < 0)
	{
		RemoveTcpContext(pContext);
		DestroyContext(pContext);
		return FALSE;
	}

	return TRUE;
}