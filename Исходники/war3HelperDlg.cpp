//定义全局的底层键盘钩子回调函数
LRESULT CALLBACK LowLevelKeyboardProc(int nCode,WPARAM wParam,LPARAM lParam)
{
	//获取最前端窗口
	topWnd = GetForegroundWindow();

	//通过读取内存信息来判断是否为聊天模式
	//获取窗口进程ID
	DWORD processid;
	::GetWindowThreadProcessId(m_hwar3,&processid);
	//打开指定进程
	HANDLE processH=::OpenProcess(PROCESS_ALL_ACCESS,false,processid);
	//读指定进程 内存数据
	LPCVOID pbase=(LPCVOID)0x6FAE8450; //数据基址 通过此数据来判断聊天模式，通过CE查找。
	int chatStatus;
	//LPVOID  nbuffer=(LPVOID)&chatNum;

	::ReadProcessMemory(processH,pbase,&chatStatus,4,NULL);
	if (chatStatus)
	{
		return CallNextHookEx(m_hkeyboard,nCode,wParam,lParam);
	}
	if (topWnd==m_hwar3)  //如果最前端的窗口是魔兽争霸的窗口，则开启改键功能
	{
		PKBDLLHOOKSTRUCT kbstruct;
		if(0==PostMessage(m_hwar3,WM_KEYDOWN,0x4C,1))
		{
			ASSERT(0);
			return  1;
		}

		if (WM_KEYDOWN==wParam)
		{
			kbstruct=(PKBDLLHOOKSTRUCT)lParam;
			//修改小键盘
			if ((int)g_num1[0]==kbstruct->vkCode)
			{
				keybd_event(VK_NUMPAD1,0,0,0);
				keybd_event(VK_NUMPAD1,0,KEYEVENTF_KEYUP,0);
				return 1;
			}
			if ((int)g_num2[0]==kbstruct->vkCode)
			{
				keybd_event(VK_NUMPAD2,0,0,0);
				keybd_event(VK_NUMPAD2,0,KEYEVENTF_KEYUP,0);
				return 1;
			}
			if ((int)g_num4[0]==kbstruct->vkCode)
			{
				keybd_event(VK_NUMPAD4,0,0,0);
				keybd_event(VK_NUMPAD4,0,KEYEVENTF_KEYUP,0);
				return 1;
			}
			if ((int)g_num5[0]==kbstruct->vkCode)
			{
				keybd_event(VK_NUMPAD5,0,0,0);
				keybd_event(VK_NUMPAD5,0,KEYEVENTF_KEYUP,0);
				return 1;
			}
			if ((int)g_num7[0]==kbstruct->vkCode)
			{
				keybd_event(VK_NUMPAD7,0,0,0);
				keybd_event(VK_NUMPAD7,0,KEYEVENTF_KEYUP,0);
				return 1;
			}
			if ((int)g_num8[0]==kbstruct->vkCode)
			{
				keybd_event(VK_NUMPAD8,0,0,0);
				keybd_event(VK_NUMPAD8,0,KEYEVENTF_KEYUP,0);
				return 1;
			}

			//修改技能键
			if ((int)g_newmag1[0]==kbstruct->vkCode && (int)g_oldmag1[0]!=0)
			{
				keybd_event(g_oldmag1[0],0,0,0);
				keybd_event(g_oldmag1[0],0,KEYEVENTF_KEYUP,0);
				return 1;
			}
			if ((int)g_newmag2[0]==kbstruct->vkCode && (int)g_oldmag2[0]!=0)
			{
				keybd_event(g_oldmag2[0],0,0,0);
				keybd_event(g_oldmag2[0],0,KEYEVENTF_KEYUP,0);
				return 1;
			}
			if ((int)g_newmag3[0]==kbstruct->vkCode && (int)g_oldmag3[0]!=0)
			{
				keybd_event(g_oldmag3[0],0,0,0);
				keybd_event(g_oldmag3[0],0,KEYEVENTF_KEYUP,0);
				return 1;
			}
			if ((int)g_newmag4[0]==kbstruct->vkCode && (int)g_oldmag4[0]!=0)
			{
				keybd_event(g_oldmag4[0],0,0,0);
				keybd_event(g_oldmag4[0],0,KEYEVENTF_KEYUP,0);
				return 1;
			}

		}
	}

	return CallNextHookEx(m_hkeyboard,nCode,wParam,lParam);
}