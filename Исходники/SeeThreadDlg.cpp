void SeeThreadDlg::initThreadList()
{
	//遍历所有的thread；
	//
	SetWindowText(m_StrThread);
	THREADENTRY32 thd32={sizeof(THREADENTRY32)};
	HANDLE hThreadsnap;
	hThreadsnap=CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD
		,m_currPid);
	if (hThreadsnap==INVALID_HANDLE_VALUE)
	{
		return;
	}
	if (!Thread32First(hThreadsnap,&thd32))
	{
		CloseHandle(hThreadsnap);
		return;
	}
	m_VecThdList.clear();
	do 
	{
		_stprintf_s(strThreadId,_T("%d"),thd32.th32ThreadID);
		m_ThreadList.InsertItem(0,strThreadId);
		m_VecThdList.push_back(thd32);

	} while (Thread32Next(hThreadsnap,&thd32));
	CloseHandle(hThreadsnap);
}