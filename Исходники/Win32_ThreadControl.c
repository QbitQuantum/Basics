// This is meant to be called from the main thread only. 
void RequestSuspension() {
    if (!g_SuspensionRequested) {
        if (!ResetEvent(g_hResumeFromSuspension)) {
            exit(GetLastError());
        }
        _InterlockedOr(&g_SuspensionRequested, 1);
    }
}