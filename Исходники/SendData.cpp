bool InitCom(HANDLE& m_hCom, OVERLAPPED& wrOverlapped, char* comNum)
{
	//第一步，打开串口
	//HANDLE m_hCom;
	
	m_hCom = CreateFile((LPCWSTR)comNum, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if (m_hCom == INVALID_HANDLE_VALUE)
	{
		std::cout << "CreateFile fail!" << endl;
		return false;
	}
	//cout << "CreateFile OK!" << endl;

	//第二步，设置缓冲区大小
	if (!SetupComm(m_hCom, 2048, 2048))
	{
		cout << "SetupComm fail! Close Comm!" << endl;
		CloseHandle(m_hCom);
		return false;
	}
	//cout << "SetupComm OK!" << endl;

	//第三步，设置超时
	COMMTIMEOUTS TimeOuts;
	memset(&TimeOuts, 0, sizeof(TimeOuts));
	TimeOuts.ReadIntervalTimeout = MAXDWORD;
	TimeOuts.ReadTotalTimeoutConstant = 0;
	TimeOuts.ReadTotalTimeoutMultiplier = 0;
	TimeOuts.WriteTotalTimeoutConstant = 2000;
	TimeOuts.WriteTotalTimeoutMultiplier = 2000;
	SetCommTimeouts(m_hCom, &TimeOuts);

	//第四步，设置串口参数
	DCB dcb;
	if (!GetCommState(m_hCom, &dcb))
	{
		cout << "GetCommState fail! Comm close" << endl;
		CloseHandle(m_hCom);
		return false;
	}
	//cout << "GetCommState OK!" << endl;

	dcb.DCBlength = sizeof(dcb);
	if (!BuildCommDCB((WCHAR*)_T("9600,n,8,1"), &dcb))//填充DCB的数据传输率、奇偶校验类型、数据位、停止位
	{
		//参数修改错误，进行错误处理
		cout << "BuileCOmmDCB fail,Comm close!" << endl;
		CloseHandle(m_hCom);
		return false;
	}
	if (SetCommState(m_hCom, &dcb))
	{
		//cout << "SetCommState OK!" << endl;
	}

	//第五步，建立并初始化重叠结构
	ZeroMemory(&wrOverlapped, sizeof(wrOverlapped));
	if (wrOverlapped.hEvent != NULL)
	{
		ResetEvent(wrOverlapped.hEvent);
		wrOverlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	}
	return true;
}