static int vboxTrayServiceMain(void)
{
    int rc = VINF_SUCCESS;
    Log(("VBoxTray: Entering vboxTrayServiceMain\n"));

    ghStopSem = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (ghStopSem == NULL)
    {
        rc = RTErrConvertFromWin32(GetLastError());
        Log(("VBoxTray: CreateEvent for stopping VBoxTray failed, rc=%Rrc\n", rc));
    }
    else
    {
        /*
         * Start services listed in the vboxServiceTable.
         */
        VBOXSERVICEENV svcEnv;
        svcEnv.hInstance = ghInstance;
        svcEnv.hDriver   = ghVBoxDriver;

        /* Initializes disp-if to default (XPDM) mode. */
        VBoxDispIfInit(&svcEnv.dispIf); /* Cannot fail atm. */
    #ifdef VBOX_WITH_WDDM
        /*
         * For now the display mode will be adjusted to WDDM mode if needed
         * on display service initialization when it detects the display driver type.
         */
    #endif

        /* Finally start all the built-in services! */
        rc = vboxTrayStartServices(&svcEnv, vboxServiceTable);
        if (RT_FAILURE(rc))
        {
            /* Terminate service if something went wrong. */
            vboxTrayStopServices(&svcEnv, vboxServiceTable);
        }
        else
        {
            rc = vboxTrayCreateTrayIcon();
            if (   RT_SUCCESS(rc)
                && gMajorVersion >= 5) /* Only for W2K and up ... */
            {
                /* We're ready to create the tooltip balloon.
                   Check in 10 seconds (@todo make seconds configurable) ... */
                SetTimer(ghwndToolWindow,
                         TIMERID_VBOXTRAY_CHECK_HOSTVERSION,
                         10 * 1000, /* 10 seconds */
                         NULL       /* No timerproc */);
            }

            if (RT_SUCCESS(rc))
            {
                /* Do the Shared Folders auto-mounting stuff. */
                rc = VBoxSharedFoldersAutoMount();
                if (RT_SUCCESS(rc))
                {
                    /* Report the host that we're up and running! */
                    hlpReportStatus(VBoxGuestFacilityStatus_Active);
                }
            }

            if (RT_SUCCESS(rc))
            {
                /* Boost thread priority to make sure we wake up early for seamless window notifications
                 * (not sure if it actually makes any difference though). */
                SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

                /*
                 * Main execution loop
                 * Wait for the stop semaphore to be posted or a window event to arrive
                 */

                DWORD dwEventCount = 2;
                HANDLE hWaitEvent[2] = { ghStopSem, ghSeamlessNotifyEvent };

                if (0 == ghSeamlessNotifyEvent) /* If seamless mode is not active / supported, reduce event array count. */
                    dwEventCount = 1;

                Log(("VBoxTray: Number of events to wait in main loop: %ld\n", dwEventCount));
                while (true)
                {
                    DWORD waitResult = MsgWaitForMultipleObjectsEx(dwEventCount, hWaitEvent, 500, QS_ALLINPUT, 0);
                    waitResult = waitResult - WAIT_OBJECT_0;

                    /* Only enable for message debugging, lots of traffic! */
                    //Log(("VBoxTray: Wait result  = %ld\n", waitResult));

                    if (waitResult == 0)
                    {
                        Log(("VBoxTray: Event 'Exit' triggered\n"));
                        /* exit */
                        break;
                    }
                    else if (   waitResult == 1
                             && ghSeamlessNotifyEvent != 0) /* Only jump in, if seamless is active! */
                    {
                        Log(("VBoxTray: Event 'Seamless' triggered\n"));

                        /* seamless window notification */
                        VBoxSeamlessCheckWindows();
                    }
                    else
                    {
                        /* timeout or a window message, handle it */
                        MSG msg;
                        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
                        {
                            Log(("VBoxTray: msg %p\n", msg.message));
                            if (msg.message == WM_QUIT)
                            {
                                Log(("VBoxTray: WM_QUIT!\n"));
                                SetEvent(ghStopSem);
                                continue;
                            }
                            TranslateMessage(&msg);
                            DispatchMessage(&msg);
                        }
                    }
                }
                Log(("VBoxTray: Returned from main loop, exiting ...\n"));
            }
            Log(("VBoxTray: Waiting for services to stop ...\n"));
            vboxTrayStopServices(&svcEnv, vboxServiceTable);
        } /* Services started */
        CloseHandle(ghStopSem);
    } /* Stop event created */

    vboxTrayRemoveTrayIcon();

    Log(("VBoxTray: Leaving vboxTrayServiceMain with rc=%Rrc\n", rc));
    return rc;
}