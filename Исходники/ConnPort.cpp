int ConnPort::OpenPort(TCHAR *szPort,int iBaudrate,int iParity,int iDataBits,int iStopBits)
{
	 DWORD dwThreadID=0;
	 g_iExitFlag=0;
	 m_hPort=NULL;
	
	 m_hPort=CreateFile(szPort,
						GENERIC_READ|GENERIC_WRITE,
						0,
						NULL,
						OPEN_EXISTING,
						FILE_FLAG_OVERLAPPED,
						NULL);
    if(!m_hPort) 
    {
        m_hPort=NULL;
        wprintf(TEXT("open port failed!!!\r\n"));
        return FALSE;
    }

   //指定端口检测的事件集
   SetCommMask(m_hPort,EV_RXCHAR);
   //设置缓冲区，内部输入、输出缓冲区大小
   SetupComm(m_hPort,1024,1024);
   //刷新缓冲区信息->输入、输出缓冲区
   PurgeComm(m_hPort,PURGE_TXCLEAR|PURGE_RXCLEAR);

   if(!ConfigPort(iBaudrate,iParity,iDataBits,iStopBits)) return FALSE;
   if(!CommTimeouts())return FALSE;

  //创建读写线程
   m_hThreadRead	=	CreateThread(0,0,(LPTHREAD_START_ROUTINE)ReadThreadProc,	(void*)this,0,&dwThreadID);
   m_hThreadWrite	=	CreateThread(0,0,(LPTHREAD_START_ROUTINE)WriteThreadProc,	(void*)this,0,&dwThreadID);
   m_hDataParse		=   CreateThread(0,0,(LPTHREAD_START_ROUTINE)PareDataProc,		(void*)this,0,&dwThreadID);

   m_bIsConnect=TRUE;
   return TRUE;
}