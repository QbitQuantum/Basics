 HOOKFUNC HANDLE WINAPI MyOpenWaitableTimerA(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCSTR lpTimerName)
 {
     ENTER();
     HANDLE rv = OpenWaitableTimerA(dwDesiredAccess, bInheritHandle, lpTimerName);
     LEAVE(rv);
     EnterCriticalSection(&s_handleCS);
     std::set<HANDLE>& handles = s_threadIdHandles[GetCurrentThreadId()];
     handles.insert(rv);
     LeaveCriticalSection(&s_handleCS);
     return rv;
 }