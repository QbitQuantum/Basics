/// <summary>
/// Window message loop
/// </summary>
/// <returns>wParam of last received message</returns>
WPARAM KinectWindow::MessageLoop()
{
    m_hStopStreamEventThread = CreateEventW(nullptr, TRUE, FALSE, nullptr);

    HANDLE hEventThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)StreamEventThread, this, 0, nullptr);

    MSG  msg = {0};
    BOOL ret;
    while (0 != (ret = GetMessageW(&msg, nullptr, 0, 0)))
    {
        if (-1 == ret)
        {
            break;
        }

        if (IsDialogMessageW(m_hWnd, &msg))
        {
            continue;
        }

        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    WaitForSingleObject(hEventThread, INFINITE);
    CloseHandle(hEventThread);

    return msg.wParam;
}