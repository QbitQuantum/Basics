/*++
 * @name ExpCreateWorkerThread
 *
 *     The ExpCreateWorkerThread routine creates a new worker thread for the
 *     specified queue.
 **
 * @param QueueType
 *        Type of the queue to use for this thread. Valid values are:
 *          - DelayedWorkQueue
 *          - CriticalWorkQueue
 *          - HyperCriticalWorkQueue
 *
 * @param Dynamic
 *        Specifies whether or not this thread is a dynamic thread.
 *
 * @return None.
 *
 * @remarks HyperCritical work threads run at priority 7; Critical work threads
 *          run at priority 5, and delayed work threads run at priority 4.
 *
 *          This, worker threads cannot pre-empty a normal user-mode thread.
 *
 *--*/
VOID
NTAPI
ExpCreateWorkerThread(WORK_QUEUE_TYPE WorkQueueType,
                      IN BOOLEAN Dynamic)
{
    PETHREAD Thread;
    HANDLE hThread;
    ULONG Context;
    KPRIORITY Priority;

    /* Check if this is going to be a dynamic thread */
    Context = WorkQueueType;

    /* Add the dynamic mask */
    if (Dynamic) Context |= EX_DYNAMIC_WORK_THREAD;

    /* Create the System Thread */
    PsCreateSystemThread(&hThread,
                         THREAD_ALL_ACCESS,
                         NULL,
                         NULL,
                         NULL,
                         ExpWorkerThreadEntryPoint,
                         UlongToPtr(Context));

    /* If the thread is dynamic */
    if (Dynamic)
    {
        /* Increase the count */
        InterlockedIncrement(&ExWorkerQueue[WorkQueueType].DynamicThreadCount);
    }

    /* Set the priority */
    if (WorkQueueType == DelayedWorkQueue)
    {
        /* Priority == 4 */
        Priority = EX_DELAYED_QUEUE_PRIORITY_INCREMENT;
    }
    else if (WorkQueueType == CriticalWorkQueue)
    {
        /* Priority == 5 */
        Priority = EX_CRITICAL_QUEUE_PRIORITY_INCREMENT;
    }
    else
    {
        /* Priority == 7 */
        Priority = EX_HYPERCRITICAL_QUEUE_PRIORITY_INCREMENT;
    }

    /* Get the Thread */
    ObReferenceObjectByHandle(hThread,
                              THREAD_SET_INFORMATION,
                              PsThreadType,
                              KernelMode,
                              (PVOID*)&Thread,
                              NULL);

    /* Set the Priority */
    KeSetBasePriorityThread(&Thread->Tcb, Priority);

    /* Dereference and close handle */
    ObDereferenceObject(Thread);
    ObCloseHandle(hThread, KernelMode);
}