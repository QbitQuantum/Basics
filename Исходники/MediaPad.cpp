int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	
    // Application related local variables
    MSG msg;
    HACCEL hAccelTable;
    TCHAR Text[100 + MAX_PATH];

    // COM related local variables
    DWORD dwIndex;
    TCHAR szDeviceName[MAX_PATH];
    TCHAR ComPort[20];
    DWORD dwReturnValue;
    DCB dcb;                                    // COM device-control block
    COMMTIMEOUTS CommTimeouts;                  // COM timeout structure

    // Initialize global strings
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_430BOOST_CAPTOUCH_MEDIAPAD, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization
    if (!InitInstance(hInstance, nCmdShow))
    {
        MessageBox(NULL,
            _T("An error occured during application init!\r\n") \
            _T("Press OK to exit program."),
            _T("430Boost-CapTouch MediaControl Error Dialog"),
            MB_OK | MB_ICONEXCLAMATION);
        return 1;                               // Exit program
    }

    // Scan through all COM port class devices in the system and
    // check for a friendly name / HW ID match with the MSP-EXP430F5438
    // demo board. COM devices from 0 to MAX_COM_SEARCH_INDEX
    // are scanned.
    for (dwIndex = 0; dwIndex < MAX_COM_SEARCH_INDEX; dwIndex++)
    {
        dwReturnValue = EnumComPorts(dwIndex, szDeviceName, _countof(szDeviceName));
		

        if (dwReturnValue == ERROR_SUCCESS)
        {
            break;                                    // COM port found!
        }
        else if (dwReturnValue == ERROR_NO_MORE_ITEMS)
        {
            MessageBox(hWnd,
                _T("MSP430G2-LaunchPad not found!\r\n") \
                _T("Double-check LaunchPad USB driver installation and connections.\r\n\r\n") \
                _T("Press OK to exit program."),
                _T("430Boost-CapTouch MediaControl Error Dialog"),
                MB_OK | MB_ICONEXCLAMATION);
            Shell_NotifyIcon(NIM_DELETE, &nidApp);    // Remove notification bar icon
            return 1;
        }
        else
        {
           MessageBox(hWnd,
                _T("An error occured during VCP initialization!\r\n") \
                _T("Press OK to exit program."),
                _T("430Boost-CapTouch MediaControl Error Dialog"),
                MB_OK | MB_ICONEXCLAMATION);
            Shell_NotifyIcon(NIM_DELETE, &nidApp);    // Remove notification bar icon
            return 1;
        }
    }

    // COM Interface Initializations
    _tcscpy_s(&ComPort[0], _countof(ComPort), _T("\\\\.\\"));       // Preceed name with "\\.\" to
    _tcscpy_s(&ComPort[4], _countof(ComPort) - 4, szDeviceName);    // access higher # ports

    hCom = CreateFile(ComPort,                  // COM-Port
						
        GENERIC_READ | GENERIC_WRITE,           // read/write-mode
        0,                                      // Open w/ exclusive-access
        NULL,                                   // no security attributes
        OPEN_EXISTING,                          // creation distribution
        FILE_FLAG_OVERLAPPED,                   // Use overlapped I/O
        NULL);                                  // hTemplate must be NULL

    if (hCom == INVALID_HANDLE_VALUE)           // Open successful?
    {
        _stprintf_s(Text, _countof(Text),
            _T("Error opening %s!"), szDeviceName);

        MessageBox(hWnd, Text,
            _T("430Boost-CapTouch MediaControl Error Dialog"),
            MB_OK | MB_ICONEXCLAMATION);
        Shell_NotifyIcon(NIM_DELETE, &nidApp);  // Remove notification bar icon
        return 1;
    }

    if (!GetCommState(hCom, &dcb))              // Read current DCB
    {
        MessageBox(hWnd,
            _T("An error occured during VCP initialization!\r\n") \
            _T("Press OK to exit program."),
            _T("430Boost CapTouch MediaControl Error Dialog"),
            MB_OK | MB_ICONEXCLAMATION);
        CloseHandle(hCom);                      // Close COM ressource
        return 1;                               // Exit program
    }

    dcb.BaudRate        = 9600;               // Set baud rate
    dcb.fBinary         = TRUE;
    dcb.fParity         = FALSE;
    dcb.fOutxCtsFlow    = FALSE;                // Disable flow-control for
    dcb.fOutxDsrFlow    = FALSE;                // working with only 3 lines
    dcb.fDsrSensitivity = FALSE;                // (GND, RXD, TXD)
    dcb.fOutX           = FALSE;
    dcb.fInX            = FALSE;
    dcb.fNull           = FALSE;
    dcb.fRtsControl     = RTS_CONTROL_DISABLE;  // Disable flow control
    dcb.fAbortOnError   = FALSE;
    dcb.ByteSize        = 8;
    dcb.StopBits        = ONESTOPBIT;

    if (!SetCommState(hCom, &dcb))              // Set DCB
    {
        MessageBox(hWnd,
            _T("An error occured during VCP initialization!\r\n") \
            _T("Press OK to exit program."),
            _T("430Boost-CapTouch MediaControl Error Dialog"),
            MB_OK | MB_ICONEXCLAMATION);
        Shell_NotifyIcon(NIM_DELETE, &nidApp);  // Remove notification bar icon
        CloseHandle(hCom);                      // Close COM ressource
        return 1;                               // Exit program
    }

    CommTimeouts.ReadIntervalTimeout         = 0;
    CommTimeouts.ReadTotalTimeoutMultiplier  = 1000;  // Wait 1s per RX char
    CommTimeouts.ReadTotalTimeoutConstant    = 0;
    CommTimeouts.WriteTotalTimeoutMultiplier = 0;
    CommTimeouts.WriteTotalTimeoutConstant   = 0;

    if (!SetCommTimeouts(hCom, &CommTimeouts))  // Set COM timeouts
    {
        MessageBox(hWnd,
            _T("An error occured during VCP initialization!\r\n") \
            _T("Press OK to exit program."),
            _T("430Boost-CapTouch MediaControl Error Dialog"),
            MB_OK | MB_ICONEXCLAMATION);
        Shell_NotifyIcon(NIM_DELETE, &nidApp);  // Remove notification bar icon
        CloseHandle(hCom);                      // Close COM ressource
        return 1;                               // Exit program
    }

    // Initialization sequence all-go. Show the COM port to the user
    // and start the run loop.
    _stprintf_s(Text, sizeof Text / sizeof TCHAR,
        _T("LaunchPad CapTouch found on %s.\r\n") \
        _T("Press OK to minimize the application and start the program."),
        szDeviceName);
    MessageBox(hWnd, Text,
        _T("430Boost-CapTouch MediaControl Dialog"),
        MB_OK | MB_ICONINFORMATION);

    // Activate UART RX functionality
    if (!ReadFileEx(hCom, COMBuffer, 2, &OverlappedIn, FileIOCompletionRoutine))
    {
        MessageBox(hWnd,
            _T("An error occured during VCP initialization!\r\n") \
            _T("Press OK to exit program."),
            _T("430Boost-CapTouch MediaControl Error Dialog"),
            MB_OK | MB_ICONEXCLAMATION);
        Shell_NotifyIcon(NIM_DELETE, &nidApp);  // Remove notification bar icon
        CloseHandle(hCom);                      // Close COM ressource
        return 1;                               // Exit program
    }


    ZeroMemory(&msg, sizeof(msg));

    // Enter the message handling loop
    while (msg.message != WM_QUIT)
    {
        // Wait for any message while staying in an alertable state to
        // process asynchronous I/O.
        MsgWaitForMultipleObjectsEx(0, NULL, INFINITE, QS_ALLINPUT, MWMO_ALERTABLE);

        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }

    // Application cleanup
    Shell_NotifyIcon(NIM_DELETE, &nidApp);      // Remove notification bar icon
    CloseHandle(hCom);                          // Close COM ressource

    return 0;                                   // Exit application
}