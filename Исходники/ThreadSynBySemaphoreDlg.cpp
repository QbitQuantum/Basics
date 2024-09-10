/*
*函数介绍：线程执行过程
*入口参数：pArg：创建线程时，传进来的参数，这里指的列表框控件指针
*出口参数：(无)
*返回值：这里只返回1。
*/
DWORD  CThreadSynBySemaphoreDlg::ThreadProc(PVOID pArg)
{

	CListBox* pLstBox = (CListBox*)pArg;

	TCHAR buffer[10];
	//等待信号量可用，当信号量计数大于0时，可用
	if (WaitForSingleObject(g_hSynSemaphore,INFINITE) == WAIT_OBJECT_0)
	{

		//给数组赋值
		for (int i=0;i<MAXDATASIZE;i++)
		{
			g_incNum++;  //加1
			g_aGlobalData[i] = g_incNum;  //赋值
			Sleep(5);
		}
		
		//显示已经赋值的数组
		for(int i = 0 ; i < MAXDATASIZE ; i++)
		{
			_itow(g_aGlobalData[i],buffer,10);
			pLstBox->AddString(buffer);  //
		}
	}
	//因为等待函数自动给信号量计数减1
	//所以给信号量计数加1，使信号量继续可用
	ReleaseSemaphore(g_hSynSemaphore,1,NULL);
	return 1;
}