int CALLBACK WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR theCmdLine, int nCmdShow)
{
	HANDLE				myAccel;
	HWND				myWindowFrame;
	MSG					myMsg;
    WNDCLASSEX			myWC;
	char				myFileName[MAX_PATH];
	DWORD				myLength;
	OSErr				myErr = noErr;

	ghInst = hInstance;
	gCmdLine = theCmdLine;
	
	if (hPrevInstance == NULL) {
		LoadString(hInstance, IDS_APPNAME, gAppName, sizeof(gAppName));
		
		// register the frame window class
		myWC.cbSize        = sizeof(WNDCLASSEX);
		myWC.style         = CS_HREDRAW | CS_VREDRAW;
		myWC.lpfnWndProc   = (WNDPROC)QTFrame_FrameWndProc;
		myWC.cbClsExtra    = 0;
		myWC.cbWndExtra    = 0;
		myWC.hInstance     = hInstance;
		myWC.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON));
		myWC.hCursor       = LoadCursor(NULL, IDC_ARROW);
		myWC.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		myWC.lpszMenuName  = gAppName;
		myWC.lpszClassName = gAppName;
		myWC.hIconSm       = LoadImage(hInstance, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 16, 16, 0);
									 
		if (!RegisterClassEx(&myWC)) {
			if (!RegisterClass((LPWNDCLASS)&myWC.style))
        		return(0);
		}

		// register the movie child window class
		myWC.cbSize        = sizeof(WNDCLASSEX);
		myWC.style         = 0;
		myWC.lpfnWndProc   = (WNDPROC)QTFrame_MovieWndProc;
		myWC.cbClsExtra    = 0;
		myWC.cbWndExtra    = 0;
		myWC.hInstance     = hInstance;
		myWC.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CHILDICON));
		// to avoid having QuickTime VR "fight" with the system over the cursor,
		// we set the client area cursor to NULL; this means that for QuickTime
		// movies, we'll need to change the cursor to an arrow manually; see the
		// handling of the WM_MOUSEMOVE message in QTFrame_MovieWndProc
		myWC.hCursor       = NULL;
		myWC.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		myWC.lpszMenuName  = NULL;
		myWC.lpszClassName = gChildName;
		myWC.hIconSm       = LoadImage(hInstance, MAKEINTRESOURCE(IDI_CHILDICON), IMAGE_ICON, 16, 16, 0);
									 
		if (!RegisterClassEx(&myWC)) {
			if (!RegisterClass((LPWNDCLASS)&myWC.style))
        		return(0);
		}
	}

	// load accelerators
	myAccel = LoadAccelerators(hInstance, gAppName);

	// initialize QuickTime Media Layer and QuickTime; alert the user and return 0 if unsuccessful
	myErr = InitializeQTML(0L);
	if (myErr != noErr) {
		MessageBox(NULL, "QuickTime is not installed on this computer. Exiting.", gAppName, MB_OK | MB_APPLMODAL);
		return(0);
	}
	
	myErr = EnterMovies();
	if (myErr != noErr) {
		MessageBox(NULL, "Could not initialize QuickTime. Exiting.", gAppName, MB_OK | MB_APPLMODAL);
		return(0);
	}

	// get the application's resource file, if it exists
	myLength = GetModuleFileName(NULL, myFileName, MAX_PATH);		// NULL means: the current process
	if (myLength != 0) {
		NativePathNameToFSSpec(myFileName, &gAppFSSpec, kFullNativePath);

		gAppResFile = FSpOpenResFile(&gAppFSSpec, fsRdWrPerm);
		if (gAppResFile != kInvalidFileRefNum)
			UseResFile(gAppResFile);
	}
	
	// do any application-specific initialization that must occur before the frame window is created
	QTApp_Init(kInitAppPhase_BeforeCreateFrameWindow);
	
	// create the main frame window
	myWindowFrame = CreateWindow(gAppName, gAppName, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
                               		CW_USEDEFAULT, 
                               		CW_USEDEFAULT,
                             		CW_USEDEFAULT, 
                             		CW_USEDEFAULT,
                             		NULL, 
                             		NULL, 
                             		hInstance, 
                             		NULL);
	ghWnd = myWindowFrame;
	
	// make sure we got a frame window
	if (myWindowFrame == NULL)
		return(0);
		
	// show the window
	ShowWindow(myWindowFrame, nCmdShow);
	UpdateWindow(myWindowFrame);
	
	// do any application-specific initialization that must occur after the frame window is created
	QTApp_Init(kInitAppPhase_AfterCreateFrameWindow);
	
	// get and process events until the user quits
    while (GetMessage(&myMsg, NULL, 0, 0)) {	
		if (!TranslateMDISysAccel(ghWndMDIClient, &myMsg)) {
        	if (!TranslateAccelerator(myWindowFrame, myAccel, &myMsg)) {
                TranslateMessage(&myMsg);
                DispatchMessage(&myMsg);
			}
		}
    }

	// close the application's resource file, if it was previously opened
	if (gAppResFile != kInvalidFileRefNum)
		CloseResFile(gAppResFile);

	// terminate the QuickTime Media Layer
	ExitMovies();
	TerminateQTML();

	return(myMsg.wParam);			// returns the value from PostQuitMessage
}