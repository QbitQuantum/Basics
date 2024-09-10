static PPH_PROCESS_ITEM PhpCreateProcessItemForHiddenProcess(
    _In_ PPH_HIDDEN_PROCESS_ENTRY Entry
    )
{
    NTSTATUS status;
    PPH_PROCESS_ITEM processItem;
    PPH_PROCESS_ITEM idleProcessItem;
    HANDLE processHandle;
    PROCESS_BASIC_INFORMATION basicInfo;
    KERNEL_USER_TIMES times;
    PROCESS_PRIORITY_CLASS priorityClass;
    ULONG handleCount;
    HANDLE processHandle2;

    if (Entry->Type == NormalProcess)
    {
        processItem = PhReferenceProcessItem(Entry->ProcessId);

        if (processItem)
            return processItem;
    }

    processItem = PhCreateProcessItem(Entry->ProcessId);

    // Mark the process as terminated if necessary.
    if (Entry->Type == TerminatedProcess)
        processItem->State |= PH_PROCESS_ITEM_REMOVED;

    // We need a process record. Just use the record of System Idle Process.
    if (idleProcessItem = PhReferenceProcessItem(SYSTEM_IDLE_PROCESS_ID))
    {
        processItem->Record = idleProcessItem->Record;
        PhReferenceProcessRecord(processItem->Record);
    }
    else
    {
        PhDereferenceObject(processItem);
        return NULL;
    }

    // Set up the file name and process name.

    PhSwapReference(&processItem->FileName, Entry->FileName);

    if (processItem->FileName)
    {
        processItem->ProcessName = PhGetBaseName(processItem->FileName);
    }
    else
    {
        processItem->ProcessName = PhCreateString(L"Unknown");
    }

    if (ProcessesMethod == BruteForceScanMethod)
    {
        status = PhOpenProcess(
            &processHandle,
            ProcessQueryAccess,
            Entry->ProcessId
            );
    }
    else
    {
        status = PhOpenProcessByCsrHandles(
            &processHandle,
            ProcessQueryAccess,
            Entry->ProcessId
            );
    }

    if (NT_SUCCESS(status))
    {
        // Basic information and not-so-dynamic information

        processItem->QueryHandle = processHandle;

        if (NT_SUCCESS(PhGetProcessBasicInformation(processHandle, &basicInfo)))
        {
            processItem->ParentProcessId = basicInfo.InheritedFromUniqueProcessId;
            processItem->BasePriority = basicInfo.BasePriority;
        }

        PhGetProcessSessionId(processHandle, &processItem->SessionId);

        PhPrintUInt32(processItem->ParentProcessIdString, HandleToUlong(processItem->ParentProcessId));
        PhPrintUInt32(processItem->SessionIdString, processItem->SessionId);

        if (NT_SUCCESS(PhGetProcessTimes(processHandle, &times)))
        {
            processItem->CreateTime = times.CreateTime;
            processItem->KernelTime = times.KernelTime;
            processItem->UserTime = times.UserTime;
        }

        // TODO: Token information?

        if (NT_SUCCESS(NtQueryInformationProcess(
            processHandle,
            ProcessPriorityClass,
            &priorityClass,
            sizeof(PROCESS_PRIORITY_CLASS),
            NULL
            )))
        {
            processItem->PriorityClass = priorityClass.PriorityClass;
        }

        if (NT_SUCCESS(NtQueryInformationProcess(
            processHandle,
            ProcessHandleCount,
            &handleCount,
            sizeof(ULONG),
            NULL
            )))
        {
            processItem->NumberOfHandles = handleCount;
        }
    }

    // Stage 1
    // Some copy and paste magic here...

    if (processItem->FileName)
    {
        // Small icon, large icon.
        ExtractIconEx(
            processItem->FileName->Buffer,
            0,
            &processItem->LargeIcon,
            &processItem->SmallIcon,
            1
            );

        // Version info.
        PhInitializeImageVersionInfo(&processItem->VersionInfo, processItem->FileName->Buffer);
    }

    // Use the default EXE icon if we didn't get the file's icon.
    {
        if (!processItem->SmallIcon || !processItem->LargeIcon)
        {
            if (processItem->SmallIcon)
            {
                DestroyIcon(processItem->SmallIcon);
                processItem->SmallIcon = NULL;
            }
            else if (processItem->LargeIcon)
            {
                DestroyIcon(processItem->LargeIcon);
                processItem->LargeIcon = NULL;
            }

            PhGetStockApplicationIcon(&processItem->SmallIcon, &processItem->LargeIcon);
            processItem->SmallIcon = DuplicateIcon(NULL, processItem->SmallIcon);
            processItem->LargeIcon = DuplicateIcon(NULL, processItem->LargeIcon);
        }
    }

    // POSIX, command line

    status = PhOpenProcess(
        &processHandle2,
        ProcessQueryAccess | PROCESS_VM_READ,
        Entry->ProcessId
        );

    if (NT_SUCCESS(status))
    {
        BOOLEAN isPosix = FALSE;
        PPH_STRING commandLine;
        ULONG i;

        status = PhGetProcessIsPosix(processHandle2, &isPosix);
        processItem->IsPosix = isPosix;

        if (!NT_SUCCESS(status) || !isPosix)
        {
            status = PhGetProcessCommandLine(processHandle2, &commandLine);

            if (NT_SUCCESS(status))
            {
                // Some command lines (e.g. from taskeng.exe) have nulls in them.
                // Since Windows can't display them, we'll replace them with
                // spaces.
                for (i = 0; i < (ULONG)commandLine->Length / 2; i++)
                {
                    if (commandLine->Buffer[i] == 0)
                        commandLine->Buffer[i] = ' ';
                }
            }
        }
        else
        {
            // Get the POSIX command line.
            status = PhGetProcessPosixCommandLine(processHandle2, &commandLine);
        }

        if (NT_SUCCESS(status))
        {
            processItem->CommandLine = commandLine;
        }

        NtClose(processHandle2);
    }

    // TODO: Other stage 1 tasks.

    PhSetEvent(&processItem->Stage1Event);

    return processItem;
}