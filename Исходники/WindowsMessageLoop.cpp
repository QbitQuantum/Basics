void
InitUIThread()
{
  // If we aren't setup before a call to NotifyWorkerThread, we'll hang
  // on startup.
  if (!gUIThreadId) {
    gUIThreadId = GetCurrentThreadId();
  }

  MOZ_ASSERT(gUIThreadId);
  MOZ_ASSERT(gUIThreadId == GetCurrentThreadId(),
             "Called InitUIThread multiple times on different threads!");

  if (!gWinEventHook) {
    gWinEventHook = SetWinEventHook(EVENT_OBJECT_CREATE, EVENT_OBJECT_DESTROY,
                                    NULL, &WinEventHook, GetCurrentProcessId(),
                                    gUIThreadId, WINEVENT_OUTOFCONTEXT);

    // We need to execute this after setting the hook in case the OLE window
    // already existed.
    gCOMWindow = FindCOMWindow();
  }
  MOZ_ASSERT(gWinEventHook);
}