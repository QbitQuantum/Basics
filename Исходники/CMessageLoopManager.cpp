CStatus CMessageLoopManager::EnterMessageLoop(void * pContext)
{
	
	//允许传递给线程的参数是NULL型，表示不传递参数，所以不做检查

	//1、进入消息循环前，允许消息循环做一些初始化的工作
 	CStatus s1 = Initialize();
	if(!s1.IsSuccess())
		return s1;

	//在进入消息循环前，调用观察者的初始化函数
	CStatus s_initOfMsgObserver = m_pMsgObserver->Initialize(this,pContext);
	if(!s_initOfMsgObserver.IsSuccess())
		return s_initOfMsgObserver;

	//3、消息队列的拥有线程owner开始进入一个死循环（即消息循环机制）
	//owner 阻塞的一直从消息队列中读取other线程发给它的消息
	//然后根据自己手中的消息分发表，将消息派送给不同的消息处理类去
	//处理消息。
	//当任何其他线程向他发送一个退出消息后，owner结束处理消息的工作j
	while(true)
	{
		int failed_counter = 0;
		CMessage * pMsg = WaitForMessage();
		if(0 == pMsg)
		{
			//如果等待消息失败超过5次，就认为消息队列出问题
			//推出消息循环
			if(failed_counter++ < WaitForMessageFailedTimes)	
					continue;
			else
				return CStatus(-1,0,"in EnterMessageLoop of CMessageLoopManager : wait for message faild");
		}
		
		CStatus s2 = DispatchMessage(pMsg);
		if(!s2.IsSuccess())
			return s2;
		
		if(s2.m_ciReturnCode == QUIT_MESSAGE_LOOP)
			break;
	}	
	
	//5、允许消息队列做一些收尾工作
	CStatus s3 = Uninitialize();
	if(!s3.IsSuccess())
		return s3;

	return CStatus(0,0);
}