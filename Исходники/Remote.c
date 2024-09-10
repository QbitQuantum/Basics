/*************************************
* BOOL GetProcessIdByName(LPSTR szProcessName, LPDWORD lpPID)
* 功能	通过进程名获取进程PID
*
* 参数	LPSTR szProcessName	进程名
*		LPDWORD lpPID		指向保存PID的变量
* 返回是否成功
**************************************/
BOOL GetProcessIdByName(LPSTR szProcessName, LPDWORD lpPID)
{
	// 变量及初始化
	STARTUPINFO st;
	PROCESS_INFORMATION pi;
	PROCESSENTRY32 ps;
	HANDLE hSnapshot;
	ZeroMemory(&st, sizeof(STARTUPINFO));
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	st.cb = sizeof(STARTUPINFO);
	ZeroMemory(&ps,sizeof(PROCESSENTRY32));
	ps.dwSize = sizeof(PROCESSENTRY32);
	// 遍历进程
	hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0);
	if(hSnapshot == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	if(!Process32First(hSnapshot,&ps))
	{
		return FALSE;
	}
	do
	{
		// 比较进程名
		if(lstrcmpi(ps.szExeFile,"explorer.exe")==0)
		{
			// 找到了
			*lpPID = ps.th32ProcessID;
			CloseHandle(hSnapshot);
			return TRUE;
		}
	}
	while(Process32Next(hSnapshot,&ps));
	// 没有找到
	CloseHandle(hSnapshot);
	return FALSE;
}