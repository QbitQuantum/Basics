void KGWin32App::Run()
{
    m_bLoop = TRUE;

    SetTimerFrame(1000);

    while (m_bLoop) 
    {
        DWORD dwResult = MsgWaitForMultipleObjectsEx(EVENT_TOTAL, m_Events, INFINITE, QS_ALLEVENTS, 0);
        switch (dwResult - WAIT_OBJECT_0) 
        {
        case EVENT_TIMER:
            if (m_bEnabled)
                m_bLoop = OnLoop();
            break;
        case EVENT_RENDER:
            OnPaint();
            break;
        case EVENT_TOTAL: 
            {
                MSG msg;
                while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
                {
                    if (msg.message == WM_QUIT) 
                    {
                        OnMsgProc(WM_QUIT, 0, 0);
                        m_bLoop = FALSE;
                    }
                    else
                    {
                        TranslateMessage(&msg);

                        if (m_hwndEmbedWebPage != NULL && m_hWnd != msg.hwnd && 
                            msg.message >= WM_KEYFIRST && msg.message <= WM_KEYLAST)
                        {
                            SendMessage(m_hwndEmbedWebPage, msg.message, msg.wParam, msg.lParam);
                        }

                        DispatchMessage(&msg);
                    }
                }
                break;
            }
        }
    }

    Exit();
}