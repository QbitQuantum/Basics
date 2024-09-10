VOID PhpThreadProviderUpdate(
    __in PPH_THREAD_PROVIDER ThreadProvider,
    __in PVOID ProcessInformation
    )
{
    PPH_THREAD_PROVIDER threadProvider = ThreadProvider;
    PSYSTEM_PROCESS_INFORMATION process;
    SYSTEM_PROCESS_INFORMATION localProcess;
    PSYSTEM_THREAD_INFORMATION threads;
    ULONG numberOfThreads;
    ULONG i;

    process = PhFindProcessInformation(ProcessInformation, threadProvider->ProcessId);

    if (!process)
    {
        // The process doesn't exist anymore. Pretend it does but
        // has no threads.
        process = &localProcess;
        process->NumberOfThreads = 0;
    }

    threads = process->Threads;
    numberOfThreads = process->NumberOfThreads;

    // System Idle Process has one thread per CPU.
    // They all have a TID of 0, but we can't have
    // multiple TIDs, so we'll assign unique TIDs.
    if (threadProvider->ProcessId == SYSTEM_IDLE_PROCESS_ID)
    {
        for (i = 0; i < numberOfThreads; i++)
        {
            threads[i].ClientId.UniqueThread = (HANDLE)i;
        }
    }

    // Look for dead threads.
    {
        PPH_LIST threadsToRemove = NULL;
        ULONG enumerationKey = 0;
        PPH_THREAD_ITEM *threadItem;

        while (PhEnumHashtable(threadProvider->ThreadHashtable, (PPVOID)&threadItem, &enumerationKey))
        {
            BOOLEAN found = FALSE;

            // Check if the thread still exists.
            for (i = 0; i < numberOfThreads; i++)
            {
                PSYSTEM_THREAD_INFORMATION thread = &threads[i];

                if ((*threadItem)->ThreadId == thread->ClientId.UniqueThread)
                {
                    found = TRUE;
                    break;
                }
            }

            if (!found)
            {
                // Raise the thread removed event.
                PhInvokeCallback(&threadProvider->ThreadRemovedEvent, *threadItem);

                if (!threadsToRemove)
                    threadsToRemove = PhCreateList(2);

                PhAddItemList(threadsToRemove, *threadItem);
            }
        }

        if (threadsToRemove)
        {
            PhAcquireFastLockExclusive(&threadProvider->ThreadHashtableLock);

            for (i = 0; i < threadsToRemove->Count; i++)
            {
                PhpRemoveThreadItem(
                    threadProvider,
                    (PPH_THREAD_ITEM)threadsToRemove->Items[i]
                    );
            }

            PhReleaseFastLockExclusive(&threadProvider->ThreadHashtableLock);
            PhDereferenceObject(threadsToRemove);
        }
    }

    // Go through the queued thread query data.
    {
        PSLIST_ENTRY entry;
        PPH_THREAD_QUERY_DATA data;

        entry = RtlInterlockedFlushSList(&threadProvider->QueryListHead);

        while (entry)
        {
            data = CONTAINING_RECORD(entry, PH_THREAD_QUERY_DATA, ListEntry);
            entry = entry->Next;

            if (data->StartAddressResolveLevel == PhsrlFunction && data->StartAddressString)
            {
                PhSwapReference(&data->ThreadItem->StartAddressString, data->StartAddressString);
                data->ThreadItem->StartAddressResolveLevel = data->StartAddressResolveLevel;
            }

            PhSwapReference2(&data->ThreadItem->ServiceName, data->ServiceName);

            data->ThreadItem->JustResolved = TRUE;

            if (data->StartAddressString) PhDereferenceObject(data->StartAddressString);
            PhDereferenceObject(data->ThreadItem);
            PhFree(data);
        }
    }

    // Look for new threads and update existing ones.
    for (i = 0; i < numberOfThreads; i++)
    {
        PSYSTEM_THREAD_INFORMATION thread = &threads[i];
        PPH_THREAD_ITEM threadItem;

        threadItem = PhReferenceThreadItem(threadProvider, thread->ClientId.UniqueThread);

        if (!threadItem)
        {
            ULONG64 cycles;
            PVOID startAddress = NULL;

            threadItem = PhCreateThreadItem(thread->ClientId.UniqueThread);

            threadItem->CreateTime = thread->CreateTime;
            threadItem->KernelTime = thread->KernelTime;
            threadItem->UserTime = thread->UserTime;

            PhUpdateDelta(&threadItem->ContextSwitchesDelta, thread->ContextSwitches);
            threadItem->Priority = thread->Priority;
            threadItem->BasePriority = thread->BasePriority;
            threadItem->State = (KTHREAD_STATE)thread->ThreadState;
            threadItem->WaitReason = thread->WaitReason;

            // Try to open a handle to the thread.
            if (!NT_SUCCESS(PhOpenThread(
                &threadItem->ThreadHandle,
                THREAD_QUERY_INFORMATION,
                threadItem->ThreadId
                )))
            {
                PhOpenThread(
                    &threadItem->ThreadHandle,
                    ThreadQueryAccess,
                    threadItem->ThreadId
                    );
            }

            // Get the cycle count.
            if (NT_SUCCESS(PhpGetThreadCycleTime(
                threadProvider,
                threadItem,
                &cycles
                )))
            {
                PhUpdateDelta(&threadItem->CyclesDelta, cycles);
            }

            // Initialize the CPU time deltas.
            PhUpdateDelta(&threadItem->CpuKernelDelta, threadItem->KernelTime.QuadPart);
            PhUpdateDelta(&threadItem->CpuUserDelta, threadItem->UserTime.QuadPart);

            // Try to get the start address.

            if (threadItem->ThreadHandle)
            {
                NtQueryInformationThread(
                    threadItem->ThreadHandle,
                    ThreadQuerySetWin32StartAddress,
                    &startAddress,
                    sizeof(PVOID),
                    NULL
                    );
            }

            if (!startAddress)
                startAddress = thread->StartAddress;

            threadItem->StartAddress = (ULONG64)startAddress;

            // Get the Win32 priority.
            threadItem->PriorityWin32 = GetThreadPriority(threadItem->ThreadHandle);

            if (PhTestEvent(&threadProvider->SymbolsLoadedEvent))
            {
                threadItem->StartAddressString = PhpGetThreadBasicStartAddress(
                    threadProvider,
                    threadItem->StartAddress,
                    &threadItem->StartAddressResolveLevel
                    );
            }

            if (!threadItem->StartAddressString)
            {
                threadItem->StartAddressResolveLevel = PhsrlAddress;
                threadItem->StartAddressString = PhCreateStringEx(NULL, PH_PTR_STR_LEN * 2);
                PhPrintPointer(
                    threadItem->StartAddressString->Buffer,
                    (PVOID)threadItem->StartAddress
                    );
                PhTrimToNullTerminatorString(threadItem->StartAddressString);
            }

            PhpQueueThreadQuery(threadProvider, threadItem);

            // Is it a GUI thread?

            if (threadItem->ThreadHandle && KphIsConnected())
            {
                PVOID win32Thread;

                if (NT_SUCCESS(KphQueryInformationThread(
                    threadItem->ThreadHandle,
                    KphThreadWin32Thread,
                    &win32Thread,
                    sizeof(PVOID),
                    NULL
                    )))
                {
                    threadItem->IsGuiThread = win32Thread != NULL;
                }
            }

            // Add the thread item to the hashtable.
            PhAcquireFastLockExclusive(&threadProvider->ThreadHashtableLock);
            PhAddEntryHashtable(threadProvider->ThreadHashtable, &threadItem);
            PhReleaseFastLockExclusive(&threadProvider->ThreadHashtableLock);

            // Raise the thread added event.
            PhInvokeCallback(&threadProvider->ThreadAddedEvent, threadItem);
        }
        else
        {
            BOOLEAN modified = FALSE;

            if (threadItem->JustResolved)
                modified = TRUE;

            threadItem->KernelTime = thread->KernelTime;
            threadItem->UserTime = thread->UserTime;

            threadItem->Priority = thread->Priority;
            threadItem->BasePriority = thread->BasePriority;

            threadItem->State = (KTHREAD_STATE)thread->ThreadState;

            if (threadItem->WaitReason != thread->WaitReason)
            {
                threadItem->WaitReason = thread->WaitReason;
                modified = TRUE;
            }

            // If the resolve level is only at address, it probably
            // means symbols weren't loaded the last time we
            // tried to get the start address. Try again.
            if (threadItem->StartAddressResolveLevel == PhsrlAddress)
            {
                if (PhTestEvent(&threadProvider->SymbolsLoadedEvent))
                {
                    PPH_STRING newStartAddressString;

                    newStartAddressString = PhpGetThreadBasicStartAddress(
                        threadProvider,
                        threadItem->StartAddress,
                        &threadItem->StartAddressResolveLevel
                        );

                    PhSwapReference2(
                        &threadItem->StartAddressString,
                        newStartAddressString
                        );

                    modified = TRUE;
                }
            }

            // If we couldn't resolve the start address to a
            // module+offset, use the StartAddress instead
            // of the Win32StartAddress and try again.
            // Note that we check the resolve level again
            // because we may have changed it in the previous
            // block.
            if (
                threadItem->JustResolved &&
                threadItem->StartAddressResolveLevel == PhsrlAddress
                )
            {
                if (threadItem->StartAddress != (ULONG64)thread->StartAddress)
                {
                    threadItem->StartAddress = (ULONG64)thread->StartAddress;
                    PhpQueueThreadQuery(threadProvider, threadItem);
                }
            }

            // Update the context switch count.
            {
                ULONG oldDelta;

                oldDelta = threadItem->ContextSwitchesDelta.Delta;
                PhUpdateDelta(&threadItem->ContextSwitchesDelta, thread->ContextSwitches);

                if (threadItem->ContextSwitchesDelta.Delta != oldDelta)
                {
                    modified = TRUE;
                }
            }

            // Update the cycle count.
            {
                ULONG64 cycles;
                ULONG64 oldDelta;

                oldDelta = threadItem->CyclesDelta.Delta;

                if (NT_SUCCESS(PhpGetThreadCycleTime(
                    threadProvider,
                    threadItem,
                    &cycles
                    )))
                {
                    PhUpdateDelta(&threadItem->CyclesDelta, cycles);

                    if (threadItem->CyclesDelta.Delta != oldDelta)
                    {
                        modified = TRUE;
                    }
                }
            }

            // Update the CPU time deltas.
            PhUpdateDelta(&threadItem->CpuKernelDelta, threadItem->KernelTime.QuadPart);
            PhUpdateDelta(&threadItem->CpuUserDelta, threadItem->UserTime.QuadPart);

            // Update the CPU usage.
            // If the cycle time isn't available, we'll fall back to using the CPU time.
            if (PhEnableCycleCpuUsage && (threadProvider->ProcessId == SYSTEM_IDLE_PROCESS_ID || threadItem->ThreadHandle))
            {
                threadItem->CpuUsage = (FLOAT)threadItem->CyclesDelta.Delta / PhCpuTotalCycleDelta;
            }
            else
            {
                threadItem->CpuUsage = (FLOAT)(threadItem->CpuKernelDelta.Delta + threadItem->CpuUserDelta.Delta) /
                    (PhCpuKernelDelta.Delta + PhCpuUserDelta.Delta + PhCpuIdleDelta.Delta);
            }

            // Update the Win32 priority.
            {
                LONG oldPriorityWin32 = threadItem->PriorityWin32;

                threadItem->PriorityWin32 = GetThreadPriority(threadItem->ThreadHandle);

                if (threadItem->PriorityWin32 != oldPriorityWin32)
                {
                    modified = TRUE;
                }
            }

            // Update the GUI thread status.

            if (threadItem->ThreadHandle && KphIsConnected())
            {
                PVOID win32Thread;

                if (NT_SUCCESS(KphQueryInformationThread(
                    threadItem->ThreadHandle,
                    KphThreadWin32Thread,
                    &win32Thread,
                    sizeof(PVOID),
                    NULL
                    )))
                {
                    BOOLEAN oldIsGuiThread = threadItem->IsGuiThread;

                    threadItem->IsGuiThread = win32Thread != NULL;

                    if (threadItem->IsGuiThread != oldIsGuiThread)
                        modified = TRUE;
                }
            }

            threadItem->JustResolved = FALSE;

            if (modified)
            {
                // Raise the thread modified event.
                PhInvokeCallback(&threadProvider->ThreadModifiedEvent, threadItem);
            }

            PhDereferenceObject(threadItem);
        }
    }

    PhInvokeCallback(&threadProvider->UpdatedEvent, NULL);
    threadProvider->RunId++;
}