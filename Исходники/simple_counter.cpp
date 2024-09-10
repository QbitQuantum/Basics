void SimpleCounterWorker::updateThreadList()
{
    // now enum all threads for this processId
    if (loopCounter) {
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pid);

        // FIXME [avlechen] Strategy for exeptions is not defined
        if (hSnap == INVALID_HANDLE_VALUE) {
            DWORD exitCode = 0;
            if (GetExitCodeProcess(hProcess, &exitCode)) {
                if (exitCode != STILL_ACTIVE)  {
                    // FIXME [avlechen] Target program exited with code 0x%08x, exitCode;
                }
            } else {
                // FIXME [avlechen] CreateToolhelp32Snapshot failed with error code 0x%08x, GetLastError()
            }
        }

        threads.clear();
        THREADENTRY32 te;
        memset(&te, 0, sizeof(te));
        te.dwSize = sizeof(te);
        while (Thread32First(hSnap, &te) == FALSE) {
            if (te.th32OwnerProcessID == pid) {
                threads.push_back(te);
            }
        }
        // TODO [avlechen]: Possibly, we should store hSnap during sampling
        CloseHandle(hSnap);
    }
    loopCounter++;
}