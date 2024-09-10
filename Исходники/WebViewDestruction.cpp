static void runMessagePump(DWORD timeoutMilliseconds)
{
    DWORD startTickCount = GetTickCount();
    MSG msg;
    BOOL result;
    while ((result = PeekMessageW(&msg, 0, 0, 0, PM_REMOVE)) && GetTickCount() - startTickCount <= timeoutMilliseconds) {
        if (result == -1)
            break;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}