VOID
SetThreadFields(
    PSYSTEM_THREAD_INFORMATION ThreadInfo,
    HWND hwnd
    )
{
    TIME_FIELDS UserTime;
    TIME_FIELDS KernelTime;
    TIME_FIELDS RunTime;
    LARGE_INTEGER Time;
    CHAR TimeString[15];
    CHAR StartString[32];
    HANDLE hThread;
    CONTEXT ThreadContext;
    NTSTATUS Status;
    OBJECT_ATTRIBUTES Obja;
    ULONG PcValue;

    //
    // Display the selected thread information
    //

    //
    // Compute runtimes
    //

    RtlTimeToTimeFields ( &ThreadInfo->UserTime, &UserTime);
    RtlTimeToTimeFields ( &ThreadInfo->KernelTime, &KernelTime);

    RtlTimeToTimeFields ( &ThreadInfo->UserTime, &UserTime);
    RtlTimeToTimeFields ( &ThreadInfo->KernelTime, &KernelTime);
    Time.QuadPart = RefreshTimeOfDayInfo.CurrentTime.QuadPart - ThreadInfo->CreateTime.QuadPart;
    RtlTimeToTimeFields ( &Time, &RunTime);
    wsprintf(TimeString,"%3ld:%02ld:%02ld.%03ld",
                RunTime.Hour,
                RunTime.Minute,
                RunTime.Second,
                RunTime.Milliseconds
                );
    SetDlgItemText(
        hwnd,
        PXPLODE_THREADELAPSED_TIME,
        TimeString
        );

    wsprintf(TimeString,"%3ld:%02ld:%02ld.%03ld",
                UserTime.Hour,
                UserTime.Minute,
                UserTime.Second,
                UserTime.Milliseconds
                );
    SetDlgItemText(
        hwnd,
        PXPLODE_THREADUSER_TIME,
        TimeString
        );

    wsprintf(TimeString,"%3ld:%02ld:%02ld.%03ld",
                KernelTime.Hour,
                KernelTime.Minute,
                KernelTime.Second,
                KernelTime.Milliseconds
                );
    SetDlgItemText(
        hwnd,
        PXPLODE_THREADKERNEL_TIME,
        TimeString
        );

    wsprintf(StartString,"0x%08lx",
                ThreadInfo->StartAddress
                );
    SetDlgItemText(
        hwnd,
        PXPLODE_THREAD_START,
        StartString
        );

    //
    // Do the priority Group
    //

    SetDlgItemInt(
        hwnd,
        PXPLODE_THREAD_DYNAMIC,
        ThreadInfo->Priority,
        FALSE
        );
    switch ( ThreadInfo->BasePriority - DlgProcessInfo->BasePriority ) {

        case 2:
            CheckRadioButton(
                hwnd,
                PXPLODE_THREAD_HIGHEST,
                PXPLODE_THREAD_LOWEST,
                PXPLODE_THREAD_HIGHEST
                );
            break;

        case 1:
            CheckRadioButton(
                hwnd,
                PXPLODE_THREAD_HIGHEST,
                PXPLODE_THREAD_LOWEST,
                PXPLODE_THREAD_ABOVE
                );
            break;

        case -1:
            CheckRadioButton(
                hwnd,
                PXPLODE_THREAD_HIGHEST,
                PXPLODE_THREAD_LOWEST,
                PXPLODE_THREAD_BELOW
                );
            break;
        case -2:
            CheckRadioButton(
                hwnd,
                PXPLODE_THREAD_HIGHEST,
                PXPLODE_THREAD_LOWEST,
                PXPLODE_THREAD_LOWEST
                );
            break;
        case 0:
        default:
            CheckRadioButton(
                hwnd,
                PXPLODE_THREAD_HIGHEST,
                PXPLODE_THREAD_LOWEST,
                PXPLODE_THREAD_NORMAL
                );
            break;
        }
    //
    // Complete thread information
    //

    SetDlgItemInt(
        hwnd,
        PXPLODE_THREAD_SWITCHES,
        ThreadInfo->ContextSwitches,
        FALSE
        );

    PcValue = 0;
    InitializeObjectAttributes(&Obja, NULL, 0, NULL, NULL);
    Status = NtOpenThread(
                &hThread,
                THREAD_GET_CONTEXT,
                &Obja,
                &ThreadInfo->ClientId
                );
    if ( NT_SUCCESS(Status) ) {
        ThreadContext.ContextFlags = CONTEXT_CONTROL;
        Status = NtGetContextThread(hThread,&ThreadContext);
        NtClose(hThread);
        if ( NT_SUCCESS(Status) ) {
            PcValue = (ULONG) CONTEXT_TO_PROGRAM_COUNTER(&ThreadContext);
            }
        }
    if ( PcValue ) {
        wsprintf(StartString,"0x%08lx",
                    PcValue
                    );
        SetDlgItemText(
            hwnd,
            PXPLODE_THREAD_PC,
            StartString
            );
        }
    else {
        SetDlgItemText(
            hwnd,
            PXPLODE_THREAD_PC,
            "Unknown"
            );
        }


    //
    // Disable the thread buttons if we can't get at the thread or it's token
    //

    {
        HANDLE Thread;
        HANDLE Token;
        BOOL ThreadOK = FALSE;
        BOOL GotToken = FALSE;

        Thread = OpenThread(MAXIMUM_ALLOWED, FALSE, (DWORD)ThreadInfo->ClientId.UniqueThread);
        if (Thread != NULL) {

            ThreadOK = TRUE;

            if (OpenThreadToken(Thread, MAXIMUM_ALLOWED, TRUE, &Token)) {
                GotToken = TRUE;
                CloseHandle(Token);
            }
            CloseHandle(Thread);
        }

        EnableWindow(GetDlgItem(hwnd, PXPLODE_THREAD_ACL), ThreadOK);

        EnableWindow(GetDlgItem(hwnd, PXPLODE_THREAD_TOKEN), GotToken);
        EnableWindow(GetDlgItem(hwnd, PXPLODE_THREAD_TOKEN_ACL), GotToken);
    }
}