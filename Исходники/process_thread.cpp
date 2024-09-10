int TraceAllThreadByPid(const DWORD Pid,DWORD *Tid)
{
	int count=0;
	THREADENTRY32 th32;
	th32.dwSize=sizeof(th32);//指定结构的长度，以字节为单位。在调用Thread32First时，设置这个成员为SIZEOF（THREADENTRY32）。如果你不初始化的dwSize，Thread32First将调用失败。 
	HANDLE hThreadSnap=::CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,0);
	//CreateToolhelp32Snapshot可以通过获取进程信息为指定的进程、进程使用的堆[HEAP]、模块[MODULE]、线程建立一个快照。
	if(hThreadSnap==INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	bool more=Thread32First(hThreadSnap,&th32);
	while(more)
	{
		if(th32.th32OwnerProcessID==Pid)
		{
			Tid[count++]=th32.th32ThreadID;
		}
		more=Thread32Next(hThreadSnap,&th32);//hTreadSnap快照句柄
	}
	CloseHandle(hThreadSnap);
	return count;
}