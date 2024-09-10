// FIXME: Maybe return a NTSTATUS
static BOOL
GuiInit(IN PCONSOLE_INIT_INFO ConsoleInitInfo,
        IN HANDLE ConsoleLeaderProcessHandle,
        IN OUT PGUI_INIT_INFO GuiInitInfo)
{
    BOOL Success = TRUE;
    UNICODE_STRING DesktopPath;
    DESKTOP_CONSOLE_THREAD DesktopConsoleThreadInfo;
    HWINSTA hWinSta;
    HDESK hDesk;

    NTSTATUS Status;
    HANDLE hInputThread;
    CLIENT_ID ClientId;

    /*
     * Initialize and register the console window class, if needed.
     */
    if (!ConsInitialized)
    {
        if (!RegisterConWndClass(ConSrvDllInstance)) return FALSE;
        ConsInitialized = TRUE;
    }

    /*
     * Set-up the console input thread. We have
     * one console input thread per desktop.
     */

    if (!CsrImpersonateClient(NULL))
        // return STATUS_BAD_IMPERSONATION_LEVEL;
        return FALSE;

    if (ConsoleInitInfo->DesktopLength)
    {
        DesktopPath.MaximumLength = ConsoleInitInfo->DesktopLength;
        DesktopPath.Length = DesktopPath.MaximumLength - sizeof(UNICODE_NULL);
        DesktopPath.Buffer = ConsoleInitInfo->Desktop;
    }
    else
    {
        RtlInitUnicodeString(&DesktopPath, L"Default");
    }

    hDesk = NtUserResolveDesktop(ConsoleLeaderProcessHandle,
                                 &DesktopPath,
                                 0,
                                 &hWinSta);
    DPRINT("NtUserResolveDesktop(DesktopPath = '%wZ') returned hDesk = 0x%p; hWinSta = 0x%p\n",
           &DesktopPath, hDesk, hWinSta);

    CsrRevertToSelf();

    if (hDesk == NULL) return FALSE;

    /*
     * We need to see whether we need to create a
     * new console input thread for this desktop.
     */
    DesktopConsoleThreadInfo.DesktopHandle = hDesk;
    DesktopConsoleThreadInfo.ThreadId = (ULONG_PTR)INVALID_HANDLE_VALUE; // Special value to say we just want to retrieve the thread ID.
    NtUserConsoleControl(ConsoleCtrlDesktopConsoleThread,
                         &DesktopConsoleThreadInfo,
                         sizeof(DesktopConsoleThreadInfo));
    DPRINT("NtUserConsoleControl returned ThreadId = 0x%p\n", DesktopConsoleThreadInfo.ThreadId);

    /*
     * Save the opened window station and desktop handles in the initialization
     * structure. They will be used later on, and released, by the GUI frontend.
     */
    GuiInitInfo->WinSta  = hWinSta;
    GuiInitInfo->Desktop = hDesk;

    /* Here GuiInitInfo contains original handles */

    /* If we already have a console input thread on this desktop... */
    if (DesktopConsoleThreadInfo.ThreadId != 0)
    {
        /* ... just use it... */
        DPRINT("Using input thread InputThreadId = 0x%p\n", DesktopConsoleThreadInfo.ThreadId);
        GuiInitInfo->InputThreadId = DesktopConsoleThreadInfo.ThreadId;
        goto Quit;
    }

    /* ... otherwise create a new one. */

    /* Initialize a startup event for the thread to signal it */
    Status = NtCreateEvent(&GuiInitInfo->GuiThreadStartupEvent, EVENT_ALL_ACCESS,
                           NULL, SynchronizationEvent, FALSE);
    if (!NT_SUCCESS(Status))
    {
        Success = FALSE;
        goto Quit;
    }

    /*
     * Duplicate the desktop handle for the console input thread internal needs.
     * If it happens to need also a window station handle in the future, then
     * it is there that you also need to duplicate the window station handle!
     *
     * Note also that we are going to temporarily overwrite the stored handles
     * in GuiInitInfo because it happens that we use also this structure to give
     * the duplicated handles to the input thread that is going to initialize.
     * After the input thread finishes its initialization, we restore the handles
     * in GuiInitInfo to their old values.
     */
    Status = NtDuplicateObject(NtCurrentProcess(),
                               hDesk,
                               NtCurrentProcess(),
                               (PHANDLE)&GuiInitInfo->Desktop,
                               0, 0, DUPLICATE_SAME_ACCESS);
    if (!NT_SUCCESS(Status))
    {
        Success = FALSE;
        goto Quit;
    }

    /* Here GuiInitInfo contains duplicated handles */

    Status = RtlCreateUserThread(NtCurrentProcess(),
                                 NULL,
                                 TRUE, // Start the thread in suspended state
                                 0,
                                 0,
                                 0,
                                 (PVOID)GuiConsoleInputThread,
                                 (PVOID)GuiInitInfo,
                                 &hInputThread,
                                 &ClientId);
    if (NT_SUCCESS(Status))
    {
        /* Add it as a static server thread and resume it */
        CsrAddStaticServerThread(hInputThread, &ClientId, 0);
        Status = NtResumeThread(hInputThread, NULL);
    }
    DPRINT("Thread creation hInputThread = 0x%p, InputThreadId = 0x%p, Status = 0x%08lx\n",
           hInputThread, ClientId.UniqueThread, Status);

    if (!NT_SUCCESS(Status) || hInputThread == NULL)
    {
        /* Close the thread's handle */
        if (hInputThread) NtClose(hInputThread);

        /* We need to close here the duplicated desktop handle */
        CloseDesktop(GuiInitInfo->Desktop); // NtUserCloseDesktop

        /* Close the startup event and bail out */
        NtClose(GuiInitInfo->GuiThreadStartupEvent);

        DPRINT1("CONSRV: Failed to create graphics console thread.\n");
        Success = FALSE;
        goto Quit;
    }

    /* No need to close hInputThread, this is done by CSR automatically */

    /* Wait for the thread to finish its initialization, and close the startup event */
    NtWaitForSingleObject(GuiInitInfo->GuiThreadStartupEvent, FALSE, NULL);
    NtClose(GuiInitInfo->GuiThreadStartupEvent);

    /*
     * Save the input thread ID for later use, and restore the original handles.
     * The copies are held by the console input thread.
     */
    GuiInitInfo->InputThreadId = (ULONG_PTR)ClientId.UniqueThread;
    GuiInitInfo->WinSta  = hWinSta;
    GuiInitInfo->Desktop = hDesk;

    /* Here GuiInitInfo contains again original handles */

Quit:
    if (!Success)
    {
        /*
         * Close the original handles. Do not use the copies in GuiInitInfo
         * because we may have failed in the middle of the duplicate operation
         * and the handles stored in GuiInitInfo may have changed.
         */
        CloseDesktop(hDesk); // NtUserCloseDesktop
        CloseWindowStation(hWinSta); // NtUserCloseWindowStation
    }

    return Success;
}