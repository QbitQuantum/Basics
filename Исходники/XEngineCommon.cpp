	//void winMsgRelease()
	//{
	//	if(customWinProc == daemonProc)
	//	{
	//		Shell_NotifyIcon(NIM_DELETE, &nid);	//资源释放
	//	}
	//}
	void simulateFullScreen(HWND hwnd)
	{
		//方案1
		int ScreenX = GetSystemMetrics(SM_CXSCREEN); //获得全屏的宽
		int ScreenY = GetSystemMetrics(SM_CYSCREEN); //获得全屏的高
		int DialogX = GetSystemMetrics(SM_CXDLGFRAME) - 3; //获得你的窗口左边空白边框的宽度	//-3这个值，不同的系统会不同
		int DialogY = GetSystemMetrics(SM_CYDLGFRAME) + GetSystemMetrics(SM_CYCAPTION);  //获得你的窗口
		WINDOWPLACEMENT newment;
		newment.length = sizeof(WINDOWPLACEMENT);
		newment.flags = WPF_RESTORETOMAXIMIZED;
		newment.showCmd = SW_SHOWMAXIMIZED;

		newment.ptMaxPosition.x = 0;
		newment.ptMaxPosition.y = 0;
		newment.ptMinPosition.x = 0;
		newment.ptMinPosition.y = 0;
		newment.rcNormalPosition.left = -DialogX;      //(0,0)点重合
		newment.rcNormalPosition.top = -DialogY;
		newment.rcNormalPosition.bottom = ScreenX - DialogY; //尺寸一致
		newment.rcNormalPosition.right = ScreenY - DialogX;
		SetWindowPlacement(hwnd, &newment);
		//方案2
		//	SetWindowLongPtr(hwnd, GWL_STYLE, 
		//		WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE);
		//	//MoveWindow(hwnd, 0, 0, windowWidth, windowHeight, TRUE);
		//	setWindowPos(0,0);
	}