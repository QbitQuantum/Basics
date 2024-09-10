HRESULT fSuspendThreadsInProcessById(DWORD dwProcessId) {
  HANDLE hThreadSnapshot;
  HRESULT hResult = fGetSnapshot(TH32CS_SNAPTHREAD, 0, hThreadSnapshot);
  if (SUCCEEDED(hResult)) {
    THREADENTRY32 oThreadEntry32;
    oThreadEntry32.dwSize = sizeof(oThreadEntry32);
    if (!Thread32First(hThreadSnapshot, &oThreadEntry32)) {
      _tprintf(_T("Cannot get first thread from snapshot\r\n"));
      hResult = HRESULT_FROM_WIN32(GetLastError());
    } else do {
      if (oThreadEntry32.th32OwnerProcessID == dwProcessId) {
        HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, oThreadEntry32.th32ThreadID);
        if (!hThread) {
          _tprintf(_T("Cannot open thread %d of process %d"), oThreadEntry32.th32ThreadID, oThreadEntry32.th32OwnerProcessID);
          hResult = HRESULT_FROM_WIN32(GetLastError());
        } else {
          if (SuspendThread(hThread) == -1) {
            _tprintf(_T("Cannot suspend thread %d of process %d"), oThreadEntry32.th32ThreadID, oThreadEntry32.th32OwnerProcessID);
            hResult = HRESULT_FROM_WIN32(GetLastError());
          }
          if (!fCloseHandleAndUpdateResult(hThread, hResult)) {
            _tprintf(_T("Cannot close thread %d of process %d\r\n"), oThreadEntry32.th32ThreadID, oThreadEntry32.th32OwnerProcessID);
          }
        }
      }
    } while (SUCCEEDED(hResult) && Thread32Next(hThreadSnapshot, &oThreadEntry32));
    if (!fCloseHandleAndUpdateResult(hThreadSnapshot, hResult)) {
      _tprintf(_T("Cannot close snapshot\r\n"));
    }
  }
  return hResult;
}