//
// WinProcCallback
//
INT_PTR WINAPI WinProcCallback(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
	)
	// Routine Description:
	//     Simple Windows callback for handling messages.
	//     This is where all the work is done because the example
	//     is using a window to process messages. This logic would be handled 
	//     differently if registering a service instead of a window.

	// Parameters:
	//     hWnd - the window handle being registered for events.

	//     message - the message being interpreted.

	//     wParam and lParam - extended information provided to this
	//          callback by the message sender.

	//     For more information regarding these parameters and return value,
	//     see the documentation for WNDCLASSEX and CreateWindowEx.
{
	LRESULT lRet = 1;
	static HDEVNOTIFY hDeviceNotify;
	static HWND hEditWnd;
	static ULONGLONG msgCount = 0;

	switch (message)
	{
	case WM_CREATE:
		//
		// This is the actual registration., In this example, registration 
		// should happen only once, at application startup when the window
		// is created.
		//
		// If you were using a service, you would put this in your main code 
		// path as part of your service initialization.
		//
		if (!DoRegisterDeviceInterfaceToHwnd(
			WceusbshGUID,
			hWnd,
			&hDeviceNotify))
		{
			// Terminate on failure.
			ErrorHandler(TEXT("DoRegisterDeviceInterfaceToHwnd"));
			ExitProcess(1);
		}


		//
		// Make the child window for output.
		//
		hEditWnd = CreateWindow(TEXT("EDIT"),// predefined class 
			NULL,        // no window title 
			WS_CHILD | WS_VISIBLE | WS_VSCROLL |
			ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
			0, 0, 0, 0,  // set size in WM_SIZE message 
			hWnd,        // parent window 
			(HMENU)1,    // edit control ID 
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);       // pointer not needed 

		if (hEditWnd == NULL)
		{
			// Terminate on failure.
			ErrorHandler(TEXT("CreateWindow: Edit Control"));
			ExitProcess(1);
		}
		// Add text to the window. 
		SendMessage(hEditWnd, WM_SETTEXT, 0,
			(LPARAM)TEXT("Registered for USB device notification...\n"));

		break;

	case WM_SETFOCUS:
		SetFocus(hEditWnd);

		break;

	case WM_SIZE:
		// Make the edit control the size of the window's client area. 
		MoveWindow(hEditWnd,
			0, 0,                  // starting x- and y-coordinates 
			LOWORD(lParam),        // width of client area 
			HIWORD(lParam),        // height of client area 
			TRUE);                 // repaint window 

		break;

	case WM_DEVICECHANGE:
	{
		//
		// This is the actual message from the interface via Windows messaging.
		// This code includes some additional decoding for this particular device type
		// and some common validation checks.
		//
		// Note that not all devices utilize these optional parameters in the same
		// way. Refer to the extended information for your particular device type 
		// specified by your GUID.
		//
		PDEV_BROADCAST_DEVICEINTERFACE b = (PDEV_BROADCAST_DEVICEINTERFACE)lParam;
		TCHAR strBuff[256];

		// Output some messages to the window.
		switch (wParam)
		{
		case DBT_DEVICEARRIVAL:
			msgCount++;
			StringCchPrintf(
				strBuff, 256,
				TEXT("Message %d: DBT_DEVICEARRIVAL\n"), msgCount);
			break;
		case DBT_DEVICEREMOVECOMPLETE:
			msgCount++;
			StringCchPrintf(
				strBuff, 256,
				TEXT("Message %d: DBT_DEVICEREMOVECOMPLETE\n"), msgCount);
			break;
		case DBT_DEVNODES_CHANGED:
			msgCount++;
			StringCchPrintf(
				strBuff, 256,
				TEXT("Message %d: DBT_DEVNODES_CHANGED\n"), msgCount);
			break;
		default:
			msgCount++;
			StringCchPrintf(
				strBuff, 256,
				TEXT("Message %d: WM_DEVICECHANGE message received, value %d unhandled.\n"),
				msgCount, wParam);
			break;
		}
		OutputMessage(hEditWnd, wParam, (LPARAM)strBuff);
	}
		break;
	case WM_CLOSE:
		if (!UnregisterDeviceNotification(hDeviceNotify))
		{
			ErrorHandler(TEXT("UnregisterDeviceNotification"));
		}
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		// Send all other messages on to the default windows handler.
		lRet = DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return lRet;
}