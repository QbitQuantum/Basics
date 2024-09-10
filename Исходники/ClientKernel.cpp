//内核配置
bool __cdecl CClientKernel::InitClientKernel(LPCTSTR lpszComLine, IUnknownEx * pIUnknownEx)
{
	//效验参数
	ASSERT(lpszComLine!=NULL);
	if (lpszComLine==NULL) return false;

	//创建窗口
	if (m_hWnd==NULL) 
	{
		CRect rcCreate(0,0,0,0);
		Create(NULL,NULL,WS_CHILD,rcCreate,GetDesktopWindow(),100);
	}

	//获取框架
	m_pIClientKernelSink=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,IClientKernelSink);
	if (m_pIClientKernelSink==NULL) return false;
	m_hWndGameFrame=m_pIClientKernelSink->GetFrameWnd();

	//读取配置
	m_bAllowUserLookon=AfxGetApp()->GetProfileInt(TEXT("GameOption"),TEXT("AllowLookon"),FALSE)?true:false;

	//视频设置
	CVideoServiceManager * pVideoServiceManager=CVideoServiceManager::GetInstance();
	if (pVideoServiceManager!=NULL) pVideoServiceManager->SetClientKernel(QUERY_OBJECT_PTR_INTERFACE(this,IUnknownEx));

	//命令行处理
	if (lpszComLine[0]!=0)
	{
		//提出 TOKEN
		int nStringLength=0;
		CString strRoomToken;
		LPCTSTR pszRoomToken=TEXT("/RoomToken:");
		LPCTSTR lpszBeginString=lpszComLine;
		while (true)
		{
			LPCTSTR lpszEndString=_tcschr(lpszBeginString,TEXT(' '));
			nStringLength=(lpszEndString==NULL)?lstrlen(lpszBeginString):(int)(lpszEndString-lpszBeginString);

			//判断标识
			const int nTokenLength=lstrlen(pszRoomToken);
			if ((nStringLength>=nTokenLength)&&(memcmp(lpszBeginString,pszRoomToken,nTokenLength*sizeof(TCHAR))==0))
			{
				CopyMemory(strRoomToken.GetBufferSetLength(nStringLength-nTokenLength),lpszBeginString+nTokenLength,
					(nStringLength-nTokenLength)*sizeof(TCHAR));
				strRoomToken.ReleaseBuffer();
				break;
			}

			//设置变量
			if (lpszEndString==NULL) break;
			lpszBeginString=(lpszEndString+1);
		}

		//共享内存
		if (strRoomToken.GetLength()>0)
		{
			m_hShareMemory=OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,strRoomToken);
			if (m_hShareMemory==NULL) return false;
			m_pShareMemory=(tagShareMemory *)MapViewOfFile(m_hShareMemory,FILE_MAP_ALL_ACCESS,0,0,0);
			if (m_pShareMemory==NULL) return false;
			if (m_pShareMemory->wDataSize<sizeof(tagShareMemory)) return false;
			m_pShareMemory->hWndGameFrame=m_hWndGameFrame;
		}

		//信道模块
		if (m_hShareMemory!=NULL)
		{
			ASSERT(m_pShareMemory->hWndGameServer!=NULL);
			IUnknownEx * pIUnknownEx=QUERY_ME_INTERFACE(IUnknownEx);
			if (m_ChannelServiceHelper.CreateInstance()==false) return false;
			if (m_ChannelServiceHelper->SetChannelMessageSink(pIUnknownEx)==false) return false;
			if (m_ChannelServiceHelper->CreateChannel(m_pShareMemory->hWndGameServer)==false) return false;
		}
	}

	//更新标题
	UpdateGameTitle();

	return true;
}