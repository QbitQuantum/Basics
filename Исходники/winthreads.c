HANDLE tMPI_Thread_create_NUMA(LPSECURITY_ATTRIBUTES lpThreadAttributes,
                               SIZE_T dwStackSize,
                               LPTHREAD_START_ROUTINE lpStartAddress,
                               LPVOID lpParameter,
                               DWORD dwCreationFlags,
                               LPDWORD lpThreadId)
{
    LPPROC_THREAD_ATTRIBUTE_LIST pAttributeList = NULL;
    HANDLE hThread = NULL;
    SIZE_T cbAttributeList = 0;
    GROUP_AFFINITY GroupAffinity;
    PROCESSOR_NUMBER IdealProcessorNumber;
    ULONG CurrentProcessorIndex;

    /* for each thread created, round-robin through the set of valid 
       processors and affinity masks.
       the assumption is that callers of tMPI_Thread_create_NUMA are creating 
       threads that saturate a given processor.
       for cases where threads are being created that rarely do work, standard 
       thread creation (eg: CreateThread) should be invoked instead.
    */

    CurrentProcessorIndex = (ULONG)InterlockedIncrement((volatile LONG *)&g_ulThreadIndex);
    CurrentProcessorIndex = CurrentProcessorIndex % g_ulTotalProcessors;

    /* group, mask. */

    memcpy(&GroupAffinity, 
           &(g_MPI_ProcessorInfo[CurrentProcessorIndex].GroupAffinity), 
           sizeof(GROUP_AFFINITY));

    /* group, processor number */
    
    memcpy(&IdealProcessorNumber, 
           &(g_MPI_ProcessorInfo[CurrentProcessorIndex].ProcessorNumber), 
           sizeof(PROCESSOR_NUMBER)); 

    /* determine size of allocation for AttributeList */

    if(!func_InitializeProcThreadAttributeList(pAttributeList,
                                               2,
                                               0,
                                               &cbAttributeList))
    {
        DWORD dwLastError = GetLastError();
        if( dwLastError != ERROR_INSUFFICIENT_BUFFER )
        {
            tMPI_Fatal_error(TMPI_FARGS,
                             "InitializeProcThreadAttributeList, error code=%d",
                             dwLastError);
            goto cleanup;
        }
    }

    pAttributeList = (LPPROC_THREAD_ATTRIBUTE_LIST)tMPI_Malloc( cbAttributeList );
    if( pAttributeList == NULL )
    {
        tMPI_Fatal_error(TMPI_FARGS,"Failed to allocate pAttributeList");
        goto cleanup;
    }

    memset( pAttributeList, 0, cbAttributeList );

    if(!func_InitializeProcThreadAttributeList(pAttributeList,
                                               2,
                                               0,
                                               &cbAttributeList))
    {
        tMPI_Fatal_error(TMPI_FARGS,
                         "InitializeProcThreadAttributeList, error code=%d",
                         GetLastError());
        goto cleanup;
    }

    if(!func_UpdateProcThreadAttribute(pAttributeList,
                                       0,
                                       PROC_THREAD_ATTRIBUTE_GROUP_AFFINITY,
                                       &GroupAffinity,
                                       sizeof(GroupAffinity),
                                       NULL,
                                       NULL))
    {
        tMPI_Fatal_error(TMPI_FARGS,"UpdateProcThreadAttribute, error code=%d",
                         GetLastError());
        goto cleanup;
    }

    if(!func_UpdateProcThreadAttribute(pAttributeList,
                                       0,
                                       PROC_THREAD_ATTRIBUTE_IDEAL_PROCESSOR,
                                       &IdealProcessorNumber,
                                       sizeof(IdealProcessorNumber),
                                       NULL,
                                       NULL))
    {
        tMPI_Fatal_error(TMPI_FARGS,"UpdateProcThreadAttribute, error code=%d",
                         GetLastError());
        goto cleanup;
    }


    hThread = func_CreateRemoteThreadEx( GetCurrentProcess(),
                                         lpThreadAttributes,
                                         dwStackSize,
                                         lpStartAddress,
                                         lpParameter,
                                         dwCreationFlags,
                                         pAttributeList,
                                         lpThreadId);
            
    func_DeleteProcThreadAttributeList( pAttributeList );

#if 0   
	// TODO: debug only or DISCARD
    if( hThread )
    {
        PROCESSOR_NUMBER ProcNumber;
        USHORT NodeNumber;

        GetThreadIdealProcessorEx(hThread, &ProcNumber);
        GetNumaProcessorNodeEx(&ProcNumber, &NodeNumber);

        printf("started thread tid=%lu group=%lu mask=0x%I64x number=%lu numanode=%lu\n",
            *lpThreadId,
            GroupAffinity.Group,
            (ULONGLONG)GroupAffinity.Mask,
            ProcNumber.Number,
            NodeNumber
            );
    }
#endif

cleanup:
    
    if( pAttributeList )
    {
        tMPI_Free( pAttributeList );
    }

    return hThread;
}