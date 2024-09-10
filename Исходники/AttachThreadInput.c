BOOLEAN InitThreads()
{
    /* Create a LL hook that drops any physical keyboard and mouse action
       and prevent the user from interfering with the test results */
    if(!IsDebuggerPresent())
    {
        hMouseHookLL = SetWindowsHookExW(WH_MOUSE_LL, MouseLLHookProc, GetModuleHandleW( NULL ), 0);
        ok(hMouseHookLL!=NULL,"failed to set hook\n");
        hKbdHookLL = SetWindowsHookExW(WH_KEYBOARD_LL, KbdLLHookProc, GetModuleHandleW( NULL ), 0);
        ok(hKbdHookLL!=NULL,"failed to set hook\n");
    }

    /* create test clases */
    RegisterSimpleClass(TestProc, L"TestClass");

    memset(&data[0], 0, sizeof(data[0]));

    data[0].tid = GetCurrentThreadId();

    /* create test window */
    data[0].hWnd = CreateWindowW(L"TestClass", L"test", WS_OVERLAPPEDWINDOW,
                                 100, 100, 500, 500, NULL, NULL, 0, NULL);
    if(!data[0].hWnd)
    {
        win_skip("CreateWindowW failed\n");
        return FALSE;
    }   

    /* create thread1(same desktop) */
    if(!CreateTestThread(1, NULL)) return FALSE;

    /* create thread2(same desktop) */
    if(!CreateTestThread(2, NULL)) return FALSE;

    /* ugly ros hack to bypass desktop crapiness */
    if(!CreateTestThread(6, L"ThreadTestDesktop")) return FALSE;

    /* create thread3(different desktop) */
    if(!CreateTestThread(3, L"ThreadTestDesktop")) return FALSE;

    /* create thread4(different desktop) */
    if(!CreateTestThread(4, L"ThreadTestDesktop")) return FALSE;

    return TRUE;
}