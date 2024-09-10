long CProcessTools::KillProcess(LPCTSTR processName,long lWhich)
	//强行关闭任务管理器中映像名称为processName的进程
	//lWhich:关闭第几个映像名称为processName的进程，-1表示全部，0表示第一个
	//返回成功关闭的个数
{
	ASSERT(processName && _tcslen(processName));
	if(!processName || _tcslen(processName)<1) return 0;
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
    if (hProcessSnap == INVALID_HANDLE_VALUE) return 0; 
    PROCESSENTRY32 pe32 = {0};
    pe32.dwSize = sizeof(PROCESSENTRY32); 
    if(!Process32First(hProcessSnap, &pe32))
	{
		CloseHandle(hProcessSnap);
		return 0;
	}
	HANDLE hProcess=NULL;
	long ret=0;
	long count=0;
	do
	{
		hProcess = OpenProcess (PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID); 
		if(_tcsicmp(pe32.szExeFile,processName)) CloseHandle (hProcess);
		else
		{
			if(count==lWhich || lWhich==-1)//需要关闭
			{
				if(TerminateProcess(hProcess,0)) ret++;
			}
			CloseHandle(hProcess);
			if(lWhich!=-1) break;//不是关闭所有,停止枚举
		}
	} 
	while(Process32Next(hProcessSnap, &pe32));
    CloseHandle (hProcessSnap);
	return ret;
}