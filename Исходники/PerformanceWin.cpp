int CollectorWin::preCollect(const CollectorHints& hints, uint64_t /* iTick */)
{
    LogFlowThisFuncEnter();

    uint64_t user, kernel, idle, total;
    int rc = getRawHostCpuLoad(&user, &kernel, &idle);
    if (RT_FAILURE(rc))
        return rc;
    total = user + kernel + idle;

    DWORD dwError;
    const CollectorHints::ProcessList& processes = hints.getProcessFlags();
    CollectorHints::ProcessList::const_iterator it;

    mProcessStats.clear();

    for (it = processes.begin(); it != processes.end() && RT_SUCCESS(rc); it++)
    {
        RTPROCESS process = it->first;
        HANDLE h = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                               FALSE, process);

        if (!h)
        {
            dwError = GetLastError();
            Log (("OpenProcess() -> 0x%x\n", dwError));
            rc = RTErrConvertFromWin32(dwError);
            break;
        }

        VMProcessStats vmStats;
        if ((it->second & COLLECT_CPU_LOAD) != 0)
        {
            FILETIME ftCreate, ftExit, ftKernel, ftUser;
            if (!GetProcessTimes(h, &ftCreate, &ftExit, &ftKernel, &ftUser))
            {
                dwError = GetLastError();
                Log (("GetProcessTimes() -> 0x%x\n", dwError));
                rc = RTErrConvertFromWin32(dwError);
            }
            else
            {
                vmStats.cpuKernel = FILETTIME_TO_100NS(ftKernel);
                vmStats.cpuUser   = FILETTIME_TO_100NS(ftUser);
                vmStats.cpuTotal  = total;
            }
        }
        if (RT_SUCCESS(rc) && (it->second & COLLECT_RAM_USAGE) != 0)
        {
            PROCESS_MEMORY_COUNTERS pmc;
            if (!GetProcessMemoryInfo(h, &pmc, sizeof(pmc)))
            {
                dwError = GetLastError();
                Log (("GetProcessMemoryInfo() -> 0x%x\n", dwError));
                rc = RTErrConvertFromWin32(dwError);
            }
            else
                vmStats.ramUsed = pmc.WorkingSetSize;
        }
        CloseHandle(h);
        mProcessStats[process] = vmStats;
    }

    LogFlowThisFuncLeave();

    return rc;
}