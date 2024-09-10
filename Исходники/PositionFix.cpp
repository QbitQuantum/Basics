// asynchronous position fix improves stability
ULONG AsyncFixThread( LPVOID pParam )
{
	HWND hWnd = (HWND) pParam;
	
	// little delay is needed to guarantee that window is ready
	for (int x = 0; x < 20; x++)
	{
		Sleep(100);
		if (IsWindow(hWnd) == FALSE)
			return 0;
		if (IsWindowVisible(hWnd) == TRUE)
			break;
	}

	Sleep(100);

	__try
	{
		if (IsWindow(hWnd) == TRUE)
		{
			if ((GetParent(hWnd) == NULL || ((GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD) == NULL)) && IsWindowVisible(hWnd) == TRUE)
			{
				wchar_t className[50];
				ZeroString(className, 50);
				GetClassName(hWnd, className, 50);

				if (wcslen(className))
				{

					RECT rect = {0, 0, 0, 0};
					GetWindowRect(hWnd, &rect);
					int newY = rect.top;
					int newHeight = rect.bottom - rect.top;
					

					if (FixPosition(hWnd, className, 0, &newY, &newHeight) == TRUE)
					{
						SetWindowPos(hWnd, NULL, rect.left, newY, rect.right - rect.left, newHeight, SWP_NOZORDER);
					}

					wchar_t windowName[50];
					ZeroString(windowName, 50);
					GetWindowText(hWnd, windowName, 50);

					DWORD isDoubleFix = IsDoubleFixWindow(hWnd);
					if (isDoubleFix && (IsSipWindowVisible() == TRUE || isDoubleFix == 2) && ShouldBeProcessed(className) == TRUE)
					{
						//RECT rect = {0, 0, 0, 0};
						//GetWindowRect(hWnd, &rect);
						//SetWindowPos(hWnd, NULL, rect.left, rect.top, 
						//	rect.right - rect.left, rect.bottom - rect.top, 
						//	SWP_NOZORDER);
						SIPINFO si;
						GetSipInfo(&si);
						SHSipInfo(SPI_SETSIPINFO, 0, &si, 0);
					}
				}
			}
		}
	}
	__except (GetExceptionCode())
	{
	}
	return 0;
};