BOOL CSpiCommApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

    CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	CSpiCommDlg dlg;

	// Lets check if BT is plugged in
	HANDLE hRadio = INVALID_HANDLE_VALUE;
	BLUETOOTH_FIND_RADIO_PARAMS params = {sizeof(BLUETOOTH_FIND_RADIO_PARAMS)};
	HBLUETOOTH_RADIO_FIND hf = BluetoothFindFirstRadio(&params, &hRadio);
	if (hf == NULL)
	{
		MessageBox(NULL, L"Bluetooth radio is not present or not functioning.  Please plug in the dongle and try again.", L"Error", MB_OK);
		return FALSE;
	}
    CloseHandle(hRadio);
    BluetoothFindRadioClose(hf);

	// This application supports Microsoft on Win8 or BTW on Win7.
	if (IsOSWin8())
	{
		dlg.m_bWin8 = TRUE;
        if ((hLib = LoadLibrary(L"BluetoothApis.dll")) == NULL)
		{
			MessageBox(NULL, L"Failed to load BluetoothAPIs library", L"Error", MB_OK);
			return FALSE;
		}
        guidSvcSpiComm                = GUID_SPI_COMM_SERVICE;
        guidCharSpiCommControlPoint   = GUID_SPI_COMM_CHARACTERISTIC_CONTROL_POINT;
        guidCharSpiCommData           = GUID_SPI_COMM_CHARACTERISTIC_DATA;
	}
	else if (IsOSWin7())
	{
		dlg.m_bWin8 = FALSE;

        if ((hLib = LoadLibrary(L"BtwLeApi.Dll")) == NULL)
		{
			MessageBox(NULL, L"Broadcom Blueototh profile pack for Windows (BTW) has to be installed", L"Error", MB_OK);
			return FALSE;
		}
        BtwGuidFromGuid(&guidSvcSpiComm, &GUID_SPI_COMM_SERVICE);
        BtwGuidFromGuid(&guidCharSpiCommControlPoint, &GUID_SPI_COMM_CHARACTERISTIC_CONTROL_POINT);
        BtwGuidFromGuid(&guidCharSpiCommData, &GUID_SPI_COMM_CHARACTERISTIC_DATA);
	}
	else
	{
		MessageBox(NULL, L"This application requires Windows 8 or Windows 7 with Broadcom Bluetooth profile pack for Windows (BTW) installed", L"Error", MB_OK);
		return FALSE;
	}

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	SetRegistryKey(_T("Broadcom"));

	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}
	else if (nResponse == -1)
	{
	}
    if (hLib != NULL)
        FreeLibrary(hLib);

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}