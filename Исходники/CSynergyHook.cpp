static
bool
attachThreadToForeground()
{
    // only attach threads if using low level hooks.  a low level hook
    // runs in the thread that installed the hook but we have to make
    // changes that require being attached to the target thread (which
    // should be the foreground window).  a regular hook runs in the
    // thread that just removed the event from its queue so we're
    // already in the right thread.
    if (g_hookThread != 0) {
        HWND window    = GetForegroundWindow();
        DWORD threadID = GetWindowThreadProcessId(window, NULL);
        // skip if no change
        if (g_attachedThread != threadID) {
            // detach from previous thread
            detachThread();

            // attach to new thread
            if (threadID != 0 && threadID != g_hookThread) {
                AttachThreadInput(g_hookThread, threadID, TRUE);
                g_attachedThread = threadID;
            }
            return true;
        }
    }
    return false;
}