/*++
 * @name CsrSbCreateSession
 *
 * The CsrSbCreateSession API is called by the Session Manager whenever a new
 * session is created.
 *
 * @param ApiMessage
 *        Pointer to the Session Manager API Message.
 *
 * @return TRUE in case of success, FALSE otherwise.
 *
 * @remarks The CsrSbCreateSession routine will initialize a new CSR NT
 *          Session and allocate a new CSR Process for the subsystem process.
 *
 *--*/
BOOLEAN
NTAPI
CsrSbCreateSession(IN PSB_API_MSG ApiMessage)
{
    PSB_CREATE_SESSION_MSG CreateSession = &ApiMessage->CreateSession;
    HANDLE hProcess, hThread;
    PCSR_PROCESS CsrProcess;
    NTSTATUS Status;
    KERNEL_USER_TIMES KernelTimes;
    PCSR_THREAD CsrThread;
    //PVOID ProcessData;
    //ULONG i;

    /* Save the Process and Thread Handles */
    hProcess = CreateSession->ProcessInfo.ProcessHandle;
    hThread = CreateSession->ProcessInfo.ThreadHandle;

    /* Lock the Processes */
    CsrAcquireProcessLock();

    /* Allocate a new process */
    CsrProcess = CsrAllocateProcess();
    if (!CsrProcess)
    {
        /* Fail */
        ApiMessage->ReturnValue = STATUS_NO_MEMORY;
        CsrReleaseProcessLock();
        return TRUE;
    }

    /* Set the exception port */
    Status = NtSetInformationProcess(hProcess,
                                     ProcessExceptionPort,
                                     &CsrApiPort,
                                     sizeof(HANDLE));

    /* Check for success */
    if (!NT_SUCCESS(Status))
    {
        /* Fail the request */
        CsrDeallocateProcess(CsrProcess);
        CsrReleaseProcessLock();

        /* Strange as it seems, NTSTATUSes are actually returned */
        return (BOOLEAN)STATUS_NO_MEMORY;
    }

    /* Get the Create Time */
    Status = NtQueryInformationThread(hThread,
                                      ThreadTimes,
                                      &KernelTimes,
                                      sizeof(KERNEL_USER_TIMES),
                                      NULL);

    /* Check for success */
    if (!NT_SUCCESS(Status))
    {
        /* Fail the request */
        CsrDeallocateProcess(CsrProcess);
        CsrReleaseProcessLock();

        /* Strange as it seems, NTSTATUSes are actually returned */
        return (BOOLEAN)Status;
    }

    /* Allocate a new Thread */
    CsrThread = CsrAllocateThread(CsrProcess);
    if (!CsrThread)
    {
        /* Fail the request */
        CsrDeallocateProcess(CsrProcess);
        CsrReleaseProcessLock();

        ApiMessage->ReturnValue = STATUS_NO_MEMORY;
        return TRUE;
    }

    /* Setup the Thread Object */
    CsrThread->CreateTime = KernelTimes.CreateTime;
    CsrThread->ClientId = CreateSession->ProcessInfo.ClientId;
    CsrThread->ThreadHandle = hThread;
    ProtectHandle(hThread);
    CsrThread->Flags = 0;

    /* Insert it into the Process List */
    CsrInsertThread(CsrProcess, CsrThread);

    /* Setup Process Data */
    CsrProcess->ClientId = CreateSession->ProcessInfo.ClientId;
    CsrProcess->ProcessHandle = hProcess;
    CsrProcess->NtSession = CsrAllocateNtSession(CreateSession->SessionId);

    /* Set the Process Priority */
    CsrSetBackgroundPriority(CsrProcess);
#if 0
    /* Get the first data location */
    ProcessData = &CsrProcess->ServerData[CSR_SERVER_DLL_MAX];

    /* Loop every DLL */
    for (i = 0; i < CSR_SERVER_DLL_MAX; i++)
    {
        /* Check if the DLL is loaded and has Process Data */
        if (CsrLoadedServerDll[i] && CsrLoadedServerDll[i]->SizeOfProcessData)
        {
            /* Write the pointer to the data */
            CsrProcess->ServerData[i] = ProcessData;

            /* Move to the next data location */
            ProcessData = (PVOID)((ULONG_PTR)ProcessData +
                                  CsrLoadedServerDll[i]->SizeOfProcessData);
        }
        else
        {
            /* Nothing for this Process */
            CsrProcess->ServerData[i] = NULL;
        }
    }
#else
    /* HACKZ: should go in BaseSrv part of CreateCallback done in Insert below */
    RtlInitializeCriticalSection(&CsrProcess->HandleTableLock);
#endif
    /* Insert the Process */
    CsrInsertProcess(NULL, NULL, CsrProcess);

    /* Activate the Thread */
    ApiMessage->ReturnValue = NtResumeThread(hThread, NULL);

    /* Release lock and return */
    CsrReleaseProcessLock();
    return TRUE;
}