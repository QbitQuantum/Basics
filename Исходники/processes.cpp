/// Helper function for enumerating all active processes on the system
Status getProcList(std::set<long>& pids) {
  auto procSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (procSnap == INVALID_HANDLE_VALUE) {
    return Status(1, "Failed to open process snapshot");
  }

  PROCESSENTRY32 procEntry;
  procEntry.dwSize = sizeof(PROCESSENTRY32);
  auto ret = Process32First(procSnap, &procEntry);

  if (ret == FALSE) {
    CloseHandle(procSnap);
    return Status(1, "Failed to open first process");
  }

  while (ret != FALSE) {
    pids.insert(procEntry.th32ProcessID);
    ret = Process32Next(procSnap, &procEntry);
  }

  CloseHandle(procSnap);
  return Status(0, "Ok");
}