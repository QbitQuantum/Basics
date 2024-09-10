	//************************************************************
	//********功能：具体线程池类析构函数
	//********参数：
	//********返回值：
	//************************************************************
	CRealThreadPool::~CRealThreadPool()
	{
		if (m_hQuitEvent)
		{
			SetEvent(m_hQuitEvent);//退出检测线程
			CloseHandle(m_hQuitEvent);
		}
		CloseThreadPool();//关闭线程池
	}