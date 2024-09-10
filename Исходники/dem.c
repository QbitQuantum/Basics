static VOID WINAPI DosStart(LPWORD Stack)
{
    BOOLEAN Success;
    DWORD Result;
#ifndef STANDALONE
    INT i;
#endif

    DPRINT("DosStart\n");

    /*
     * We succeeded, deregister the DOS Starting BOP
     * so that no app will be able to call us back.
     */
    RegisterBop(BOP_START_DOS, NULL);

    /* Initialize the callback context */
    InitializeContext(&DosContext, BIOS_CODE_SEGMENT, 0x0010);

    Success  = DosBIOSInitialize();
//  Success &= DosKRNLInitialize();
    if (!Success)
    {
        BiosDisplayMessage("DOS32 loading failed (Error: %u). The VDM will shut down.\n", GetLastError());
        EmulatorTerminate();
        return;
    }

    /* Load the mouse driver */
    DosMouseInitialize();

#ifndef STANDALONE

    /* Parse the command line arguments */
    for (i = 1; i < NtVdmArgc; i++)
    {
        if (wcsncmp(NtVdmArgv[i], L"-i", 2) == 0)
        {
            /* This is the session ID (hex format) */
            SessionId = wcstoul(NtVdmArgv[i] + 2, NULL, 16);
        }
    }

    /* Initialize Win32-VDM environment */
    Env = RtlAllocateHeap(RtlGetProcessHeap(), HEAP_ZERO_MEMORY, EnvSize);
    if (Env == NULL)
    {
        DosDisplayMessage("Failed to initialize the global environment (Error: %u). The VDM will shut down.\n", GetLastError());
        EmulatorTerminate();
        return;
    }

    /* Clear the structure */
    RtlZeroMemory(&CommandInfo, sizeof(CommandInfo));

    /* Get the initial information */
    CommandInfo.TaskId = SessionId;
    CommandInfo.VDMState = VDM_GET_FIRST_COMMAND | VDM_FLAG_DOS;
    GetNextVDMCommand(&CommandInfo);

#else

    /* Retrieve the command to start */
    if (NtVdmArgc >= 2)
    {
        WideCharToMultiByte(CP_ACP, 0, NtVdmArgv[1], -1, AppName, sizeof(AppName), NULL, NULL);

        if (NtVdmArgc >= 3)
            WideCharToMultiByte(CP_ACP, 0, NtVdmArgv[2], -1, CmdLine, sizeof(CmdLine), NULL, NULL);
        else
            strcpy(CmdLine, "");
    }
    else
    {
        DosDisplayMessage("Invalid DOS command line\n");
        EmulatorTerminate();
        return;
    }

#endif

    /*
     * At this point, CS:IP points to the DOS BIOS exit code. If the
     * root command interpreter fails to start (or if it exits), DOS
     * exits and the VDM terminates.
     */

    /* Start the root command interpreter */
    // TODO: Really interpret the 'SHELL=' line of CONFIG.NT, and use it!

    /*
     * Prepare the stack for DosStartComSpec:
     * push Flags, CS and IP, and an extra WORD.
     */
    setSP(getSP() - sizeof(WORD));
    *((LPWORD)SEG_OFF_TO_PTR(getSS(), getSP())) = (WORD)getEFLAGS();
    setSP(getSP() - sizeof(WORD));
    *((LPWORD)SEG_OFF_TO_PTR(getSS(), getSP())) = getCS();
    setSP(getSP() - sizeof(WORD));
    *((LPWORD)SEG_OFF_TO_PTR(getSS(), getSP())) = getIP();
    setSP(getSP() - sizeof(WORD));

    Result = DosStartComSpec(TRUE, SEG_OFF_TO_PTR(SYSTEM_ENV_BLOCK, 0),
                             MAKELONG(getIP(), getCS()),
#ifndef STANDALONE
                             &RootCmd.ComSpecPsp
#else
                             NULL
#endif
                             );
    if (Result != ERROR_SUCCESS)
    {
        /* Unprepare the stack for DosStartComSpec */
        setSP(getSP() + 4*sizeof(WORD));

        DosDisplayMessage("Failed to start the Command Interpreter (Error: %u). The VDM will shut down.\n", Result);
        EmulatorTerminate();
        return;
    }

#ifndef STANDALONE
    RootCmd.Terminated = FALSE;
    InsertComSpecInfo(&RootCmd);
#endif

    /**/
    /* Attach to the console and resume the VM */
    DosProcessConsoleAttach();
    EmulatorResume();
    /**/

    return;
}