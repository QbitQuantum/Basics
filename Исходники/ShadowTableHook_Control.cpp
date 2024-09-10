VOID CMainDialog::OnHideWindowHandles()
{
	CHAR ProcessName[MAX_PATH];
	CEdit *pProcessName = (CEdit *)GetDlgItem(IDC_PROCESSNAME);
	CButton *pHideWindowHandlesButton = (CButton *)GetDlgItem(IDHIDEWINDOWHANDLES);
	CButton *pShowWindowHandlesButton = (CButton *)GetDlgItem(IDSHOWWINDOWHANDLES);

	pProcessName->GetWindowText(ProcessName, sizeof(ProcessName));
	strcat(ProcessName, ".exe");

	DWORD HiddenWindowHandleProcessId;
	LPVOID pHiddenWindowHandleProcessId = &HiddenWindowHandleProcessId;

	if(FALSE != (HiddenWindowHandleProcessId = GetProcessID(ProcessName)))
	{
		pHideWindowHandlesButton->EnableWindow(FALSE);
		pShowWindowHandlesButton->EnableWindow(TRUE);
	}
	else
	{
		MessageBox("Process Does Not Exist!", "Error", MB_ICONERROR);
		return;
	}

	if (DriverLoaded)
	{
		UnloadDriver();
		DriverLoaded = FALSE;
	}

	LoadDriver();
	DriverLoaded = TRUE;

	CommDevice = CreateFile("\\\\.\\ShadowTableHookDriver", GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if(CommDevice == INVALID_HANDLE_VALUE)
	{
		int error = GetLastError();

		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, 
			GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 
			0, NULL);

		MessageBox((LPTSTR)lpMsgBuf, "GetLastError", MB_OK|MB_ICONINFORMATION);

		return;
	}

	if(CommDevice)
	{
		DWORD dwReturn;

		if (0 == (DeviceIoControl(CommDevice, IO_SEND_HIDDEN_PROCESS_ID, 
			pHiddenWindowHandleProcessId, sizeof(HiddenWindowHandleProcessId), 
			NULL, 0, &dwReturn, NULL)))
		{
			int error = GetLastError();

			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, 
				GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 
				0, NULL);

			MessageBox((LPCSTR)lpMsgBuf, "GetLastError", MB_OK|MB_ICONINFORMATION);

			return;
		}
	}

	if(CommDevice)
	{
		DWORD dwReturn;

		IsGUIThread(TRUE);

		if (0 == (DeviceIoControl(CommDevice, IO_HOOK_SYSTEM_SERVICES, NULL, 0, 
			NULL, 0, &dwReturn, NULL)))
		{
			int error = GetLastError();

			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, 
				GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 
				0, NULL);

			MessageBox((LPCSTR)lpMsgBuf, "GetLastError", MB_OK|MB_ICONINFORMATION);

			return;
		}
	}

}