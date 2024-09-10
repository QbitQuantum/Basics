/*++
 * @name CsrCreateProcess
 * @implemented NT4
 *
 * The CsrCreateProcess routine creates a CSR Process object for an NT Process.
 *
 * @param hProcess
 *        Handle to an existing NT Process to which to associate this
 *        CSR Process.
 *
 * @param hThread
 *        Handle to an existing NT Thread to which to create its
 *        corresponding CSR Thread for this CSR Process.
 *
 * @param ClientId
 *        Pointer to the Client ID structure of the NT Process to associate
 *        with this CSR Process.
 *
 * @param NtSession
 * @param Flags
 * @param DebugCid
 *
 * @return STATUS_SUCCESS in case of success, STATUS_UNSUCCESSFUL otherwise.
 *
 * @remarks None.
 *
 *--*/
NTSTATUS
NTAPI
CsrCreateProcess(IN HANDLE hProcess,
                 IN HANDLE hThread,
                 IN PCLIENT_ID ClientId,
                 IN PCSR_NT_SESSION NtSession,
                 IN ULONG Flags,
                 IN PCLIENT_ID DebugCid)
{
    PCSR_THREAD CurrentThread = CsrGetClientThread();
    CLIENT_ID CurrentCid;
    PCSR_PROCESS CurrentProcess;
    PCSR_SERVER_DLL ServerDll;
    PVOID ProcessData;
    ULONG i;
    PCSR_PROCESS CsrProcess;
    NTSTATUS Status;
    PCSR_THREAD CsrThread;
    KERNEL_USER_TIMES KernelTimes;

    /* Get the current CID and lock Processes */
    CurrentCid = CurrentThread->ClientId;
    CsrAcquireProcessLock();

    /* Get the current CSR Thread */
    CurrentThread = CsrLocateThreadByClientId(&CurrentProcess, &CurrentCid);
    if (!CurrentThread)
    {
        /* We've failed to locate the thread */
        CsrReleaseProcessLock();
        return STATUS_THREAD_IS_TERMINATING;
    }

    /* Allocate a new Process Object */
    CsrProcess = CsrAllocateProcess();
    if (!CsrProcess)
    {
        /* Couldn't allocate Process */
        CsrReleaseProcessLock();
        return STATUS_NO_MEMORY;
    }

    /* Inherit the Process Data */
    CurrentProcess = CurrentThread->Process;
    ProcessData = &CsrProcess->ServerData[CSR_SERVER_DLL_MAX];
    for (i = 0; i < CSR_SERVER_DLL_MAX; i++)
    {
        /* Get the current Server */
        ServerDll = CsrLoadedServerDll[i];

        /* Check if the DLL is Loaded and has Per Process Data */
        if (ServerDll && ServerDll->SizeOfProcessData)
        {
            /* Set the pointer */
            CsrProcess->ServerData[i] = ProcessData;

            /* Copy the Data */
            RtlMoveMemory(ProcessData,
                          CurrentProcess->ServerData[i],
                          ServerDll->SizeOfProcessData);

            /* Update next data pointer */
            ProcessData = (PVOID)((ULONG_PTR)ProcessData +
                                  ServerDll->SizeOfProcessData);
        }
        else
        {
            /* No data for this Server */
            CsrProcess->ServerData[i] = NULL;
        }
    }

    /* Set the Exception Port for us */
    Status = NtSetInformationProcess(hProcess,
                                     ProcessExceptionPort,
                                     &CsrApiPort,
                                     sizeof(CsrApiPort));
    if (!NT_SUCCESS(Status))
    {
        /* Failed */
        CsrDeallocateProcess(CsrProcess);
        CsrReleaseProcessLock();
        return STATUS_NO_MEMORY;
    }

    /* Check if CreateProcess got CREATE_NEW_PROCESS_GROUP */
    if (Flags & CsrProcessCreateNewGroup)
    {
        /*
         * We create the process group leader of a new process group, therefore
         * its process group ID and sequence number are its own ones.
         */
        CsrProcess->ProcessGroupId = HandleToUlong(ClientId->UniqueProcess);
        CsrProcess->ProcessGroupSequence = CsrProcess->SequenceNumber;
    }
    else
    {
        /* Inherit the process group ID and sequence number from the current process */
        CsrProcess->ProcessGroupId = CurrentProcess->ProcessGroupId;
        CsrProcess->ProcessGroupSequence = CurrentProcess->ProcessGroupSequence;
    }

    /* Check if this is a console process */
    if (Flags & CsrProcessIsConsoleApp) CsrProcess->Flags |= CsrProcessIsConsoleApp;

    /* Mask out non-debug flags */
    Flags &= ~(CsrProcessIsConsoleApp | CsrProcessCreateNewGroup | CsrProcessPriorityFlags);

    /* Check if every process will be debugged */
    if (!(Flags) && (CurrentProcess->DebugFlags & CsrDebugProcessChildren))
    {
        /* Pass it on to the current process */
        CsrProcess->DebugFlags = CsrDebugProcessChildren;
        CsrProcess->DebugCid = CurrentProcess->DebugCid;
    }

    /* Check if Debugging was used on this process */
    if ((Flags & (CsrDebugOnlyThisProcess | CsrDebugProcessChildren)) && (DebugCid))
    {
        /* Save the debug flag used */
        CsrProcess->DebugFlags = Flags;

        /* Save the CID */
        CsrProcess->DebugCid = *DebugCid;
    }

    /* Check if Debugging is enabled */
    if (CsrProcess->DebugFlags)
    {
        /* Set the Debug Port for us */
        Status = NtSetInformationProcess(hProcess,
                                         ProcessDebugPort,
                                         &CsrApiPort,
                                         sizeof(CsrApiPort));
        ASSERT(NT_SUCCESS(Status));
        if (!NT_SUCCESS(Status))
        {
            /* Failed */
            CsrDeallocateProcess(CsrProcess);
            CsrReleaseProcessLock();
            return STATUS_NO_MEMORY;
        }
    }

    /* Get the Thread Create Time */
    Status = NtQueryInformationThread(hThread,
                                      ThreadTimes,
                                      &KernelTimes,
                                      sizeof(KernelTimes),
                                      NULL);
    if (!NT_SUCCESS(Status))
    {
        /* Failed */
        CsrDeallocateProcess(CsrProcess);
        CsrReleaseProcessLock();
        return STATUS_NO_MEMORY;
    }

    /* Allocate a CSR Thread Structure */
    CsrThread = CsrAllocateThread(CsrProcess);
    if (!CsrThread)
    {
        /* Failed */
        CsrDeallocateProcess(CsrProcess);
        CsrReleaseProcessLock();
        return STATUS_NO_MEMORY;
    }

    /* Save the data we have */
    CsrThread->CreateTime = KernelTimes.CreateTime;
    CsrThread->ClientId = *ClientId;
    CsrThread->ThreadHandle = hThread;
    ProtectHandle(hThread);
    CsrThread->Flags = 0;

    /* Insert the Thread into the Process */
    Status = CsrInsertThread(CsrProcess, CsrThread);
    if (!NT_SUCCESS(Status))
    {
        /* Bail out */
        CsrDeallocateProcess(CsrProcess);
        CsrDeallocateThread(CsrThread);
        CsrReleaseProcessLock();
        return Status;
    }

    /* Reference the session */
    CsrReferenceNtSession(NtSession);
    CsrProcess->NtSession = NtSession;

    /* Setup Process Data */
    CsrProcess->ClientId = *ClientId;
    CsrProcess->ProcessHandle = hProcess;
    CsrProcess->ShutdownLevel = 0x280;

    /* Set the Priority to Background */
    CsrSetBackgroundPriority(CsrProcess);

    /* Insert the Process */
    CsrInsertProcess(CurrentProcess, CsrProcess);

    /* Release lock and return */
    CsrReleaseProcessLock();
    return Status;
}