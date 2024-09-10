PPH_LIST EnumerateAppDomainIpcBlockWow64(
    _In_ HANDLE ProcessHandle,
    _In_ AppDomainEnumerationIPCBlock_Wow64* AppDomainIpcBlock
    )
{
    LARGE_INTEGER timeout;
    SIZE_T appDomainInfoBlockLength;
    HANDLE legacyPrivateBlockMutexHandle = NULL;
    AppDomainEnumerationIPCBlock_Wow64 tempBlock;
    AppDomainInfo_Wow64* appDomainInfoBlock = NULL;
    PPH_LIST appDomainsList = PhCreateList(1);

    // If the mutex isn't filled in, the CLR is either starting up or shutting down
    if (!AppDomainIpcBlock->Mutex)
    {
        goto CleanupExit;
    }

    // Dup the valid mutex handle into this process.
    if (!NT_SUCCESS(NtDuplicateObject(
        ProcessHandle,
        UlongToHandle(AppDomainIpcBlock->Mutex),
        NtCurrentProcess(),
        &legacyPrivateBlockMutexHandle,
        GENERIC_ALL,
        0,
        DUPLICATE_SAME_ACCESS | DUPLICATE_SAME_ATTRIBUTES
        )))
    {
        goto CleanupExit;
    }

    // Acquire the mutex, only waiting two seconds.
    // We can't actually gaurantee that the target put a mutex object in here.
    if (NtWaitForSingleObject(
        legacyPrivateBlockMutexHandle,
        FALSE,
        PhTimeoutFromMilliseconds(&timeout, 2000)
        ) == STATUS_WAIT_0)
    {
        // Make sure the mutex handle is still valid. If its not, then we lost a shutdown race.
        if (!AppDomainIpcBlock->Mutex)
        {
            goto CleanupExit;
        }
    }
    else
    {
        // Again, landing here is most probably a shutdown race.
        goto CleanupExit;
    }

    // Beware: If the target pid is not properly honoring the mutex, the data in the IPC block may still shift underneath us.
    // If we get here, then hMutex is held by this process.

    // Make a copy of the IPC block so that we can gaurantee that it's not changing on us.
    memcpy(&tempBlock, AppDomainIpcBlock, sizeof(AppDomainEnumerationIPCBlock_Wow64));

    // It's possible the process will not have any appdomains.
    if ((tempBlock.ListOfAppDomains == 0) != (tempBlock.SizeInBytes == 0))
    {
        goto CleanupExit;
    }

    // All the data in the IPC block is signed integers. They should never be negative,
    // so check that now.
    if ((tempBlock.TotalSlots < 0) ||
        (tempBlock.NumOfUsedSlots < 0) ||
        (tempBlock.LastFreedSlot < 0) ||
        (tempBlock.SizeInBytes < 0) ||
        (tempBlock.ProcessNameLengthInBytes < 0))
    {
        goto CleanupExit;
    }

    // Allocate memory to read the remote process' memory into
    appDomainInfoBlockLength = tempBlock.SizeInBytes;

    // Check other invariants.
    if (appDomainInfoBlockLength != tempBlock.TotalSlots * sizeof(AppDomainInfo_Wow64))
    {
        goto CleanupExit;
    }

    appDomainInfoBlock = (AppDomainInfo_Wow64*)PhAllocate(appDomainInfoBlockLength);
    memset(appDomainInfoBlock, 0, appDomainInfoBlockLength);

    if (!NT_SUCCESS(NtReadVirtualMemory(
        ProcessHandle,
        UlongToPtr(tempBlock.ListOfAppDomains),
        appDomainInfoBlock,
        appDomainInfoBlockLength,
        NULL
        )))
    {
        PhFree(appDomainInfoBlock);
        goto CleanupExit;
    }

    // Collect all the AppDomain names into a list of strings.
    for (INT i = 0; i < tempBlock.NumOfUsedSlots; i++)
    {
        SIZE_T appDomainNameLength;
        PVOID appDomainName;

        if (!appDomainInfoBlock[i].AppDomainName)
            continue;

        // Should be positive, and at least have a null-terminator character.
        if (appDomainInfoBlock[i].NameLengthInBytes <= 1)
            continue;

        // Make sure buffer has right geometry.
        if (appDomainInfoBlock[i].NameLengthInBytes < 0)
            continue;

        // If it's not on a WCHAR boundary, then we may have a 1-byte buffer-overflow.
        appDomainNameLength = appDomainInfoBlock[i].NameLengthInBytes / sizeof(WCHAR);

        if ((appDomainNameLength * sizeof(WCHAR)) != appDomainInfoBlock[i].NameLengthInBytes)
            continue;

        // It should at least have 1 char for the null terminator.
        if (appDomainNameLength < 1)
            continue;

        // We know the string is a well-formed null-terminated string,
        // but beyond that, we can't verify that the data is actually truthful.
        appDomainName = PhAllocate(appDomainInfoBlock[i].NameLengthInBytes + 1);
        memset(appDomainName, 0, appDomainInfoBlock[i].NameLengthInBytes + 1);

        if (!NT_SUCCESS(NtReadVirtualMemory(
            ProcessHandle,
            UlongToPtr(appDomainInfoBlock[i].AppDomainName),
            appDomainName,
            appDomainInfoBlock[i].NameLengthInBytes,
            NULL
            )))
        {
            PhFree(appDomainName);
            continue;
        }

        PhAddItemList(appDomainsList, appDomainName);
    }

CleanupExit:

    if (appDomainInfoBlock)
    {
        PhFree(appDomainInfoBlock);
    }

    if (legacyPrivateBlockMutexHandle)
    {
        NtReleaseMutant(legacyPrivateBlockMutexHandle, NULL);
        NtClose(legacyPrivateBlockMutexHandle);
    }

    return appDomainsList;
}