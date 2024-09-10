NTSTATUS PhpWorkQueueThreadStart(
    _In_ PVOID Parameter
    )
{
    PPH_WORK_QUEUE workQueue = (PPH_WORK_QUEUE)Parameter;

    while (TRUE)
    {
        NTSTATUS status;
        HANDLE semaphoreHandle;
        LARGE_INTEGER timeout;
        PPH_WORK_QUEUE_ITEM workQueueItem = NULL;

        // Check if we have more threads than the limit.
        if (workQueue->CurrentThreads > workQueue->MaximumThreads)
        {
            BOOLEAN terminate = FALSE;

            // Lock and re-check.
            PhAcquireQueuedLockExclusive(&workQueue->StateLock);

            // Check the minimum as well.
            if (workQueue->CurrentThreads > workQueue->MaximumThreads &&
                workQueue->CurrentThreads > workQueue->MinimumThreads)
            {
                workQueue->CurrentThreads--;
                terminate = TRUE;
            }

            PhReleaseQueuedLockExclusive(&workQueue->StateLock);

            if (terminate)
                break;
        }

        semaphoreHandle = PhpGetSemaphoreWorkQueue(workQueue);

        if (!workQueue->Terminating)
        {
            // Wait for work.
            status = NtWaitForSingleObject(
                semaphoreHandle,
                FALSE,
                PhTimeoutFromMilliseconds(&timeout, workQueue->NoWorkTimeout)
                );
        }
        else
        {
            status = STATUS_UNSUCCESSFUL;
        }

        if (status == STATUS_WAIT_0 && !workQueue->Terminating)
        {
            PLIST_ENTRY listEntry;

            // Dequeue the work item.

            PhAcquireQueuedLockExclusive(&workQueue->QueueLock);

            listEntry = RemoveHeadList(&workQueue->QueueListHead);

            if (IsListEmpty(&workQueue->QueueListHead))
                PhPulseCondition(&workQueue->QueueEmptyCondition);

            PhReleaseQueuedLockExclusive(&workQueue->QueueLock);

            // Make sure we got work.
            if (listEntry != &workQueue->QueueListHead)
            {
                workQueueItem = CONTAINING_RECORD(listEntry, PH_WORK_QUEUE_ITEM, ListEntry);

                PhpExecuteWorkQueueItem(workQueueItem);
                _InterlockedDecrement(&workQueue->BusyCount);

                PhpDestroyWorkQueueItem(workQueueItem);
            }
        }
        else
        {
            BOOLEAN terminate = FALSE;

            // No work arrived before the timeout passed, or we are terminating, or some error occurred.
            // Terminate the thread.

            PhAcquireQueuedLockExclusive(&workQueue->StateLock);

            if (workQueue->Terminating || workQueue->CurrentThreads > workQueue->MinimumThreads)
            {
                workQueue->CurrentThreads--;
                terminate = TRUE;
            }

            PhReleaseQueuedLockExclusive(&workQueue->StateLock);

            if (terminate)
                break;
        }
    }

    PhReleaseRundownProtection(&workQueue->RundownProtect);

    return STATUS_SUCCESS;
}