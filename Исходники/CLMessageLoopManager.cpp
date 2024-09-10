CLStatus CLMessageLoopManager::EnterMessageLoop(void *pContext)
{
	SLExecutiveInitialParameter *para = (SLExecutiveInitialParameter *)pContext;
	CLStatus s = Initialize();//队列（管道，网络等对象）等的初始化工作
	if(!s.IsSuccess())
	{
		throw "In CLMessageLoopManager::EnterMessageLoop(), Initialize() error.";
		para->pNotifier->NotifyInitialFinished(false);
		return CLStatus(-1,0);
	}
	CLStatus s1 = m_pMessageOberver->Initialize(this,para->pContext);//初始化CLMessageOberver对象,如注册不同消息的处理方法
	if(!s1.IsSuccess())
	{
		throw "In CLMessageLoopManager::EnterMessageLoop(), m_pMessageOberver->Initialize error.";
		para->pNotifier->NotifyInitialFinished(false);
		return CLStatus(-1,0);
	}
	para->pNotifier->NotifyInitialFinished(true);

	while(true)
	{
		CLMessage *pMsg = WaitForMessage();
		CLStatus s3 = DispatchMessage(pMsg);
		if(s3.m_clReturnCode == QUIT_MESSAGE_LOOP)  //注意此退出返回码要与QUIT_MESSAGE_LOOP保持一致
			break;
		delete pMsg;
	}
	delete m_pMessageOberver; //所有消息处理完毕，删除消息处理方法CLMessageOberver对象
	m_pMessageOberver = 0;  //这里加入了赋值语句，使得m_pMessageOberver = 0，因为在本类的析构中还释放了一次，造成segmentation fault
	CLStatus s4 = Uninitialize();//反初始化队列（管道，网络等对象）等
	return CLStatus(0,0);
}