bool SockPool::Create(CString user)
{
	Wsemaphore = CreateSemaphore(NULL, 1, 100, user + _T("NetProtocolWsemaphore"));//创建信号量P
	Rsemaphore = CreateSemaphore(NULL, 0, 100, user + _T("NetProtocolRsemaphore"));//创建信号量C
	Dsemaphore = CreateSemaphore(NULL, 0, 100, user + _T("NetProtocolDsemaphore"));//创建信号量S
	MFile = CreateFileMapping(HANDLE(0xFFFFFFFF), NULL, PAGE_READWRITE, 0, sizeof(regstruct), user + _T("NetProtocolListen"));///<创建注册文件
	//if (MFile == NULL)
		//AfxMessageBox(user + _T("NetProtocolListen") + _T("   failed"));
	//AfxMessageBox(user + _T("NetProtocolListen") + _T("   success"));
	SH = OpenProcess(PROCESS_ALL_ACCESS, FALSE, _getpid());///<获取本机IP
	CString soc;
	int len = user.GetLength();
	soc = user.Mid(len - 6, len);
	if (soc.Compare(_T("server"))==0){
		HANDLE Success = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, user + _T("NetProtocolCreate"));
		if (Success == NULL){
			AfxMessageBox(_T("参数传递失败!"));
			exit(0);
			return false;
		}
		ReleaseSemaphore(Success, 1, NULL);
	}
	preg = (regstruct *)MapViewOfFile(MFile, FILE_MAP_WRITE, 0, 0, sizeof(regstruct)); ///<映射注册文件
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)NewConnThread, (LPVOID) this, NULL, NULL);
	return true;
}