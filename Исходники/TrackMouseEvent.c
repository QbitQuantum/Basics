static void create_test_windows()
{
    hMouseHookLL = SetWindowsHookExW(WH_MOUSE_LL, MouseLLHookProc, GetModuleHandleW( NULL ), 0);
    hMouseHook = SetWindowsHookExW(WH_MOUSE, MouseHookProc, GetModuleHandleW( NULL ), GetCurrentThreadId());
    ok(hMouseHook!=NULL,"failed to set hook\n");
    ok(hMouseHookLL!=NULL,"failed to set hook\n");
    
    RegisterSimpleClass(TmeTestProc, L"testClass");

    hWnd1 = CreateWindowW(L"testClass", L"test", WS_OVERLAPPEDWINDOW,
                         100, 100, 500, 500, NULL, NULL, 0, NULL);
    hWnd2 = CreateWindowW(L"testClass", L"test", WS_CHILD,
                         50, 50, 200, 200, hWnd1, NULL, 0, NULL);
    hWnd3 = CreateWindowW(L"testClass", L"test", WS_CHILD,
                         150, 150, 200, 200, hWnd1, NULL, 0, NULL);

    ShowWindow(hWnd1, SW_SHOW);
    UpdateWindow(hWnd1);
    ShowWindow(hWnd2, SW_SHOW);
    UpdateWindow(hWnd2);
    ShowWindow(hWnd3, SW_SHOWNORMAL);
    UpdateWindow(hWnd3);
    //SetWindowPos (hWnd3, HWND_TOP, 0,0,0,0, SWP_NOMOVE|SWP_NOREDRAW);
}