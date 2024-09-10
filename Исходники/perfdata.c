void PerfDataRefresh(void)
{
    ULONG                                      ulSize;
    NTSTATUS                                   status;
    LPBYTE                                     pBuffer;
    ULONG                                      BufferSize;
    PSYSTEM_PROCESS_INFORMATION                pSPI;
    PPERFDATA                                  pPDOld;
    ULONG                                      Idx, Idx2;
    HANDLE                                     hProcess;
    HANDLE                                     hProcessToken;
    SYSTEM_PERFORMANCE_INFORMATION             SysPerfInfo;
    SYSTEM_TIMEOFDAY_INFORMATION               SysTimeInfo;
    SYSTEM_FILECACHE_INFORMATION               SysCacheInfo;
    LPBYTE                                     SysHandleInfoData;
    PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION  SysProcessorTimeInfo;
    double                                     CurrentKernelTime;
    PSECURITY_DESCRIPTOR                       ProcessSD;
    PSID                                       ProcessUser;
    ULONG                                      Buffer[64]; /* must be 4 bytes aligned! */
    ULONG                                      cwcUserName;

    /* Get new system time */
    status = NtQuerySystemInformation(SystemTimeOfDayInformation, &SysTimeInfo, sizeof(SysTimeInfo), NULL);
    if (!NT_SUCCESS(status))
        return;

    /* Get new CPU's idle time */
    status = NtQuerySystemInformation(SystemPerformanceInformation, &SysPerfInfo, sizeof(SysPerfInfo), NULL);
    if (!NT_SUCCESS(status))
        return;

    /* Get system cache information */
    status = NtQuerySystemInformation(SystemFileCacheInformation, &SysCacheInfo, sizeof(SysCacheInfo), NULL);
    if (!NT_SUCCESS(status))
        return;

    /* Get processor time information */
    SysProcessorTimeInfo = (PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION)HeapAlloc(GetProcessHeap(), 0, sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION) * SystemBasicInfo.NumberOfProcessors);
    status = NtQuerySystemInformation(SystemProcessorPerformanceInformation, SysProcessorTimeInfo, sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION) * SystemBasicInfo.NumberOfProcessors, &ulSize);

    if (!NT_SUCCESS(status))
    {
        if (SysProcessorTimeInfo != NULL)
            HeapFree(GetProcessHeap(), 0, SysProcessorTimeInfo);
        return;
    }

    /* Get handle information
     * We don't know how much data there is so just keep
     * increasing the buffer size until the call succeeds
     */
    BufferSize = 0;
    do
    {
        BufferSize += 0x10000;
        SysHandleInfoData = (LPBYTE)HeapAlloc(GetProcessHeap(), 0, BufferSize);

        status = NtQuerySystemInformation(SystemHandleInformation, SysHandleInfoData, BufferSize, &ulSize);

        if (status == STATUS_INFO_LENGTH_MISMATCH) {
            HeapFree(GetProcessHeap(), 0, SysHandleInfoData);
        }

    } while (status == STATUS_INFO_LENGTH_MISMATCH);

    /* Get process information
     * We don't know how much data there is so just keep
     * increasing the buffer size until the call succeeds
     */
    BufferSize = 0;
    do
    {
        BufferSize += 0x10000;
        pBuffer = (LPBYTE)HeapAlloc(GetProcessHeap(), 0, BufferSize);

        status = NtQuerySystemInformation(SystemProcessInformation, pBuffer, BufferSize, &ulSize);

        if (status == STATUS_INFO_LENGTH_MISMATCH) {
            HeapFree(GetProcessHeap(), 0, pBuffer);
        }

    } while (status == STATUS_INFO_LENGTH_MISMATCH);

    EnterCriticalSection(&PerfDataCriticalSection);

    /*
     * Save system performance info
     */
    memcpy(&SystemPerfInfo, &SysPerfInfo, sizeof(SYSTEM_PERFORMANCE_INFORMATION));

    /*
     * Save system cache info
     */
    memcpy(&SystemCacheInfo, &SysCacheInfo, sizeof(SYSTEM_FILECACHE_INFORMATION));

    /*
     * Save system processor time info
     */
    if (SystemProcessorTimeInfo) {
        HeapFree(GetProcessHeap(), 0, SystemProcessorTimeInfo);
    }
    SystemProcessorTimeInfo = SysProcessorTimeInfo;

    /*
     * Save system handle info
     */
    memcpy(&SystemHandleInfo, SysHandleInfoData, sizeof(SYSTEM_HANDLE_INFORMATION));
    HeapFree(GetProcessHeap(), 0, SysHandleInfoData);

    for (CurrentKernelTime=0, Idx=0; Idx<(ULONG)SystemBasicInfo.NumberOfProcessors; Idx++) {
        CurrentKernelTime += Li2Double(SystemProcessorTimeInfo[Idx].KernelTime);
        CurrentKernelTime += Li2Double(SystemProcessorTimeInfo[Idx].DpcTime);
        CurrentKernelTime += Li2Double(SystemProcessorTimeInfo[Idx].InterruptTime);
    }

    /* If it's a first call - skip idle time calcs */
    if (liOldIdleTime.QuadPart != 0) {
        /*  CurrentValue = NewValue - OldValue */
        dbIdleTime = Li2Double(SysPerfInfo.IdleProcessTime) - Li2Double(liOldIdleTime);
        dbKernelTime = CurrentKernelTime - OldKernelTime;
        dbSystemTime = Li2Double(SysTimeInfo.CurrentTime) - Li2Double(liOldSystemTime);

        /*  CurrentCpuIdle = IdleTime / SystemTime */
        dbIdleTime = dbIdleTime / dbSystemTime;
        dbKernelTime = dbKernelTime / dbSystemTime;

        /*  CurrentCpuUsage% = 100 - (CurrentCpuIdle * 100) / NumberOfProcessors */
        dbIdleTime = 100.0 - dbIdleTime * 100.0 / (double)SystemBasicInfo.NumberOfProcessors; /* + 0.5; */
        dbKernelTime = 100.0 - dbKernelTime * 100.0 / (double)SystemBasicInfo.NumberOfProcessors; /* + 0.5; */
    }

    /* Store new CPU's idle and system time */
    liOldIdleTime = SysPerfInfo.IdleProcessTime;
    liOldSystemTime = SysTimeInfo.CurrentTime;
    OldKernelTime = CurrentKernelTime;

    /* Determine the process count
     * We loop through the data we got from NtQuerySystemInformation
     * and count how many structures there are (until RelativeOffset is 0)
     */
    ProcessCountOld = ProcessCount;
    ProcessCount = 0;
    pSPI = (PSYSTEM_PROCESS_INFORMATION)pBuffer;
    while (pSPI) {
        ProcessCount++;
        if (pSPI->NextEntryOffset == 0)
            break;
        pSPI = (PSYSTEM_PROCESS_INFORMATION)((LPBYTE)pSPI + pSPI->NextEntryOffset);
    }

    /* Now alloc a new PERFDATA array and fill in the data */
    pPerfData = (PPERFDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(PERFDATA) * ProcessCount);

    pSPI = (PSYSTEM_PROCESS_INFORMATION)pBuffer;
    for (Idx=0; Idx<ProcessCount; Idx++) {
        /* Get the old perf data for this process (if any) */
        /* so that we can establish delta values */
        pPDOld = NULL;
        if (pPerfDataOld) {
            for (Idx2=0; Idx2<ProcessCountOld; Idx2++) {
                if (pPerfDataOld[Idx2].ProcessId == pSPI->UniqueProcessId) {
                    pPDOld = &pPerfDataOld[Idx2];
                    break;
                }
            }
        }

        if (pSPI->ImageName.Buffer) {
            /* Don't assume a UNICODE_STRING Buffer is zero terminated: */
            int len = pSPI->ImageName.Length / 2;
            /* Check against max size and allow for terminating zero (already zeroed): */
            if(len >= MAX_PATH)len=MAX_PATH - 1;
            wcsncpy(pPerfData[Idx].ImageName, pSPI->ImageName.Buffer, len);
        } else {
            LoadStringW(hInst, IDS_IDLE_PROCESS, pPerfData[Idx].ImageName,
                       sizeof(pPerfData[Idx].ImageName) / sizeof(pPerfData[Idx].ImageName[0]));
        }

        pPerfData[Idx].ProcessId = pSPI->UniqueProcessId;

        if (pPDOld)    {
            double    CurTime = Li2Double(pSPI->KernelTime) + Li2Double(pSPI->UserTime);
            double    OldTime = Li2Double(pPDOld->KernelTime) + Li2Double(pPDOld->UserTime);
            double    CpuTime = (CurTime - OldTime) / dbSystemTime;
            CpuTime = CpuTime * 100.0 / (double)SystemBasicInfo.NumberOfProcessors; /* + 0.5; */
            pPerfData[Idx].CPUUsage = (ULONG)CpuTime;
        }
        pPerfData[Idx].CPUTime.QuadPart = pSPI->UserTime.QuadPart + pSPI->KernelTime.QuadPart;
        pPerfData[Idx].WorkingSetSizeBytes = pSPI->WorkingSetSize;
        pPerfData[Idx].PeakWorkingSetSizeBytes = pSPI->PeakWorkingSetSize;
        if (pPDOld)
            pPerfData[Idx].WorkingSetSizeDelta = labs((LONG)pSPI->WorkingSetSize - (LONG)pPDOld->WorkingSetSizeBytes);
        else
            pPerfData[Idx].WorkingSetSizeDelta = 0;
        pPerfData[Idx].PageFaultCount = pSPI->PageFaultCount;
        if (pPDOld)
            pPerfData[Idx].PageFaultCountDelta = labs((LONG)pSPI->PageFaultCount - (LONG)pPDOld->PageFaultCount);
        else
            pPerfData[Idx].PageFaultCountDelta = 0;
        pPerfData[Idx].VirtualMemorySizeBytes = pSPI->VirtualSize;
        pPerfData[Idx].PagedPoolUsagePages = pSPI->QuotaPeakPagedPoolUsage;
        pPerfData[Idx].NonPagedPoolUsagePages = pSPI->QuotaPeakNonPagedPoolUsage;
        pPerfData[Idx].BasePriority = pSPI->BasePriority;
        pPerfData[Idx].HandleCount = pSPI->HandleCount;
        pPerfData[Idx].ThreadCount = pSPI->NumberOfThreads;
        pPerfData[Idx].SessionId = pSPI->SessionId;
        pPerfData[Idx].UserName[0] = UNICODE_NULL;
        pPerfData[Idx].USERObjectCount = 0;
        pPerfData[Idx].GDIObjectCount = 0;
        ProcessUser = SystemUserSid;
        ProcessSD = NULL;

        if (pSPI->UniqueProcessId != NULL) {
            hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | READ_CONTROL, FALSE, PtrToUlong(pSPI->UniqueProcessId));
            if (hProcess) {
                /* don't query the information of the system process. It's possible but
                   returns Administrators as the owner of the process instead of SYSTEM */
                if (pSPI->UniqueProcessId != (HANDLE)0x4)
                {
                    if (OpenProcessToken(hProcess, TOKEN_QUERY, &hProcessToken))
                    {
                        DWORD RetLen = 0;
                        BOOL Ret;

                        Ret = GetTokenInformation(hProcessToken, TokenUser, (LPVOID)Buffer, sizeof(Buffer), &RetLen);
                        CloseHandle(hProcessToken);

                        if (Ret)
                            ProcessUser = ((PTOKEN_USER)Buffer)->User.Sid;
                        else
                            goto ReadProcOwner;
                    }
                    else
                    {
ReadProcOwner:
                        GetSecurityInfo(hProcess, SE_KERNEL_OBJECT, OWNER_SECURITY_INFORMATION, &ProcessUser, NULL, NULL, NULL, &ProcessSD);
                    }

                    pPerfData[Idx].USERObjectCount = GetGuiResources(hProcess, GR_USEROBJECTS);
                    pPerfData[Idx].GDIObjectCount = GetGuiResources(hProcess, GR_GDIOBJECTS);
                }

                GetProcessIoCounters(hProcess, &pPerfData[Idx].IOCounters);
                CloseHandle(hProcess);
            } else {
                goto ClearInfo;
            }
        } else {
ClearInfo:
            /* clear information we were unable to fetch */
            ZeroMemory(&pPerfData[Idx].IOCounters, sizeof(IO_COUNTERS));
        }

        cwcUserName = sizeof(pPerfData[0].UserName) / sizeof(pPerfData[0].UserName[0]);
        CachedGetUserFromSid(ProcessUser, pPerfData[Idx].UserName, &cwcUserName);

        if (ProcessSD != NULL)
        {
            LocalFree((HLOCAL)ProcessSD);
        }

        pPerfData[Idx].UserTime.QuadPart = pSPI->UserTime.QuadPart;
        pPerfData[Idx].KernelTime.QuadPart = pSPI->KernelTime.QuadPart;
        pSPI = (PSYSTEM_PROCESS_INFORMATION)((LPBYTE)pSPI + pSPI->NextEntryOffset);
    }
    HeapFree(GetProcessHeap(), 0, pBuffer);
    if (pPerfDataOld) {
        HeapFree(GetProcessHeap(), 0, pPerfDataOld);
    }
    pPerfDataOld = pPerfData;
    LeaveCriticalSection(&PerfDataCriticalSection);
}