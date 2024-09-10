static
DWORD
WINAPI
Thread1(
    _Inout_opt_ PVOID Parameter)
{
    MSG msg;

    hWndThread1 = CreateWindowExW(0, L"SendTest", NULL, 0,  10, 10, 20, 20,  NULL, NULL, 0, NULL);
    ok(hWndThread1 != NULL, "CreateWindow failed\n");

    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
        if (!(msg.message > WM_USER || IsDWmMsg(msg.message) || IseKeyMsg(msg.message)))
            RECORD_MESSAGE(1, msg.message, POST, 0, 0);
        DispatchMessageA(&msg);
    }

    ResumeThread(hThread2);

    while (MsgWaitForMultipleObjectsEx(1, &hThread2, FALSE, QS_ALLEVENTS, MWMO_ALERTABLE) != WAIT_OBJECT_0)
    {
        while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            if (!(msg.message > WM_USER || IsDWmMsg(msg.message) || IseKeyMsg(msg.message)))
                RECORD_MESSAGE(1, msg.message, POST, 0, 0);
            DispatchMessageA(&msg);
        }
    }

    DestroyWindow(hWndThread1);
    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
        if (!(msg.message > WM_USER || IsDWmMsg(msg.message) || IseKeyMsg(msg.message)))
            RECORD_MESSAGE(1, msg.message, POST, 0, 0);
        DispatchMessageA(&msg);
    }

    return 6;
}