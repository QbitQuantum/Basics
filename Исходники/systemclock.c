static BOOL SystemClockPostMessageToAdviseThread(SystemClockImpl* This, UINT iMsg) {
  if (FALSE == This->adviseThreadActive) {
    BOOL res;
    This->adviseThread = CreateThread(NULL, 0, SystemClockAdviseThread, This, 0, &This->adviseThreadId);
    if (NULL == This->adviseThread) return FALSE;
    SetThreadPriority(This->adviseThread, THREAD_PRIORITY_TIME_CRITICAL);
    This->adviseThreadActive = TRUE;
    while(1) {
      res = PostThreadMessageW(This->adviseThreadId, iMsg, 0, 0);
      /* Let the thread creates its message queue (with MsgWaitForMultipleObjects call) by yielding and retrying */
      if (!res && (GetLastError() == ERROR_INVALID_THREAD_ID))
	Sleep(0);
      else
	break;
    }
    return res;
  }
  return PostThreadMessageW(This->adviseThreadId, iMsg, 0, 0);
}