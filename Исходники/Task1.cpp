	//************************************************
	//*主程序
	//************************************************
	int APIENTRY t1::_tWinMain(HINSTANCE &hInstance,
		HINSTANCE &hPrevInstance,
		LPTSTR    &lpCmdLine,
		int       &nCmdShow, HWND &_hWnd,
		std::string winClassName, std::string winName)
	{
		
		
		// 初始化句柄和状态
		bool bUnClosedLastWin = true;
		hWnd = _hWnd;
		gHinstance = hInstance;
		ShowCursor(FALSE);
		//g_nThreadExitCount = 0;

		//获得传递的命令行参数，得到被试着名字和任务编号
		char *pdest;
		int result;
		int pos1;
		pdest = strrchr(lpCmdLine, ' ');
		pos1 = pdest - lpCmdLine;
		if (pos1>0)
		{
			strncpy(m_TaskNumStr, lpCmdLine, pos1);
		}
		else
		{
			strcpy(m_TaskNumStr, "");
		}
		pdest = strrchr(lpCmdLine, '-');
		result = pdest - lpCmdLine;
		if (result>0)
		{
			strncpy(m_TesterName, lpCmdLine + pos1 + 1, result - pos1 - 1);
		}
		else
		{
			strcpy(m_TesterName, "");
		}
		if (pos1>0)
		{
			strcpy(m_DataName, lpCmdLine + pos1 + 1);
		}
		else
		{
			strcpy(m_DataName, "");
		}
		//读取任务设置
		if (!ReadSetting())
		{
			MessageBox(hWnd, "任务设置文件格式错误！", "测试任务", MB_OK);
			return 0;
		}

		 
		//注册窗口类
		WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS, MsgProc, 0L, 0L,
			hInstance, NULL, NULL, NULL, NULL,
			std::to_string(nCmdShow).c_str(), NULL };
		RegisterClassEx(&wc);

		x_resolution = GetSystemMetrics(SM_CXSCREEN);
		y_resolution = GetSystemMetrics(SM_CYSCREEN);
		rec_x_begin = (x_resolution - 1024) / 2;
		rec_y_begin = (y_resolution - 768) / 2;
		rec_x_end = (x_resolution + 1024) / 2;
		rec_y_end = (y_resolution + 768) / 2;

		_hWnd = hWnd = CreateWindow(std::to_string(nCmdShow).c_str(), std::to_string(nCmdShow).c_str(),
			WS_VISIBLE | WS_POPUP, 0, 0, x_resolution, y_resolution,
			NULL, NULL, hInstance, NULL);

		//显示主窗口
		SetFocus(hWnd);
		

		//创建DirectX设备
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&m_lpkDInput, NULL)))
		{
			return 0;
		}

		float m_JoySpeedMax;
		if (m_HardSetting.m_JoySpeedMax > 0)
		{
			m_JoySpeedMax = m_HardSetting.m_JoySpeedMax;
		}
		else
		{
			m_JoySpeedMax = 200;
		}
		
		//关闭输入法
		HKL hkl;
		hkl = LoadKeyboardLayout("00000804", KLF_ACTIVATE);
		if (hkl != NULL)
		{
			ActivateKeyboardLayout(hkl, KLF_SETFORPROCESS);
		}
		//ShowCursor(FALSE);
		//设置操纵杆变化范围
		if (JoystickInit(hWnd, -m_JoySpeedMax, m_JoySpeedMax, 1))
		{
			JoystickUpdate();
		}
		else
		{
			MessageBox(hWnd, "请检查操纵杆连接是否正确！", "测试任务", MB_OK);
			return 0;
		}

		// declare a variable of our data structure to pass to the ThreadProcedure
		MYDATA MyThreadData;
		MyThreadData.nTime = 7509843;
		MyThreadData.nNumber = 39;

		//创建操纵杆输入线程
		// declare a DWORD to hold our thread's new generated ID
		HANDLE h = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)InputThreadProcedure,
			(LPVOID)&MyThreadData, NULL, &dwInputThreadID);

		
		//	SetPriorityClass(h,NORMAL_PRIORITY_CLASS);
		//	SetThreadPriority(h,THREAD_PRIORITY_ABOVE_NORMAL);

		// actually create and start the thread now!
		// the thread will run until we send it our own WM_THREADSTOP message
		srand((unsigned)time(NULL)); //初始化随机种子

		//初始化Direct3D
		bool b_InitD3d =  SUCCEEDED(InitD3D(hWnd));
		if (b_InitD3d)
		{
			//进入消息循环
			MSG msg;
			ZeroMemory(&msg, sizeof(msg));
			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
				{
					//处理外部消息
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					//执行测试过程
					UpdateState();
					if (m_bDisplayReady)
					{
						//渲染图形
						Render();
						hideLastWindow(bUnClosedLastWin, winClassName, winName, hInstance);
					}
				}
				Sleep(1);

				// 当按下“下一个任务”或“退出”时，终止消息循环
				if (m_TestState == STATE_NEXT 
					|| m_TestState == STATE_EXIT)
				{
					break;
				}
			}
		}
		
		ShowCursor(TRUE);
		CloseHandle(h);
		return rtn;
	}