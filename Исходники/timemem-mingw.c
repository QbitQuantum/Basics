void PrintMemoryAndTimeInfo (DWORD processID)
{
    HANDLE hProcess;
    DWORD ExitCode;
    PROCESS_MEMORY_COUNTERS pmc;
    FILETIME CreationTime;
    FILETIME ExitTime;
    FILETIME KernelTime;
    FILETIME UserTime;

    // Print the process identifier.
    fprintf(stderr, "\nProcess ID: %u\n", processID);

    // Get a handle for the process
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                           FALSE, processID);
    if (NULL == hProcess) {
        fprintf(stderr, " OpenProcess() returned NULL\n");
        return;
    }

    if (GetExitCodeProcess(hProcess, &ExitCode)) {
        fprintf(stderr, "    exit code: %d\n", ExitCode);
    } else {
        fprintf(stderr, " GetExitCodeProcess() returned FALSE\n");
        return;
    }

    // Print information about the cpu time of the process.
    // Documentation for GetProcessTimes() is available here:
    // http://msdn.microsoft.com/en-us/library/ms683223%28VS.85%29.aspx
    if (GetProcessTimes(hProcess, &CreationTime, &ExitTime,
                        &KernelTime, &UserTime)) {
        uint64 ctime = (((uint64) CreationTime.dwHighDateTime << 32)
                        + (uint64) CreationTime.dwLowDateTime);
        uint64 etime = (((uint64) ExitTime.dwHighDateTime << 32)
                        + (uint64) ExitTime.dwLowDateTime);
        uint64 ktime = (((uint64) KernelTime.dwHighDateTime << 32)
                        + (uint64) KernelTime.dwLowDateTime);
        uint64 utime = (((uint64) UserTime.dwHighDateTime << 32)
                        + (uint64) UserTime.dwLowDateTime);

        // ktime and utime are given to us in units of 100s of
        // nanoseconds.
        fprintf(stderr, "    elapsed time (seconds): %.2f\n",
                (etime - ctime) / 10000000.0);
        fprintf(stderr, "    user time (seconds): %.2f\n",
                utime / 10000000.0);
        fprintf(stderr, "    kernel time (seconds): %.2f\n",
                ktime / 10000000.0);
    } else {
        fprintf(stderr, "    GetProcessTimes() returned NULL\n");
    }

    // Print information about the memory usage of the process.
    if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
        fprintf(stderr, "    Page Fault Count: %u\n",
                pmc.PageFaultCount);
        fprintf(stderr, "    Peak Working Set Size (kbytes): %u\n",
                (pmc.PeakWorkingSetSize + 1023) / 1024);
        fprintf(stderr, "    Quota Peak Paged Pool Usage: %u\n",
                pmc.QuotaPeakPagedPoolUsage);
        fprintf(stderr, "    Quota Peak Non Paged Pool Usage: %u\n",
                pmc.QuotaPeakNonPagedPoolUsage);
        fprintf(stderr, "    Peak Pagefile Usage: %u\n",
                pmc.PeakPagefileUsage);

        // Don't bother to print these statistics, since they are most
        // likely garbage anyway, by the time the process has exited.

        //        fprintf(stderr, 
        //"\n"
        //"    Note that statistics below are probably worthless, since the\n"
        //"    process has already exited and they reflect the current resources\n"
        //"    used by the process.\n"
        //"\n"
        //                );
        //        fprintf(stderr, "    Working Set Size (kbytes): %u\n",
        //                (pmc.WorkingSetSize + 1023) / 1024);
        //        fprintf(stderr, "    Quota Paged Pool Usage: %u\n",
        //                pmc.QuotaPagedPoolUsage);
        //        fprintf(stderr, "    Quota Non Paged Pool Usage: %u\n",
        //                pmc.QuotaNonPagedPoolUsage);
        //        fprintf(stderr, "    Pagefile Usage: %u\n",
        //                pmc.PagefileUsage);
    } else {
        fprintf(stderr, "    GetProcessMemoryInfo() returned NULL\n");
    }
    CloseHandle(hProcess);
}