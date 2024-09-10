int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow )
{
    MSG				msg;

	if( !initApplication(hInstance) ) return FALSE;

	HANDLE hMutex = CreateMutex(NULL,NULL,className);
	if(ERROR_ALREADY_EXISTS == GetLastError())return FALSE;

	HANDLE	hAccel = LoadAccelerators( hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR) );

	CoInitialize(NULL);
	readProfile();
	if( !OpenPackFile() ) return FALSE;
	if( !InitInstance(hInstance,nCmdShow) ) return FALSE;
	SystemInit();
	WINNLSEnableIME(sysInf.hWnd,FALSE);
	TIMECAPS tc;
	timeGetDevCaps(&tc,sizeof(tc));
	timeBeginPeriod(tc.wPeriodMin);

	while(FALSE==sysInf.bGameEnd){
		BOOL bGotMsg;

		if(sysInf.bIsActive || lpMovie || lpStaffRoll){
			bGotMsg = PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE);
		}else{
            bGotMsg = GetMessage( &msg, NULL, 0U, 0U );
		}
		if(bGotMsg){
			if(TranslateAccelerator( sysInf.hWnd, (HACCEL)hAccel, &msg ))continue;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if(sysInf.bIsActive || sysInf.execMode==movie_mode || lpStaffRoll){
			mainLoop();
		}
	}
	WINNLSEnableIME(sysInf.hWnd,TRUE);
	timeEndPeriod(tc.wPeriodMin);
	writeProfile();

	cleanup();
	CoUninitialize();
	CloseHandle(hMutex);
	if(CheckWinExec()){
		WinExec2( str_winpath, str_winexec );
	}
	return msg.wParam;
} // WinMain