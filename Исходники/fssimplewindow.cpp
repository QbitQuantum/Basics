void FsOpenWindow(int x0,int y0,int wid,int hei,int useDoubleBuffer)
{
	if(NULL!=fsWin32Internal.hWnd)
	{
		MessageBoxA(fsWin32Internal.hWnd,"Error! Window already exists.","Error!",MB_OK);
		exit(1);
	}

	// Note 2012/03/08 RegisterClassW and CreateWindowW doesn't seem to work.
	WNDCLASSA wc;
	HINSTANCE inst=GetModuleHandleA(NULL);

	wc.style=CS_OWNDC|CS_BYTEALIGNWINDOW;
	wc.lpfnWndProc=(WNDPROC)WindowFunc;
	wc.cbClsExtra=0;
	wc.cbWndExtra=0;
	wc.hInstance=(HINSTANCE)inst;
	wc.hIcon=LoadIconA(inst,"MAINICON");
	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName=NULL;
	wc.lpszClassName=WINCLASS;
	if(0!=RegisterClassA(&wc))
	{
		doubleBuffer=useDoubleBuffer;


		RECT rc;
		rc.left  =x0;
		rc.top   =y0;
		rc.right =(unsigned long)(x0+wid-1);
		rc.bottom=(unsigned long)(y0+hei-1);
		AdjustWindowRect(&rc,WINSTYLE,FALSE);
		wid  =rc.right-rc.left+1;
		hei  =rc.bottom-rc.top+1;

#ifdef _UNICODE
		// What's the point of using CreateWindowA?  Another weird Microsoft logic here.
		static wchar_t buf[256];
		const char *windowNameA=(const char *)WINNAME;
		for(int i=0; i<255 && 0!=windowNameA[i]; ++i)
		{
			buf[i]=windowNameA[i];
			buf[i+1]=0;
		}
		const char *windowNameUsed=(const char *)buf;
#else
		const char *windowNameUsed=(const char *)WINNAME;
#endif

		fsWin32Internal.hWnd=CreateWindowA(WINCLASS,windowNameUsed,WINSTYLE,x0,y0,wid,hei,NULL,NULL,inst,NULL);
		if(NULL!=fsWin32Internal.hWnd)
		{
			InitializeOpenGL(fsWin32Internal.hWnd);

			ShowWindow(fsWin32Internal.hWnd,SW_SHOWNORMAL);
			UpdateWindow(fsWin32Internal.hWnd);

			FsPassedTime();  // Reset Timer
		}
		else
		{
			printf("Could not open window.\n");
			exit(1);
		}
	}
}