 DWORD GetMainThreadId() {
     const std::shared_ptr<void> hThreadSnapshot(
         CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0), CloseHandle);
     if (hThreadSnapshot.get() == INVALID_HANDLE_VALUE) {
         throw std::runtime_error("GetMainThreadId failed");
     }
     THREADENTRY32 tEntry;
     tEntry.dwSize = sizeof(THREADENTRY32);
     DWORD result = 0;
     DWORD currentPID = GetCurrentProcessId();
     for (BOOL success = Thread32First(hThreadSnapshot.get(), &tEntry);
     !result && success && GetLastError() != ERROR_NO_MORE_FILES;
         success = Thread32Next(hThreadSnapshot.get(), &tEntry))
     {
         if (tEntry.th32OwnerProcessID == currentPID) {
             result = tEntry.th32ThreadID;
         }
     }
     return result;
 }