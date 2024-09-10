void CTcpIocpServer::Destroy(void)
{
	// 销毁SOCKET套接字
	if(INVALID_SOCKET != m_hListenSocket)
	{
		DestroySocket(m_hListenSocket);
		m_hListenSocket = INVALID_SOCKET;
	}

	//关闭检查线程
	if(INVALID_HANDLE_VALUE != m_hAcceptEvent)
	{
		WSASetEvent(m_hAcceptEvent);
	}

	//等待Context删除完成
	while ((GetTcpContextCount() > 0 || GetAcceptExCount() > 0))
	{
		//关闭所有已连接SOCKET
		CloseAllContext();

		//关闭所有未连接SOCKET
		CloseAllAcceptExSocket();

		Sleep(5);
	}

	// 销毁完成端口句柄
	if(INVALID_HANDLE_VALUE != m_hIocp)
	{
		DestroyCompletePort(m_hIocp);
		m_hIocp = INVALID_HANDLE_VALUE;
	}

	// 销毁ACCEPT事件
	if(INVALID_HANDLE_VALUE != m_hAcceptEvent)
	{
		DestroyAcceptEvent(m_hAcceptEvent);
		m_hAcceptEvent = INVALID_HANDLE_VALUE;
	}

	// 等待线程退出
	m_CheckThread.WaitThreadExit();

	// 清空缓存
	m_OverloapCache.Clear();
}