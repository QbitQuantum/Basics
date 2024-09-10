 HOOKFUNC BOOL WINAPI MyGetSystemTimes(LPFILETIME lpIdleTime, LPFILETIME lpKernelTime, LPFILETIME lpUserTime)
 {
     ENTER();
     LOG() << "Warning: Not yet implemented!";
     return GetSystemTimes(lpIdleTime, lpKernelTime, lpUserTime);
 }