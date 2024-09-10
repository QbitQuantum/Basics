/* NOTES:
 *   For Win16, programmers generally use WINAPI WinMain(...) but WINAPI is defined in such a way
 *   that it always makes the function prolog return FAR. Unfortunately, when Watcom C's runtime
 *   calls this function in a memory model that's compact or small, the call is made as if NEAR,
 *   not FAR. To avoid a GPF or crash on return, we must simply declare it PASCAL instead. */
int PASCAL WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow) {
	WNDCLASS wnd;
	MSG msg;

	myInstance = hInstance;

#if TARGET_MSDOS == 16 && TARGET_WINDOWS < 31 /* Windows 3.0 or older (any version capable of real-mode) */
    /* our data segment is discardable.
     * in Windows 3.0 real mode that means our data segment can disappear out from under us.
     * unfortunately I don't know how to call the data segment back in.
     * so we have to compensate by locking our data segment in place. */
    LockData();
#endif

	/* FIXME: Windows 3.0 Real Mode: Why are we unable to load our own Application Icon? */
	AppIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_APPICON));
	if (!AppIcon) MessageBox(NULL,"Unable to load app icon","Oops!",MB_OK);

#ifdef WIN16_NEEDS_MAKEPROCINSTANCE
	WndProc_MPI = MakeProcInstance((FARPROC)WndProc,hInstance);
#endif

	/* NTS: In the Windows 3.1 environment all handles are global. Registering a class window twice won't work.
	 *      It's only under 95 and later (win32 environment) where Windows always sets hPrevInstance to 0
	 *      and window classes are per-application.
	 *
	 *      Windows 3.1 allows you to directly specify the FAR pointer. Windows 3.0 however demands you
	 *      MakeProcInstance it to create a 'thunk' so that Windows can call you (ick). */
	if (!hPrevInstance) {
		wnd.style = CS_HREDRAW|CS_VREDRAW;
#ifdef WIN16_NEEDS_MAKEPROCINSTANCE
		wnd.lpfnWndProc = (WNDPROC)WndProc_MPI;
#else
		wnd.lpfnWndProc = WndProc;
#endif
		wnd.cbClsExtra = 0;
		wnd.cbWndExtra = 0;
		wnd.hInstance = hInstance;
		wnd.hIcon = AppIcon;
		wnd.hCursor = NULL;
		wnd.hbrBackground = NULL;
		wnd.lpszMenuName = NULL;
		wnd.lpszClassName = WndProcClass;

		if (!RegisterClass(&wnd)) {
			MessageBox(NULL,"Unable to register Window class","Oops!",MB_OK);
			return 1;
		}
	}

	HelloMsg();

	hwndMain = CreateWindow(WndProcClass,"Hello!",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,
		300,200,
		NULL,NULL,
		hInstance,NULL);
	if (!hwndMain) {
		MessageBox(NULL,"Unable to create window","Oops!",MB_OK);
		return 1;
	}

	ShowWindow(hwndMain,nCmdShow);
	UpdateWindow(hwndMain); /* FIXME: For some reason this only causes WM_PAINT to print gibberish and cause a GPF. Why? And apparently, Windows 3.0 repaints our window anyway! */

	while (GetMessage(&msg,NULL,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

#if TARGET_MSDOS == 16
    /* Win16 only:
     * If we are the owner (the first instance that registered the window class),
     * then we must reside in memory until we are the last instance resident.
     * If we do not do this, then if multiple instances are open and the user closes US
     * before closing the others, the others will crash (having pulled the code segment
     * behind the window class out from the other processes). */
	if (!hPrevInstance) {
        while (GetModuleUsage(hInstance) > 1) {
            PeekMessage(&msg,NULL,0,0,PM_REMOVE);
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
#endif

	return msg.wParam;
}