//构建TCP进程字典
int ProcessMap::BuildTcpProcDict()
{
	//清空processtcpdict
	ClearTcpProcessDict();
	portdict.clear();
	//构建tcpportdict
	MIB_TCPTABLE_OWNER_PID tcptable;
	tcptable.dwNumEntries = sizeof(tcptable)/sizeof(tcptable.table[0]);
	DWORD tcptablesize = sizeof(tcptable);
	//if(GetExtendedTcpTable((void *)&tcptable, &tcptablesize, FALSE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0) == NO_ERROR)
	int tcptableerror = GetExtendedTcpTable((void *)&tcptable, &tcptablesize, FALSE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);
	if(tcptableerror == NO_ERROR)
	{
		for(unsigned int i =0 ; i< tcptable.dwNumEntries; i++)
		{
			int port = ntohs((unsigned short)tcptable.table[i].dwLocalPort);
			int pid = tcptable.table[i].dwOwningPid;
			portdict.insert(pair<int ,int>(port,pid));
		}
	}
	// Take a snapshot
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 p;
	p.dwSize = sizeof(PROCESSENTRY32);
	// Traverse Process List
	for(BOOL ret = Process32First(hSnapShot, &p); ret != 0; ret = Process32Next(hSnapShot, &p))
	{
		// Get pid and file name
		int pid = p.th32ProcessID;
		for(portdictit = portdict.begin();portdictit!=portdict.end();portdictit++)
		{
			if(portdictit->second == pid)
			{
				ProcessNode *processnode = new ProcessNode;
				processnode->pid = pid;
				processnode->processname = TCHARTochar(p.szExeFile);
				// Get full path (if possible)
				HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
				if (hProcess == 0)
				{
					processnode->processpath = NULL;
				}
				else
				{
					TCHAR fullPath[MAX_PATH];
					if (GetModuleFileNameEx(hProcess, 0, fullPath, MAX_PATH) > 0)// Success
					{
						processnode->processpath = TCHARTochar(fullPath);
					}
					else
						processnode->processpath = NULL;
				}
				CloseHandle(hProcess);
				tcpprocessdict.insert(pair<int,ProcessNode*>(portdictit->first,processnode));
			}
		}
		
	}
	CloseHandle(hSnapShot);

	UpdateUnknowTcpportdict();
	return 0;
}