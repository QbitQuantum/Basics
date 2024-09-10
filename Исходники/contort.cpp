int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, int iCmdShow)
{

	STARTUPINFO si;
    PROCESS_INFORMATION pi;

	


	WCHAR combinedOptions[2048];
	HWND hWnd;
	HDC hDC;
	HGLRC hRC;
	
	MSG msg;
	BOOL quit = FALSE;


	LPWSTR *szArgList;
    int argCount;

	LPWSTR pathToEmulator = NULL;
	LPWSTR pathToRom = NULL;
	LPWSTR cmdLineOptions = NULL;

	bool splitScreen = false;

	GLuint texID;


    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );	


    szArgList = CommandLineToArgvW(GetCommandLine(), &argCount);


	for(int i = 0; i < argCount; i++)
	{
		LPWSTR s = szArgList[i];

		if(wcsstr( s, TEXT("--emupath=")) > 0)
		{
			pathToEmulator = wcsstr( s, TEXT("="))+1;
			continue;
		}

		if(wcsstr( s, TEXT("--rompath=")) > 0)
		{
			pathToRom = wcsstr( s, TEXT("="))+1;
			continue;
		}

		if(wcsstr( s, TEXT("--options=")) > 0)
		{
			cmdLineOptions = wcsstr( s, TEXT("="))+1;
			continue;
		}

	}

	if(pathToEmulator == NULL)
	{
		exit(1);
	}

	wsprintf(combinedOptions, TEXT("\"%s\" \"%s\" %s"), pathToEmulator, pathToRom, cmdLineOptions);

	


	
	RegisterWindowClass(hInstance);

	hWnd = CreateWindowEx(
		WS_EX_TOPMOST|WS_EX_TOOLWINDOW , 
		TEXT("GLSample"), 
		TEXT("OpenGL Sample"), 
		
		 WS_POPUP|WS_VISIBLE|WS_SYSMENU,
		0, 0, 512, 512,
		NULL, NULL, hInstance, NULL );

	SetWindowLong(hWnd, GWL_EXSTYLE,
    GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT); 

	
	
	
	// enable OpenGL for the window
	EnableOpenGL( hWnd, &hDC, &hRC );

	SetLayeredWindowAttributes(hWnd, 0,255, LWA_ALPHA);


	// init openGL

	glEnable(GL_TEXTURE_2D);

	glDisable(GL_DEPTH_TEST| GL_LIGHTING | GL_CULL_FACE);

	glGenTextures(1, &texID);

	if(!CreateProcess(NULL, 
			combinedOptions,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi))
	{
		DWORD error = GetLastError();
		exit(error);
	}

	

	while(EnumWindows(EnumWindowsProc, pi.dwThreadId))
		Sleep(100);


	// program main loop
	while ( !quit )
	{
		if(GetAsyncKeyState( VK_ESCAPE) < 0)
		{
			SendMessage(clientHwnd, WM_CLOSE, 0,0);
				break;
		}
		

		// check the child process

		DWORD exCode;

		if(!GetExitCodeProcess(pi.hProcess, &exCode) || exCode != STILL_ACTIVE)
		{
			break;
		}

		
		// check for messages
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE )  )
		{
			
			// handle or dispatch messages
			if ( msg.message == WM_QUIT ) 
			{
				quit = TRUE;
			} 
			else 
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
			
		} 
		else 
		{
			Draw(clientHwnd, texID);

			SwapBuffers( hDC );

			UpdateGLWindow(hWnd);
			
		}
		
	}
	
	// shutdown OpenGL
	DisableOpenGL( hWnd, hDC, hRC );
	
	// destroy the window explicitly
	DestroyWindow( hWnd );
	
	return msg.wParam;
	
}