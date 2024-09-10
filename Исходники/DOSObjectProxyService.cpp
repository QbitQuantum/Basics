BOOL CDOSObjectProxyService::OnStart()
{
	FUNCTION_BEGIN;

	m_ThreadPerformanceCounter.Init(GetThreadHandle(),THREAD_CPU_COUNT_TIME);

	if(!m_ConnectionPool.Create(((CDOSServer *)GetServer())->GetConfig().MaxProxyConnection))
	{
		PrintDOSLog(0xff0000,_T("创建%u大小的连接池失败！"),
			((CDOSServer *)GetServer())->GetConfig().MaxProxyConnection);
		return FALSE;
	}
	if(!m_MsgQueue.Create(((CDOSServer *)GetServer())->GetConfig().MaxProxyMsgQueue))
	{
		PrintDOSLog(0xff0000,_T("创建%u大小的消息队列失败！"),
			((CDOSServer *)GetServer())->GetConfig().MaxProxyMsgQueue);
		return FALSE;
	}
	
	if(!m_MessageMap.Create(((CDOSServer *)GetServer())->GetConfig().MaxProxyGlobalMsgMap))
	{
		PrintDOSLog(0xff0000,_T("创建%u大小的消息映射表失败！"),
			((CDOSServer *)GetServer())->GetConfig().MaxProxyGlobalMsgMap);
		return FALSE;
	}

	if(((CDOSServer *)GetServer())->GetConfig().ProxyMsgMinCompressSize)
	{
		if (lzo_init() != LZO_E_OK)
		{
			PrintDOSLog(0xff0000,_T("代理服务开启消息压缩失败"));
			return FALSE;
		}
		PrintDOSDebugLog(0xff0000,_T("代理服务开启消息压缩"));
	}

	if(!Create(IPPROTO_TCP,
		DEFAULT_SERVER_ACCEPT_QUEUE,
		DEFAULT_SERVER_RECV_DATA_QUEUE,
		((CDOSServer *)GetServer())->GetConfig().ProxySendBufferSize,
		DEFAULT_PARALLEL_ACCEPT,
		DEFAULT_PARALLEL_RECV,
		false))
	{
		PrintDOSLog(0xffff,_T("代理服务创建失败！"));
		return FALSE;
	}

	if(!StartListen(((CDOSServer *)GetServer())->GetConfig().ObjectProxyServiceListenAddress))
	{
		PrintDOSLog(0xffff,_T("代理服务侦听于(%s:%u)失败！"),
			((CDOSServer *)GetServer())->GetConfig().ObjectProxyServiceListenAddress.GetIPString(),
			((CDOSServer *)GetServer())->GetConfig().ObjectProxyServiceListenAddress.GetPort());
		return FALSE;
	}
	PrintDOSLog(0xffff,_T("代理服务侦听于(%s:%u)！"),
		((CDOSServer *)GetServer())->GetConfig().ObjectProxyServiceListenAddress.GetIPString(),
		((CDOSServer *)GetServer())->GetConfig().ObjectProxyServiceListenAddress.GetPort());

	PrintDOSLog(0xff0000,_T("对象代理线程[%u]已启动"),GetThreadID());
	return TRUE;
	FUNCTION_END;
	return FALSE;
}