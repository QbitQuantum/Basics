void Test_GetKeyState()
{
	HWND hwnd;
    MSG msg;
	
	hwnd = CreateTestWindow();
	
	hKbdHook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, GetModuleHandleA( NULL ), 0);
	hKbdLLHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandleA( NULL ), 0);
	
	ok(hKbdHook!=NULL," \n");
	ok(hKbdLLHook!=NULL," \n");
	
	keybd_event(VK_LMENU, 0, 0,0);
	
	while (PeekMessage( &msg, 0, 0, 0, PM_REMOVE )) DispatchMessageA( &msg );
	
	keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP,0);
	
	//fixme this hangs the test
    //while (PeekMessage( &msg, 0, 0, 0, PM_REMOVE|PM_NOYIELD )) DispatchMessageA( &msg );
	
	DestroyWindow(hwnd);
	
    while (PeekMessage( &msg, 0, 0, 0, PM_REMOVE )) DispatchMessageA( &msg );
	
	UnhookWindowsHookEx (hKbdHook);
	UnhookWindowsHookEx (hKbdLLHook);	
}