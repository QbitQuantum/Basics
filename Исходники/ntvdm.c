INT
wmain(INT argc, WCHAR *argv[])
{
#ifdef STANDALONE

    if (argc < 2)
    {
        wprintf(L"\nReactOS Virtual DOS Machine\n\n"
                L"Usage: NTVDM <executable> [<parameters>]\n");
        return 0;
    }

#else

    INT i;
    WCHAR *endptr;

    /* Parse the command line arguments */
    for (i = 1; i < argc; i++)
    {
        if (wcsncmp(argv[i], L"-i", 2) == 0)
        {
            /* This is the session ID */
            SessionId = wcstoul(argv[i] + 2, &endptr, 10);

            /* The VDM hasn't been started from a console, so quit when the task is done */
            AcceptCommands = FALSE;
        }
    }

#endif

    NtVdmArgc = argc;
    NtVdmArgv = argv;

    DPRINT1("\n\n\nNTVDM - Starting...\n\n\n");

    /* Create the task event */
    VdmTaskEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    ASSERT(VdmTaskEvent != NULL);

    /* Initialize the console */
    if (!ConsoleInit())
    {
        wprintf(L"FATAL: A problem occurred when trying to initialize the console\n");
        goto Cleanup;
    }

    /* Initialize the emulator */
    if (!EmulatorInitialize(ConsoleInput, ConsoleOutput))
    {
        wprintf(L"FATAL: Failed to initialize the emulator\n");
        goto Cleanup;
    }

    /* Initialize the system BIOS */
    if (!BiosInitialize(NULL))
    {
        wprintf(L"FATAL: Failed to initialize the VDM BIOS.\n");
        goto Cleanup;
    }

    /* Let's go! Start simulation */
    CpuSimulate();

Cleanup:
    BiosCleanup();
    EmulatorCleanup();
    ConsoleCleanup();

#ifndef STANDALONE
    ExitVDM(FALSE, 0);
#endif

    /* Quit the VDM */
    DPRINT1("\n\n\nNTVDM - Exiting...\n\n\n");

    return 0;
}