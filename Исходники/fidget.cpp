WPARAM CFidgetApp::Run(void)
{
    HACCEL hAccelTable = LoadAccelerators(m_hInstance, (LPCTSTR)IDC_FIDGET);

    // Main message loop:
    //
    WPARAM iReturn = 0;
    bool bFinished = false;
    while (!bFinished)
    {
        CLinearTimeAbsolute ltaCurrent;
        ltaCurrent.GetUTC();

        // Execute background tasks at specifically scheduled times.
        //
        scheduler.RunTasks(ltaCurrent);
        CLinearTimeAbsolute ltaWakeUp;
        if (!scheduler.WhenNext(&ltaWakeUp))
        {
            ltaWakeUp = ltaCurrent + time_30m;
        }
        else if (ltaWakeUp < ltaCurrent)
        {
            // This is necessary to deal with computer time jumping backwards
            // which can happen when someone sets or resets the computer clock.
            //
            ltaWakeUp = ltaCurrent;
        }

        CLinearTimeDelta ltdTimeOut = ltaWakeUp - ltaCurrent;
        DWORD dwTimeout = ltdTimeOut.ReturnMilliseconds();

        DWORD nHandles = 0;
        DWORD dwObject = MsgWaitForMultipleObjectsEx(nHandles, NULL, dwTimeout, QS_ALLINPUT, 0);
        if (WAIT_OBJECT_0 + nHandles == dwObject)
        {
            for (; !bFinished;)
            {
                // There is at least one new message waiting to be processed.
                //
                MSG msg;
                BOOL bGM = GetMessage(&msg, NULL, 0, 0);
                if (0 == bGM)
                {
                    // WM_QUIT message was received. It is time to terminate
                    // ourselves.
                    //
                    iReturn = msg.wParam;
                    bFinished = true;
                }
                else if (-1 == bGM)
                {
                    // An unexpected problem occured.
                    //
                    bFinished = true;
                }
                else
                {
                    // Translate and dispatch message to Windows Procedure.
                    //
                    if (  (  NULL == m_hwndNewSession
                          || !IsDialogMessage(m_hwndNewSession, &msg))
                       && (  NULL == m_hwndAbout
                          || !IsDialogMessage(m_hwndAbout, &msg))
                       && !TranslateMDISysAccel(g_theApp.m_pMainFrame->m_pMDIControl->m_hwnd, &msg)
                       && !TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
                    {
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                    }
                }

                // We must process all messages in the queue before making
                // another MsgWaitForMultipleObjectsEx() call.
                //
                if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE|PM_NOYIELD))
                {
                    break;
                }
            }
        }
        else if (WAIT_TIMEOUT != dwObject)
        {
            // An unexpected event occured.
            //
            bFinished = true;
        }

        // It's time to perform some background task.
        //
    }
    DestroyAcceleratorTable(hAccelTable);
    return iReturn;
}