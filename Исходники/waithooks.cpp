 HOOKFUNC DWORD WINAPI MyMsgWaitForMultipleObjectsEx(DWORD nCount, const HANDLE *pHandles, DWORD dwMilliseconds, DWORD dwWakeMask, DWORD dwFlags)
 {
     ENTER(dwMilliseconds, dwWakeMask);
     //	TransferWait(dwMilliseconds);
     return MsgWaitForMultipleObjectsEx(nCount, pHandles, dwMilliseconds, dwWakeMask, dwFlags);
     // careful not to do anything (not even a printf) after the wait function...
     // many games will crash from a race condition if we don't return as fast as possible.
 }