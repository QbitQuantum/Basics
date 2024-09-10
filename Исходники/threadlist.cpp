//-----------------------------------------------------------------------------
// 初始化
bool C_ThreadList::Initialize(IN unsigned long ulProcessID)
{
	m_Thread.clear();

	C_WHandle ccSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0); // 取得處理程序中執行緒的快照

	if(ccSnap == INVALID_HANDLE_VALUE)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("CreateToolhelp32Snapshot failed"));

	THREADENTRY32 sThread;

	ZeroMemory(&sThread, sizeof(sThread));
	sThread.dwSize = sizeof(sThread);

	// 取得第一個執行緒列表資訊
	if(Thread32First(static_cast<HANDLE>(ccSnap), &sThread) == FALSE)
		return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("Thread32First failed"));

	// 依序取得執行緒列表資訊
	do
	{
		// 檢查此執行緒資訊是否屬於輸入的處理程序
		if(sThread.th32OwnerProcessID == ulProcessID)
			m_Thread.push_back(S_Thread(sThread));
	} while(Thread32Next(static_cast<HANDLE>(ccSnap), &sThread) == TRUE);

	return true;
}