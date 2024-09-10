static DWORD GetMainThreadId() {
  std::vector<ThreadInfo> threads;

  HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
  if (snapshot != INVALID_HANDLE_VALUE) {
    THREADENTRY32 thread_entry;
    thread_entry.dwSize = sizeof(thread_entry);
    if (Thread32First(snapshot, &thread_entry)) {
      DWORD process_id = GetProcessId(GetCurrentProcess());
      do {
        if (thread_entry.dwSize >=
            FIELD_OFFSET(THREADENTRY32, th32OwnerProcessID) +
                         sizeof(thread_entry.th32OwnerProcessID)) {
          if (thread_entry.th32OwnerProcessID == process_id) {
            ThreadInfo thread = {0};
            thread.id = thread_entry.th32ThreadID;
            threads.push_back(thread);
          }
        }
        thread_entry.dwSize = sizeof(thread_entry);
      } while (Thread32Next(snapshot, &thread_entry));
    }
    CloseHandle(snapshot);
  }

  for (std::vector<ThreadInfo>::iterator it = threads.begin();
       it != threads.end(); it++) {
    ThreadInfo &info = *it;
    HANDLE handle = GetThreadHandle(info.id, THREAD_QUERY_INFORMATION);
    GetThreadTimes(handle, &info.creation_time, &info.exit_time,
                           &info.kernel_time,   &info.user_time);
  }

  threads.erase(std::remove_if(threads.begin(), threads.end(),
                               InvalidThread()), threads.end());
  if (!threads.empty()) {
    return std::min_element(threads.begin(), threads.end(),
                            CompareThreads())->id;
  }
  return 0;
}