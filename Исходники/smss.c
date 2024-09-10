NTSTATUS
_main(IN INT argc,
      IN PCHAR argv[],
      IN PCHAR envp[],
      IN ULONG DebugFlag)
{
    NTSTATUS Status;
    KPRIORITY SetBasePriority;
    ULONG_PTR Parameters[4];
    HANDLE Handles[2];
    PVOID State;
    ULONG Flags;
    PROCESS_BASIC_INFORMATION ProcessInfo;
    UNICODE_STRING DbgString, InitialCommand;

    /* Make us critical */
    RtlSetProcessIsCritical(TRUE, NULL, FALSE);
    RtlSetThreadIsCritical(TRUE, NULL, FALSE);

    /* Raise our priority */
    SetBasePriority = 11;
    Status = NtSetInformationProcess(NtCurrentProcess(),
                                     ProcessBasePriority,
                                     (PVOID)&SetBasePriority,
                                     sizeof(SetBasePriority));
    ASSERT(NT_SUCCESS(Status));

    /* Save the debug flag if it was passed */
    if (DebugFlag) SmpDebug = DebugFlag != 0;

    /* Build the hard error parameters */
    Parameters[0] = (ULONG_PTR)&DbgString;
    Parameters[1] = Parameters[2] = Parameters[3] = 0;

    /* Enter SEH so we can terminate correctly if anything goes wrong */
    _SEH2_TRY
    {
        /* Initialize SMSS */
        Status = SmpInit(&InitialCommand, Handles);
        if (!NT_SUCCESS(Status))
        {
            DPRINT1("SMSS: SmpInit return failure - Status == %x\n", Status);
            RtlInitUnicodeString(&DbgString, L"Session Manager Initialization");
            Parameters[1] = Status;
            _SEH2_LEAVE;
        }

        /* Get the global flags */
        Status = NtQuerySystemInformation(SystemFlagsInformation,
                                          &Flags,
                                          sizeof(Flags),
                                          NULL);
        ASSERT(NT_SUCCESS(Status));

        /* Before executing the initial command check if the debug flag is on */
        if (Flags & (FLG_DEBUG_INITIAL_COMMAND | FLG_DEBUG_INITIAL_COMMAND_EX))
        {
            /* SMSS should launch ntsd with a few parameters at this point */
            DPRINT1("Global Flags Set to SMSS Debugging: Not yet supported\n");
        }

        /* Execute the initial command (Winlogon.exe) */
        Status = SmpExecuteInitialCommand(0, &InitialCommand, &Handles[1], NULL);
        if (!NT_SUCCESS(Status))
        {
            /* Fail and raise a hard error */
            DPRINT1("SMSS: Execute Initial Command failed\n");
            RtlInitUnicodeString(&DbgString,
                                 L"Session Manager ExecuteInitialCommand");
            Parameters[1] = Status;
            _SEH2_LEAVE;
        }

        /*  Check if we're already attached to a session */
        Status = SmpAcquirePrivilege(SE_LOAD_DRIVER_PRIVILEGE, &State);
        if (AttachedSessionId != -1)
        {
            /* Detach from it, we should be in no session right now */
            Status = NtSetSystemInformation(SystemSessionDetach,
                                            &AttachedSessionId,
                                            sizeof(AttachedSessionId));
            ASSERT(NT_SUCCESS(Status));
            AttachedSessionId = -1;
        }
        SmpReleasePrivilege(State);

        /* Wait on either CSRSS or Winlogon to die */
        Status = NtWaitForMultipleObjects(RTL_NUMBER_OF(Handles),
                                          Handles,
                                          WaitAny,
                                          FALSE,
                                          NULL);
        if (Status == STATUS_WAIT_0)
        {
            /* CSRSS is dead, get exit code and prepare for the hard error */
            RtlInitUnicodeString(&DbgString, L"Windows SubSystem");
            Status = NtQueryInformationProcess(Handles[0],
                                               ProcessBasicInformation,
                                               &ProcessInfo,
                                               sizeof(ProcessInfo),
                                               NULL);
            DPRINT1("SMSS: Windows subsystem terminated when it wasn't supposed to.\n");
        }
        else
        {
            /* The initial command is dead or we have another failure */
            RtlInitUnicodeString(&DbgString, L"Windows Logon Process");
            if (Status == STATUS_WAIT_1)
            {
                /* Winlogon.exe got terminated, get its exit code */
                Status = NtQueryInformationProcess(Handles[1],
                                                   ProcessBasicInformation,
                                                   &ProcessInfo,
                                                   sizeof(ProcessInfo),
                                                   NULL);
            }
            else
            {
                /* Something else satisfied our wait, so set the wait status */
                ProcessInfo.ExitStatus = Status;
                Status = STATUS_SUCCESS;
            }
            DPRINT1("SMSS: Initial command '%wZ' terminated when it wasn't supposed to.\n",
                    &InitialCommand);
        }

        /* Check if NtQueryInformationProcess was successful */
        if (NT_SUCCESS(Status))
        {
            /* Then we must have a valid exit status in the structure, use it */
            Parameters[1] = ProcessInfo.ExitStatus;
        }
        else
        {
            /* We really don't know what happened, so set a generic error */
            Parameters[1] = STATUS_UNSUCCESSFUL;
        }
    }
    _SEH2_EXCEPT(SmpUnhandledExceptionFilter(_SEH2_GetExceptionInformation()))
    {
        /* The filter should never return here */
        ASSERT(FALSE);
    }
    _SEH2_END;

    /* Something in the init loop failed, terminate SMSS */
    return SmpTerminate(Parameters, 1, RTL_NUMBER_OF(Parameters));
}