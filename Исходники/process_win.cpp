//Based on http://stackoverflow.com/a/1173396
void Process::kill(bool force) {
  std::lock_guard<std::mutex> lock(close_mutex);
  if(data.id>0 && !closed) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(snapshot) {
      PROCESSENTRY32 process;
      ZeroMemory(&process, sizeof(process));
      process.dwSize = sizeof(process);
      if(Process32First(snapshot, &process)) {
        do {
          if(process.th32ParentProcessID==data.id) {
            HANDLE process_handle = OpenProcess(PROCESS_TERMINATE, FALSE, process.th32ProcessID);
            if(process_handle) {
              TerminateProcess(process_handle, 2);
              CloseHandle(process_handle);
            }
          }
        } while (Process32Next(snapshot, &process));
      }
      CloseHandle(snapshot);
    }
    TerminateProcess(data.handle, 2);
  }
}