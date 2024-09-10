// TODO: I should probably move all initalization inside the thread
// We should minimize the amount of work done in DLL_PROCESS_ATTACH as per
// http://blogs.msdn.com/b/oleglv/archive/2003/10/24/56141.aspx
static BOOL ProcessAttach()
{
    lf("memtrace.dll: ProcessAttach()");
    if (!OpenPipe()) {
        lf("memtrace.dll: couldn't open pipe");
        return FALSE;
    } else {
        lf("memtrace.dll: opened pipe");
    }

    gHeap = HeapCreate(0, 0, 0);
    if (!gHeap) {
        lf("memtrace.dll: failed to create heap");
        return FALSE;
    }

    InitializeCriticalSection(&gMemMutex);
    gSendThreadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (!gSendThreadEvent) {
        lf("memtrace.dll: couldn't create gSendThreadEvent");
        return FALSE;
    }
    gSendThread = CreateThread(NULL, 0, DataSendThreadProc, NULL, 0, 0);
    if (!gSendThread) {
        lf("memtrace.dll: couldn't create gSendThread");
        return FALSE;
    }
    InstallHooks();
    return TRUE;
}